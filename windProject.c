#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/dma.h"
#include "hardware/timer.h"

#define PI  3.14159265

//Velocidad
const uint interruptPin = 10;
uint count_holes = 0;
uint count_steps = 0;
const uint holes = 72; //Agujeros del encoder
repeating_timer_t timer;
float radSeg = 0;
float windSpeed = 0;
float radio = 0.09;

void sys_init(void);
void addHole();
void getSpeed();
bool everySecond();

int main()
{   
    sys_init();
    while(true){
        // printf("Velocidad: %f \n", windSpeed);
        // sleep_ms(500);
    };
}

void sys_init(void) {
    //SYS_INIT
    stdio_init_all();

    //GPIOs
    gpio_init(interruptPin);

    //IRQs
    gpio_set_irq_enabled_with_callback(interruptPin, GPIO_IRQ_EDGE_RISE, true, &addHole);

    //Alarmas
    add_repeating_timer_ms(1000, everySecond, NULL, &timer);

    sleep_ms(1500);
}

void addHole(){    
    count_holes += 1;
}

bool everySecond(){
    getSpeed();
}

void getSpeed(){
    radSeg = ((count_holes * 60) / holes)*2*PI/60;
    windSpeed = radSeg * radio;
    printf("Velocidad: %f \n", windSpeed);
    count_holes = 0;
}