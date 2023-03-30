#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"

esp_err_t err;


void init_nvs(void){
    err = nvs_flash_init();
    printf("NVS init!\n");
    printf((err == ESP_OK) ? "done\n":"fail\n");
}

void app_main(void)
{
    printf("start!!\n");
    init_nvs();
    nvs_handle_t mem_par;

    err = nvs_open("part1", NVS_READWRITE, &mem_par);
    printf("NVS_open!\n");
    printf((err == ESP_OK) ? "done\n":"fail\n");

    err = nvs_set_i32(mem_par, "numero", 10);
    printf("Mem write!\n");
    printf((err == ESP_OK) ? "done\n":"fail\n");

    err = nvs_commit(mem_par);
    printf("Mem commit!\n");
    printf((err == ESP_OK) ? "done\n":"fail\n");

    int32_t number; 
    err = nvs_get_i32(mem_par, "numero", &number);
    printf("Value get!\n");
    printf((err == ESP_OK) ? "done\n":"fail\n");

    printf("el valor recuperado es: %ld\n", number);

    nvs_close(mem_par);
}
