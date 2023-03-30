#include <stdio.h>
#include "esp_chip_info.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

TaskHandle_t task1Handle = NULL;
TaskHandle_t task1Handle2 = NULL;
TaskHandle_t led_modeHandle = NULL;

void task1(void *arg){
    unsigned int counter = 0;
    while(1){
        printf("Tarea 1, felicidades, count: %d\n", counter);
        counter++;
        if(counter == 5){
            printf("tarea 2 suspendida\n");
            vTaskSuspend(task1Handle2);
        }
        if (counter == 10){
            printf("tarea 2 reanudada\n");
            vTaskResume(task1Handle2);
        }
        if (counter == 15){
            printf("tarea 2 eliminada\n");
            vTaskDelete(task1Handle2);
        }
        if (counter == 15){
            printf("tarea 1 finalizada\n");
            vTaskDelete(NULL);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}


void Led_loop(void *arg){
    while(1){
        esp_rom_gpio_pad_select_gpio(5);
        gpio_set_direction(5, GPIO_MODE_OUTPUT);
        gpio_set_level(5, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(5, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}


void task2(void *arg){
    unsigned int counter = 0;
    while(1){
        printf("Tarea 2, felicidades, count: %d\n", counter);
        counter++;
        if (counter>15){
            printf("tarea 2 finalizada\n");
            
            vTaskDelete(NULL);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}


void app_main(void)
{
    xTaskCreatePinnedToCore(task1, "task1", 4096, NULL, 10, &task1Handle, 0);
    xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 10, &task1Handle2, 1);
    vTaskDelay(2000/ portTICK_PERIOD_MS);
    xTaskCreatePinnedToCore(Led_loop, "task3", 4096, NULL, 9, &led_modeHandle, 0);
}