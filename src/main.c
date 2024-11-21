#include <xgpio.h>
#include <xil_printf.h>
#include <xparameters.h>

#define LED_DELAY     10000
#define LED_CHANNEL 1
#define SWITCH_CHANNEL 1

#define LED 0xFFFF 
#define SWITCH 0xFFFF

int main()
{
    XGpio Gpio_led, Gpio_switches;
    XGpio_Initialize(&Gpio_led, XPAR_AXI_GPIO_0_BASEADDR);
    XGpio_Initialize(&Gpio_switches, XPAR_AXI_GPIO_1_BASEADDR);
    volatile int Delay;

    XGpio_SetDataDirection(&Gpio_led, LED_CHANNEL, ~LED);
    XGpio_SetDataDirection(&Gpio_switches, SWITCH_CHANNEL, SWITCH);

    /* Loop forever blinking the LED */

    while (1) {
        u32 value = XGpio_DiscreteRead(&Gpio_switches, SWITCH_CHANNEL) << 1;
        XGpio_DiscreteWrite(&Gpio_led, LED_CHANNEL, value);

        /* Wait a small amount of time so the LED is visible */
        // value is shifted to the left once
        for (Delay = 0; Delay < LED_DELAY; Delay++);
    }
}
