
#include "BRAM_controller.h"
#include <stdint.h>
#include <xil_types.h>


uint8_t colour_background = 0x00; // First background colour
uint8_t colour_hand = 0x03; // First change colour
uint8_t colour_hand_closed = 0x1C;
        
// Pointer to BRAM
volatile uint8_t *bram_ptr = (volatile uint8_t *)BRAM_BASE_ADDRESS;


struct HandSpeler{
    bool available;
    bool closed;
    uint16_t x;
    uint16_t y;
};

HandSpeler hands[2] {{TRUE, FALSE, 0,0}, {TRUE, FALSE, 0, 0}};



// internal methods
void BRAM_write_square();


void BRAM_write(void)  { 
    BRAM_write_reset();
    BRAM_write_square();
}

void set_hand_closed(bool left, bool right){
    hands[0].closed = left;
    hands[1].closed = right;
}

void set_hand_available(bool left, bool right){
    hands[0].available = left;
    hands[1].available = right;
}

void BRAM_write_square(void) {
    uint8_t colour;

    for (int i = 0; i<2; i++) {
        if (hands[i].available) {

            if (hands[i].closed) {
                colour = colour_hand_closed;
            }else colour = colour_hand;

            uint16_t x = hands[i].x;
            uint16_t y = hands[i].y;
            bool work = TRUE;
        
            while (work){
                bram_ptr[x + (y * SCREEN_WIDTH)] = colour;
                x++;
                if (x >= hands[i].x + SQUARE_WIDTH || x >= SCREEN_WIDTH) {
                    x = hands[i].x ;
                    y = y + 1;
                    if (y >= hands[i].y + SQUARE_WIDTH) {
                        work = FALSE;
                    }
                }
            }
        }
    }
}

void BRAM_write_reset(void){
    for (uint32_t i = 0; i < BRAM_SIZE; i++) {
        bram_ptr[i] = colour_background; 
    }
}

void BRAM_backgroundcolour(uint8_t background){
    colour_background = background;
}

void BRAM_square(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
    if (!(x2 > SCREEN_WIDTH) && !(x1 > SCREEN_WIDTH) &&
     !(y1 > SCREEN_HEIGHT) && !(y2 > SCREEN_HEIGHT)){ // Limits x and y axis 
        hands[0].x = x1;
        hands[0].y = y1;

        hands[1].x = x2;
        hands[1].y = y2;

        BRAM_write_reset();
        BRAM_write_square();

    }else{
        colour_background = 0xE0;
        BRAM_write_reset(); 
    }
}
