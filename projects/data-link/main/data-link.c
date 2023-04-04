#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

ledc_channel_config_t channel_config = {
        .channel = LEDC_CHANNEL_0,
        .duty = 0,
        .gpio_num = 5,
        .hpoint = 0,
        .intr_type = LEDC_INTR_DISABLE,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_sel = LEDC_TIMER_0
    };
ledc_timer_config_t timer_config = {
        .clk_cfg = LEDC_AUTO_CLK,
        .duty_resolution = LEDC_TIMER_12_BIT,
        .freq_hz = 5000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0
    };

void blink(unsigned int step){
    for(unsigned int i = 0; i<step; i++){
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 100);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
        vTaskDelay(100/portTICK_PERIOD_MS);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}


void app_main(){
    ledc_timer_config(&timer_config);
    ledc_channel_config (&channel_config);
    esp_err_t err = nvs_flash_init(); //iniciando el nvs para guardar credenciales
    
    printf((err == ESP_OK) ? "nvs_flash OK":"nvs_flash ERR" ); //comprobar que se inicie bien el nvs

    esp_netif_init(); //creamos la interfaz de red para que corra en protocol_example
    esp_event_loop_create_default(); //evenloop para la red de protocol_example

    example_connect(); //iniciamos la red del protocol_example. Para que la interfaz de red esté disponible
    blink(2);

    esp_netif_ip_info_t ip_info; //creamos una variable que tendrá información de la ip y más cosas (estructura de datos)

    esp_netif_t *netif = NULL; //creamos la interfaz de red.

    netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF"); //obtenemos la interfaz de red en el modo en el que le dijimos, para usar una conexión estandar en staging
    
    if (netif == NULL){
        printf("No se ha iniciado la interfaz correctamente. Codigo: ERR\n");
    }else{
        esp_netif_get_ip_info(netif, &ip_info);
        printf("IP: %d.%d.%d.%d\n", IP2STR(&ip_info.ip));
    }
    

}
