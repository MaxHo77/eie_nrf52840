#include <stdbool.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <stdint.h>

#include "BTN.h"
#include "LED.h"

int password[3] = {0,2,1};

int entered[3];

int position = 0;
bool locked = true;

int i;



int main(void) {
    if(BTN_init() < 0){
        return 0;
    }

    if (LED_init() < 0){
        return 0;
    }
LED_set(LED0,LED_ON);

while(1) {
    if(locked && BTN_check_clear_pressed(BTN0)){
        if (position < 3) {
            entered[position] =  0;
            position++;
        }
    }

    if (locked && BTN_check_clear_pressed(BTN1)){
        if (position < 3) {
            entered[position] = 1;
            position++;
        }
    }

    if (locked && BTN_check_clear_pressed(BTN2)){
        if (position < 3){
            entered[position] = 2;
            position++;
        }
            
    }

    if(locked && BTN_check_clear_pressed(BTN3)){
        
        bool correct = true;



        if (position != 3){
            correct = false;
        }
        
        for(i=0; i<3; i++){
            if (entered[i] != password[i])
            correct = false;
        }
    

    if (correct == false){
        printk("Incorrect!\n");
    }

    if (correct == true){
        printk("Correct!\n");
    }

    LED_set(LED0,LED_OFF);
    locked = false;
    continue;


    
}

if (locked == false && (
    BTN_check_clear_pressed(BTN0) ||
    BTN_check_clear_pressed(BTN1) ||
    BTN_check_clear_pressed(BTN2) ||
    BTN_check_clear_pressed(BTN3) 
)){ locked = true;
    position = 0;
    LED_set(LED0, LED_ON);

}

        
}

}


