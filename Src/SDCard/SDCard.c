#include "SDCard/SDCard.h"

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

    // Send CMD0 (GO_IDLE_STATE) to Reset the Card
    response = SD_SendCommand(CMD_RESET_AND_IDLE, 0x00000000, 0x95);
    CheckResponse(CMD_RESET_AND_IDLE, response);
    if (!(response & R1_IDLE_STATE))
    {
        printf("Card reset failed. Not in Idle State. Response: 0x%02X\n\r", response);
        return response;
    }

    // Send CMD8 (SEND_IF_COND) to Check the Voltage Range
    response = SD_SendCommand(CMD_CHECK_VOLT_LEVEL, 0x000001AA, 0x87);
    CheckResponse(CMD_CHECK_VOLT_LEVEL, response);
    if (!R7_IS_VALID(response))
    {
        printf("Card does not support the Voltage range.\n\r");
        return response;
    }

    // Poll with CMD1 (SEND_OP_COND) until Card exits the Idle State
    for (int i = 0; i < 1000; i++)
    {
        response = SD_SendCommand(CMD_INIT_AND_READY, 0x40000000, 0xFF);
        CheckResponse(CMD_INIT_AND_READY, response);
        if (!(response & R1_IDLE_STATE))
        {
            printf("Card is initialized and ready.\n");
            break;
        }
        delay_ms(1);
    }
    if (response & R1_IDLE_STATE)
    {
        printf("Card initialization timed out.\n");
        return response;
    }

    // Send CMD58 (READ_OCR) to get the OCR (Operating Conditions Register)
    uint32_t ocr;
    response = SD_SendCommand(CMD_GET_CARD_CONDITIONS, 0x00000000, 0xFF);
    CheckResponse(CMD_GET_CARD_CONDITIONS, response);
    ocr = R3_GET_OCR(response);
    if (response & R3_POWER_UP_STATUS)
    {
        printf("Card OCR: 0x%08X, Card is powered up and ready.\n\r", (unsigned int)ocr);
    }
    else
    {
        printf("Card OCR: 0x%08X, Card is NOT powered up.\n\r", (unsigned int)ocr);
        return response;
    }

    // Card initialization completed successfully
    printf("SD card Reset and Initialization completed successfully.\n\r");
    return 0x00;
}


