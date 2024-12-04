#include "SDCard/RSP.h"

#include <stdio.h>

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
    printf("R3 Response: 0x%08X\n", r3);

    if (r3 & R3_POWER_UP_STATUS)
    {
        printf("- Card is Powered Up and Ready\n");
    }
    else
    {
        printf("- Card is NOT Powered Up\n");
    }

    printf("- OCR Value: 0x%08X\n", (r3 & R3_OCR_MASK));
}


static void CheckR6(uint32_t r6)
{
    printf("R6 Response: 0x%08X\n", r6);
    uint16_t rca = R6_GET_RCA(r6);
    printf("- Relative Card Address (RCA): 0x%04X\n", rca);

    if (r6 & R6_ERROR)
    	printf("- Generic Error\n");
    if (r6 & R6_ILLEGAL_COMMAND)
    	printf("- Illegal Command\n");
    if (r6 & R6_COM_CRC_ERROR)
    	printf("- Command CRC Error\n");
}


static void CheckR7(uint32_t r7)
{
    printf("R7 Response: 0x%08X\n", r7);

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
        case CMD0:
        case CMD1:
        case CMD12:
        case CMD16:
        case CMD17:
        case CMD24:	CheckR1((uint8_t)response);
            		break;

        case CMD58: CheckR3(response);
            		break;

        case CMD3:  CheckR6(response);
            	    break;

        case CMD8:  CheckR7(response);
            	    break;

        default:	printf("Unknown or unsupported response type for CMD%d\n", cmd & 0x3F);
        			break;
    }
}

