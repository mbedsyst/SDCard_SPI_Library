#include "SDCard/SDCard.h"

// SD Card Commands
#define GO_IDLE_STATE            (0x40 | 0)   // CMD0
#define SEND_OP_COND             (0x40 | 1)   // CMD1
#define SEND_IF_COND             (0x40 | 8)   // CMD8
#define SEND_CSD                 (0x40 | 9)   // CMD9
#define SEND_CID                 (0x40 | 10)  // CMD10
#define STOP_TX                  (0x40 | 12)  // CMD12
#define SET_BLOCKLEN             (0x40 | 16)  // CMD16
#define READ_SINGLE_BLOCK        (0x40 | 17)  // CMD17
#define READ_MULTIPLE_BLOCK      (0x40 | 18)  // CMD18
#define SET_BLOCK_COUNT          (0x40 | 23)  // CMD23
#define WRITE_BLOCK              (0x40 | 24)  // CMD24
#define WRITE_MULTIPLE_BLOCK     (0x40 | 25)  // CMD25
#define APP_CMD                  (0x40 | 55)  // CMD55
#define READ_OCR                 (0x40 | 58)  // CMD58
#define APP_SEND_OP_COND         (0x40 | 41)  // ACMD41 
#define SET_WR_BLOCK_ERASE_COUNT (0x40 | 23)  // ACMD23 

void SD_Reset(void)
{

}

void SD_WriteBlock(uint32_t address, uint8_t *data, uint16_t size)
{

}

void SD_ReadBlock(uint32_t address, uint8_t *data, uint16_t size)
{

}
