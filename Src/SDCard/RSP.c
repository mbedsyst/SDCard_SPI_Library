#include "SDCard/RSP.h"
#include "SDCard/CMD.h"
#include <stdio.h>
#include <stdint.h>

static void CheckR1(uint8_t r1)
{
    printf("R1 Response: 0x%02X\n", r1);

    if (r1 & R1_IDLE_STATE)
    	printf("- Card is in Idle State\n");
    if (r1 & R1_ERASE_RESET)
    	printf("- Erase Reset occurred\n");
    if (r1 & R1_ILLEGAL_COMMAND)
    	printf("- Illegal Command\n");
    if (r1 & R1_COM_CRC_ERROR)
    	printf("- Command CRC Error\n");
    if (r1 & R1_ERASE_SEQ_ERROR)
    	printf("- Erase Sequence Error\n");
    if (r1 & R1_ADDRESS_ERROR)
    	printf("- Address Mis-aligned\n");
    if (r1 & R1_PARAMETER_ERROR)
    	printf("- Parameter Error\n");
    if (!(r1 & 0xFE))
    	printf("- No Errors\n");
}


static void CheckR3(uint32_t r3)
{
    printf("R3 Response: 0x%08X\n", (unsigned int)r3);

    if (r3 & R3_POWER_UP_STATUS)
    {
        printf("- Card is Powered Up and Ready\n");
    }
    else
    {
        printf("- Card is NOT Powered Up\n");
    }

    printf("- OCR Value: 0x%08X\n", (unsigned int)(r3 & R3_OCR_MASK));
}


static void CheckR7(uint32_t r7)
{
    printf("R7 Response: 0x%08X\n", (unsigned int)r7);

    uint8_t voltage = (r7 & R7_VOLTAGE_ACCEPTED) >> 8;
    printf("- Voltage Accepted: 0x%02X\n", voltage);

    uint8_t pattern = R7_GET_PATTERN(r7);
    printf("- Check Pattern: 0x%02X\n", pattern);

    if (R7_IS_VALID(r7))
    {
        printf("- R7 Response is Valid\n");
    }
    else
    {
        printf("- R7 Response is NOT Valid\n");
    }
}


void CheckResponse(uint8_t cmd, uint32_t response)
{
    switch (cmd)
    {
        case CMD_RESET_AND_IDLE   :
        case CMD_INIT_AND_READY   :
        case CMD_STOP_TRANSMISSION:
        case CMD_SET_BLOCKLEN     :
        case CMD_READ_SINGLE_BLOCK:
        case CMD_WRITE_BLOCK      :
        			CheckR1((uint8_t)response);
            		break;

        case CMD_GET_CARD_CONDITIONS:
        			CheckR3(response);
            		break;

        case CMD_CHECK_VOLT_LEVEL:  CheckR7(response);
            	    break;

        default:	printf("Unknown or unsupported response type for CMD%d\n", cmd & 0x3F);
        			break;
    }
}

