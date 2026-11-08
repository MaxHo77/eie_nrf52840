#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <stdint.h>

#include "BTN.h"
#include "LED.h"

uint8_t counter = 0;



int main(void) {
    if (BTN_init() < 0){
        return 0;
    }

    if (LED_init() < 0){
        return 0;
    }

    while(1) {
        if (BTN_check_clear_pressed (BTN0)) {
            counter++;
        }

        if (counter >= 16){
            counter = 0;
        }

        LED_set(LED0,(counter & (1 << 0)) ? LED_ON : LED_OFF);
        LED_set(LED1,(counter & (1 << 1)) ? LED_ON : LED_OFF);
        LED_set(LED2,(counter & (1 << 2)) ? LED_ON : LED_OFF);
        LED_set(LED3,(counter & (1 << 3)) ? LED_ON : LED_OFF);


        k_msleep(1);

    }

    return 0;
}
