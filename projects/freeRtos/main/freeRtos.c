#include <stdio.h>
#include "esp_chip_info.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1Handle = NULL;
TaskHandle_t task1Handle2 = NULL;


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
}