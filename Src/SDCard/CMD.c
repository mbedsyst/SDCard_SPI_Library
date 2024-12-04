#include "SDCard/CMD.h"

// Initialization and General Commands
#define CMD_RESET_AND_IDLE           (0x40 | 0)   // CMD0
#define CMD_INIT_AND_READY           (0x40 | 1)   // CMD1

// Card Info and Status Commands
#define CMD_CHECK_VOLT_LEVEL         (0x40 | 8)   // CMD8
#define CMD_GET_CARD_SPECS_DATA      (0x40 | 9)   // CMD9
#define CMD_GET_CARD_ID_DATA         (0x40 | 10)  // CMD10
#define CMD_GET_CARD_CONDITIONS      (0x40 | 58)  // CMD58

// Data Transfer Commands
#define CMD_SET_BLOCKLEN             (0x40 | 16)  // CMD16
#define CMD_READ_SINGLE_BLOCK        (0x40 | 17)  // CMD17
#define CMD_READ_MULTIPLE_BLOCK      (0x40 | 18)  // CMD18
#define CMD_WRITE_BLOCK              (0x40 | 24)  // CMD24
#define CMD_WRITE_MULTIPLE_BLOCK     (0x40 | 25)  // CMD25

// Multi-Block Operations
#define CMD_STOP_TRANSMISSION        (0x40 | 12)  // CMD12
#define CMD_SET_BLOCK_COUNT          (0x40 | 23)  // CMD23

// Application-Specific Commands
#define CMD_APP_CMD                  (0x40 | 55)  // CMD55
#define ACMD_APP_SEND_OP_COND        (0x40 | 41)  // ACMD41
#define ACMD_SET_BLOCK_ERASE_COUNT   (0x40 | 23)  // ACMD23
