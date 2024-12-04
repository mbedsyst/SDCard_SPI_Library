#include "SDCard/SDCard.h"
#include "SDCard/CMD.h"
#include "SDCard/RSP.h"
#include <stdio.h>

static uint8_t SD_SendCommand(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    uint8_t response;
    SPI2_SelectSlave();
    SPI2_TransmitReceiveByte(cmd);                    // Command byte
    SPI2_TransmitReceiveByte((arg >> 24) & 0xFF);     // Argument byte 3
    SPI2_TransmitReceiveByte((arg >> 16) & 0xFF);     // Argument byte 2
    SPI2_TransmitReceiveByte((arg >> 8) & 0xFF);      // Argument byte 1
    SPI2_TransmitReceiveByte(arg & 0xFF);             // Argument byte 0
    SPI2_TransmitReceiveByte(crc);                    // CRC byte

    for (int i = 0; i < 8; i++)
    {
        response = SPI2_TransmitReceiveByte(0xFF);
        if ((response & 0x80) == 0)
        {
            break;
        }
    }

    SPI2_DeselectSlave();
    return response;
}

uint8_t SD_Reset(void)
{
    uint8_t response;

    // Send CMD0 (GO_IDLE_STATE) to reset the card
    response = SD_SendCommand(CMD_RESET_AND_IDLE, 0x00000000, 0x95); // CMD0 with valid CRC
    CheckResponse(CMD_RESET_AND_IDLE, response);

    if (response & R1_IDLE_STATE)
    {
        printf("Card is in Idle State after reset.\n");
    }
    else
    {
        printf("Card reset failed or is not in Idle State. Response: 0x%02X\n", response);
        return response; // Return the response in case of failure
    }

    // Send CMD8 (SEND_IF_COND) to check the voltage range
    response = SD_SendCommand(CMD_CHECK_VOLT_LEVEL, 0x000001AA, 0x87); // CMD8 with check pattern and CRC
    CheckResponse(CMD_CHECK_VOLT_LEVEL, response);

    if (!R7_IS_VALID(response))
    {
        printf("Card does not support the voltage range or check pattern mismatch.\n");
        return response; // Return error if CMD8 validation fails
    }

    // Poll with CMD1 (SEND_OP_COND) until card exits the Idle State
    for (int i = 0; i < 1000; i++)
    {
        response = SD_SendCommand(CMD_INIT_AND_READY, 0x40000000, 0xFF); // CMD1 with high-capacity support
        CheckResponse(CMD_INIT_AND_READY, response);

        if (!(response & R1_IDLE_STATE))
        {
            printf("Card is initialized and ready.\n");
            break;
        }

        // Add a short delay (platform-specific delay function)
        Platform_Delay(1); // Delay 1 ms
    }

    if (response & R1_IDLE_STATE)
    {
        printf("Card initialization timed out.\n");
        return response; // Return error if card fails to initialize
    }

    // Send CMD58 (READ_OCR) to get the OCR (Operating Conditions Register)
    uint32_t ocr;
    response = SD_SendCommand(CMD_GET_CARD_CONDITIONS, 0x00000000, 0xFF);
    CheckResponse(CMD_GET_CARD_CONDITIONS, response);
    ocr = R3_GET_OCR(response);

    if (response & R3_POWER_UP_STATUS)
    {
        printf("Card OCR: 0x%08X, Card is powered up and ready.\n", ocr);
    }
    else
    {
        printf("Card OCR: 0x%08X, Card is NOT powered up.\n", ocr);
        return response; // Return error if card is not powered up
    }

    // Card initialization completed successfully
    printf("SD card reset and initialization completed successfully.\n");
    return 0x00; // Return 0x00 for success
}

uint8_t SD_WriteBlock(uint32_t blockAddr, uint8_t *data)
{
    uint8_t response;

    // Send WRITE_BLOCK command (CMD24) with the block address
    response = SD_SendCommand(WRITE_BLOCK, blockAddr, 0xFF);

    // Check the response of CMD24
    CheckResponse(WRITE_BLOCK, response);
    if (response != 0x00) // Check if R1 response indicates no error
    {
        SPI2_DeselectSlave();
        return response; // Return error response
    }

    // Send the Data Start Token
    SPI2_TransmitReceiveByte(DATA_START_TOKEN);

    // Transmit the 512 bytes of data
    for (int i = 0; i < 512; i++)
    {
        SPI2_TransmitReceiveByte(data[i]);
    }

    // Send 2 dummy CRC bytes (not used in SPI mode)
    SPI2_TransmitReceiveByte(0xFF);
    SPI2_TransmitReceiveByte(0xFF);

    // Read the data response token
    response = SPI2_TransmitReceiveByte(0xFF) & DATA_RESPONSE_MASK;
    if (response != DATA_ACCEPTED) // Check if the data was accepted
    {
        printf("Data response error: 0x%02X\n", response);
        SPI2_DeselectSlave();
        return response; // Return error response
    }

    // Wait for the card to complete writing the block
    while (SPI2_TransmitReceiveByte(0xFF) == 0x00)
        ;

    // Check R1 response to confirm successful completion
    response = SD_SendCommand(13, 0, 0xFF); // CMD13: SEND_STATUS
    CheckResponse(13, response);

    if (response != 0x00) // If any errors persist after writing
    {
        SPI2_DeselectSlave();
        return response; // Return error response
    }

    SPI2_DeselectSlave();
    return 0x00; // Return 0x00 for success
}
