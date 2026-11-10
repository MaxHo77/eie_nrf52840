#include <stdbool.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "BTN.h"
#include "LED.h"

int password[3] = {0, 2, 1};
int entered[3];

int password_length = 3;
int position = 0;
bool locked = true;

int main(void)
{
    int i;

    if (BTN_init() < 0) {
        return 0;
    }

    if (LED_init() < 0) {
        return 0;
    }

    LED_set(LED3, LED_ON);

    bool entry_mode = false;

    for (i = 0; i < 300; i++) {
        if (BTN_check_clear_pressed(BTN3)) {
            entry_mode = true;
    }

    k_msleep(10);
}

LED_set(LED3, LED_OFF);

    if (entry_mode) {
        position = 0;

        while (1) {
            if (BTN_check_clear_pressed(BTN0)) {
                if (position < 3) {
                    password[position] = 0;
                    position++;
                }
            }

            if (BTN_check_clear_pressed(BTN1)) {
                if (position < 3) {
                    password[position] = 1;
                    position++;
                }
            }

            if (BTN_check_clear_pressed(BTN2)) {
                if (position < 3) {
                    password[position] = 2;
                    position++;
                }
            }

            if (BTN_check_clear_pressed(BTN3)) {
                password_length = position;
                printk("Password saved!\n");
                break;
            }

            k_msleep(1);
        }
    }

    position = 0;
    locked = true;

    LED_set(LED0, LED_ON);

    while (1) {
        if (locked && BTN_check_clear_pressed(BTN0)) {
            if (position < 3) {
                entered[position] = 0;
                position++;
            }
        }

        if (locked && BTN_check_clear_pressed(BTN1)) {
            if (position < 3) {
                entered[position] = 1;
                position++;
            }
        }

        if (locked && BTN_check_clear_pressed(BTN2)) {
            if (position < 3) {
                entered[position] = 2;
                position++;
            }
        }

        if (locked && BTN_check_clear_pressed(BTN3)) {
            bool correct = true;

            if (position != password_length) {
                correct = false;
            }

            for (i = 0; i < password_length; i++) {
                if (entered[i] != password[i]) {
                    correct = false;
                }
            }

            if (correct == true) {
                printk("Correct!\n");
            }

            if (correct == false) {
                printk("Incorrect!\n");
            }

            LED_set(LED0, LED_OFF);
            locked = false;

            continue;
        }

        if (locked == false &&
            (BTN_check_clear_pressed(BTN0) ||
             BTN_check_clear_pressed(BTN1) ||
             BTN_check_clear_pressed(BTN2) ||
             BTN_check_clear_pressed(BTN3))) {

            position = 0;
            locked = true;

            LED_set(LED0, LED_ON);
        }

        k_msleep(1);
    }

    return 0;
}

