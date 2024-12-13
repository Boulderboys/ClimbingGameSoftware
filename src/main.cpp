#include "BRAM_controller.h"
#include <stdint.h>
#include <xil_types.h>

#define LED_DELAY       10000
#define LED_CHANNEL     1
#define SWITCH_CHANNEL  1

#define LED             0xFFFF
#define SWITCH          0xFFFF



int main()
{
    XGpio Gpio_led, Gpio_switches;

    // Initialiseer GPIO met de juiste device ID's
    XGpio_Initialize(&Gpio_led, XPAR_AXI_GPIO_0_BASEADDR);
    XGpio_Initialize(&Gpio_switches, XPAR_AXI_GPIO_1_BASEADDR);

    // Configureer GPIO-richting
    XGpio_SetDataDirection(&Gpio_led, LED_CHANNEL, ~LED);         
    XGpio_SetDataDirection(&Gpio_switches, SWITCH_CHANNEL, SWITCH); 

    BRAM_write();

    uint16_t x1 = 0;
    uint16_t y1 = 200;
    uint16_t x2 = 400;
    uint16_t y2 = 200;

        BRAM_square(x1, y1, x2, y2);


//    BRAM_write_reset();
//    test();

    while (1) { 

            x2--;
            y2++;
            BRAM_square(x1,y1,x2,y2);

            if (y1 == 100){
                set_hand_available(FALSE, TRUE);
            }else {
                x1++;
                y1--;
            }

            if (y2 >= 300){
                set_hand_closed(FALSE, TRUE);
            }

        uint32_t value = XGpio_DiscreteRead(&Gpio_switches, SWITCH_CHANNEL);
        XGpio_DiscreteWrite(&Gpio_led, LED_CHANNEL, value);
    }

    return 0;
}
