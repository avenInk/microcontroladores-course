#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN 5
#define BUTTON_PIN 27

void app_main(void)
{
    unsigned int pin_mode_up_down = 0;

    gpio_reset_pin(LED_PIN);
    gpio_reset_pin(BUTTON_PIN);

    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_set_level(LED_PIN, pin_mode_up_down); //Pone el led apagado, en caso de estar encendido

    while(1){
        if (gpio_get_level(BUTTON_PIN) == 1){
        pin_mode_up_down = !pin_mode_up_down;
        gpio_set_level(LED_PIN, pin_mode_up_down);
        vTaskDelay(500/portTICK_PERIOD_MS);
        }
    }
}
