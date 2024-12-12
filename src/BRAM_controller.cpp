
#include "BRAM_controller.h"
#include <stdint.h>
#include <xil_types.h>


uint8_t colour_background = 0x00; // First background colour
uint8_t colour_hand = 0x03; // First change colour
uint8_t colour_hand_closed = 0x1C;
        
// Pointer to BRAM
volatile uint8_t *bram_ptr = (volatile uint8_t *)BRAM_BASE_ADDRESS;

uint16_t xy_array[2][2];


bool Hand_Closed[2] = {FALSE, FALSE};

bool Hand_Available[2] = {TRUE, TRUE};


// internal methods
void BRAM_write_square();


void BRAM_write(void)  { 
    BRAM_write_reset();
    BRAM_write_square();
}

void set_Hand_Closed(bool left, bool right){
    Hand_Closed[0] = left;
    Hand_Closed[1] = right;
}

void set_Hand_Available(bool left, bool right){
    Hand_Available[0] = left;
    Hand_Available[1] = right;
}

void BRAM_write_square(void) {
    uint8_t colour;

    for (int i = 0; i<2; i++) {
        if (Hand_Available[i]) {

            if (Hand_Closed[i]) {
                colour = colour_hand_closed;
            }else colour = colour_hand;

            uint16_t x = xy_array[i][0];
            uint16_t y = xy_array[i][1];
            bool work = TRUE;
        
            while (work){
                bram_ptr[x + (y * SCREEN_WIDTH)] = colour;
                x++;
                if (x >= xy_array[i][0] + SQUARE_WIDTH || x >= SCREEN_WIDTH) {
                    x = xy_array[i][0];
                    y = y + 1;
                    if (y >= xy_array[i][1] + SQUARE_WIDTH) {
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

void BRAM_colour(uint8_t background){
    colour_background = background;
}

void BRAM_square(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
    if (!(x2 > SCREEN_WIDTH) && !(x1 > SCREEN_WIDTH) &&
     !(y1 > SCREEN_HEIGHT) && !(y2 > SCREEN_HEIGHT)){ // beperkingen x en y as 
        xy_array[0][0] = x1;
        xy_array[0][1] = y1;

        xy_array[1][0] = x2;
        xy_array[1][1] = y2;

        BRAM_write_reset();
        BRAM_write_square();

    }else{
        colour_background = 0xE0;
        BRAM_write_reset(); 
    }
}

// void test(){
//     bool work = true;
//     uint16_t cnt = 0;
//     while(work){

//         bram_ptr[SCREEN_WIDTH * cnt + 160] = 0x0F;
//         bram_ptr[SCREEN_WIDTH * cnt + 159] = 0xF0;
//         cnt++;

//         if (cnt >= SCREEN_HEIGHT){
//             work = FALSE;
//         }
//     }
// }
