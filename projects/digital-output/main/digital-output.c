#include <stdio.h>
#include "esp_chip_info.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN 5
#define TIME_SHUTDOWN 1000

void app_main(void)
{
    unsigned int pin_mode_up_down = 1;
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    while(1){
        gpio_set_level(LED_PIN, pin_mode_up_down);
        pin_mode_up_down = !pin_mode_up_down;
        vTaskDelay(TIME_SHUTDOWN/ portTICK_PERIOD_MS);
    }
}
