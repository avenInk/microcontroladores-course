#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_http_server.h"
#include "string.h"


#define RED 13
#define GREEN 12


void blink(unsigned int step, unsigned int color){
    ledc_channel_config_t channel_config = {
            .channel = LEDC_CHANNEL_0,
            .duty = 0,
            .gpio_num = color,
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
    ledc_timer_config(&timer_config);
    ledc_channel_config (&channel_config);

    for(unsigned int i = 0; i<step; i++){
        vTaskDelay(100/portTICK_PERIOD_MS);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 1000);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
        vTaskDelay(100/portTICK_PERIOD_MS);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    }
}

static esp_err_t api_holamundo_generator(httpd_req_t *req){
    httpd_resp_send(req , "hola mundo! ", HTTPD_RESP_USE_STRLEN); //req es una petición, y esta línea de código hace una respuesta a esta petición, por eso se pide como parámetro.
    return ESP_OK;
} 

static const httpd_uri_t api = {
    .uri = "/api",
    .method = HTTP_GET,
    .handler = api_holamundo_generator

};

void http_init(){
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    if (httpd_start(&server, &config) == ESP_OK){
        httpd_register_uri_handler(server, &api);
        printf("servidor lanzado. Entra a él desde: ");
        blink(3, RED);
        return;
    }
}

void app_main(){

    esp_err_t err = nvs_flash_init(); 
    
    printf((err == ESP_OK) ? "nvs_flash OK":"nvs_flash ERR" ); 

    esp_netif_init(); 
    esp_event_loop_create_default();

    example_connect(); //iniciamos la red del protocol_example. Para que la interfaz de red esté disponible
    blink(2, GREEN);

    esp_netif_ip_info_t ip_info; //creamos una variable que tendrá información de la ip y más cosas (estructura de datos)

    esp_netif_t *netif = NULL; //creamos la interfaz de red.

    netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    
    if (netif == NULL){
        printf("No se ha iniciado la interfaz correctamente. Codigo: ERR\n");
    }else{
        esp_netif_get_ip_info(netif, &ip_info);
        printf("IP: %d.%d.%d.%d\n", IP2STR(&ip_info.ip));

        http_init();
        printf("%d.%d.%d.%d/api\n", IP2STR(&ip_info.ip));
    }
    

}
