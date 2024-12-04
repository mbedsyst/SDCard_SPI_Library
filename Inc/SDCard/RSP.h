#ifndef __RSP_H__
#define __RSP_H__

// R1 Response Bits
#define R1_IDLE_STATE          		(1 << 0)  // Card is in idle state
#define R1_ERASE_RESET         		(1 << 1)  // Erase reset occurred
#define R1_ILLEGAL_COMMAND     		(1 << 2)  // Illegal command received
#define R1_COM_CRC_ERROR       		(1 << 3)  // CRC check failed
#define R1_ERASE_SEQ_ERROR     		(1 << 4)  // Erase sequence error
#define R1_ADDRESS_ERROR       		(1 << 5)  // Mis-aligned address
#define R1_PARAMETER_ERROR     		(1 << 6)  // Invalid parameter
#define R1_READY_FOR_DATA      		(1 << 8)  // Card ready for data (applicable in transfer mode)
#define R1_APP_CMD             		(1 << 9)  // Next command is application-specific

// R1B Response Bits
#define R1B_BUSY					(0x00)  // Card is busy (after R1 bits)

// R2 Response: No specific flags (contains 128 bits of data)
#define R2_CID_CSD_LENGTH      		(136)     // Total length of R2 response (bits)

// R3 Response Bits (OCR Register)
#define R3_OCR_MASK            		(0xFFFFFFFF)  // OCR register mask (32 bits)
#define R3_POWER_UP_STATUS     		(1 << 31)     // Card is powered up and ready

// R6 Response Bits
#define R6_RCA_MASK            		(0xFFFF0000)  // Mask to extract RCA
#define R6_STATUS_MASK         		(0x0000FFFF)  // Status bits (like R1)
#define R6_ERROR               		(1 << 19)     // Generic error
#define R6_ILLEGAL_COMMAND     		(1 << 22)     // Illegal command received
#define R6_COM_CRC_ERROR       		(1 << 23)     // CRC error

// R7 Response Bits
#define R7_VOLTAGE_ACCEPTED    		(0x00000100)  // Voltage range supported
#define R7_CHECK_PATTERN       		(0x000000FF)  // Echo-back check pattern
#define R7_VALID_RESPONSE      		(0x000001AA)  // Expected response for CMD8

// Response Parsing Macros
#define R1_IS_ERROR(r1)       		((r1) & 0xFE)  						// Check if any error flags are set
#define R1B_IS_CARD_BUSY(r1b)       ((r1b) == R1B_BUSY) 				// Check if the card is still busy
#define R1B_IS_CARD_READY(r1b)      ((r1b) != R1B_BUSY) 				// Check if the card is read
#define R3_GET_OCR(response)   		((response) & R3_OCR_MASK)  		// Extract OCR from R3
#define R6_GET_RCA(response)   		(((response) & R6_RCA_MASK) >> 16)  // Extract RCA from R6
#define R7_GET_PATTERN(response) 	((response) & R7_CHECK_PATTERN)  	// Extract check pattern
#define R7_IS_VALID(r7)        		((r7) == R7_VALID_RESPONSE)  		// Validate R7 response

void CheckResponse(uint8_t cmd, uint32_t response);

#endif
