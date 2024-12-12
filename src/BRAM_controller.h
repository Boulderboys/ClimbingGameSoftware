#include <stdint.h>
#include <xgpio.h>
#include <xil_printf.h>
#include <xil_types.h>
#include <xparameters.h>

// bram constants
#define BRAM_BASE_ADDRESS  0x8'0000
#define SCREEN_WIDTH       640
#define SCREEN_HEIGHT      480
#define BRAM_SIZE    (SCREEN_WIDTH * SCREEN_HEIGHT) // Pixels bij 8-bit kleur
#define SQUARE_WIDTH       50

void BRAM_write(void);

void BRAM_backgroundcolour(uint8_t background);

void BRAM_square(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void BRAM_write_reset(void);

void set_Hand_Closed(bool left, bool right);

void set_Hand_Available(bool left, bool right);
