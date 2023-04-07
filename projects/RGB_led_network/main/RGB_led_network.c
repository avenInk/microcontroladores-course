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

#define channel_0 LEDC_CHANNEL_0
#define channel_1 LEDC_CHANNEL_1
#define channel_2 LEDC_CHANNEL_2

#define LEDC_COLOR_R LEDC_CHANNEL_0
#define LEDC_COLOR_G LEDC_CHANNEL_1
#define LEDC_COLOR_B LEDC_CHANNEL_2

#define COLOR1 13
#define COLOR2 12
#define COLOR3 14
int COLOR[3] = {COLOR1, COLOR2, COLOR3};

int32_t ledc_r, ledc_g, ledc_b = 0;


void ledc_colors_url_update(){
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_COLOR_R, ledc_r);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_COLOR_R);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_COLOR_G, ledc_g);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_COLOR_G);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_COLOR_B, ledc_b);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_COLOR_B);
}

static esp_err_t api_holamundo_generator(httpd_req_t *req){
    
    char *buf;
    size_t len_buf;

    len_buf = httpd_req_get_url_query_len(req) + 1; //Metemos el tamaño del query en la url dentro de una variable len_buf
    if(len_buf > 1){ //si hay un query en el url (len_buf > 1 ) entonces hacemos lo siguiente:
        buf = malloc(len_buf); //reservamos el mamaño del query en buf para agregar la información a continuación:
        if(httpd_req_get_url_query_str(req, buf, len_buf) == ESP_OK){; // tomamos el query del url en el req (respuesta) y lo metemos en buf, le pasamos ademas el tamaño
            char param[4];//un char para guardar 255 a 0 como str
            if(httpd_query_key_value(buf, "r", param, sizeof(param)) == ESP_OK){ // Tomamos el query y buscamos la clave 'r' y lo guardamos en param
                ledc_r = atoi(param);
                printf("take query, value: R = %ld\n", ledc_r);
            }
            if(httpd_query_key_value(buf, "g", param, sizeof(param)) == ESP_OK){ 
                ledc_g = atoi(param);
                printf("take query, value: G = %ld\n", ledc_g);
            }
            if(httpd_query_key_value(buf, "b", param, sizeof(param)) == ESP_OK){ 
                ledc_b = atoi(param);
                printf("take query, value: B = %ld\n\n", ledc_b);
            }
        }
        free(buf); //liberamos la memoria que habíamos reservado para el buf con malloc
    }

    ledc_colors_url_update();

    httpd_resp_set_hdr(req, "Content-Type", "application/json"); // Creamos el header para que el navegador lea res como un json

    char res[32];
    sprintf(res, "{\"R\": %ld,\"G\": %ld,\"B\": %ld}",ledc_r, ledc_g, ledc_b );
    httpd_resp_send(req , res, HTTPD_RESP_USE_STRLEN); //req es una petición, y esta línea de código hace una respuesta a esta petición, por eso se pide como parámetro.
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
        return;
    }
}

ledc_channel_t channel_[3] = {LEDC_CHANNEL_0, LEDC_CHANNEL_1, LEDC_CHANNEL_2};

ledc_channel_config_t channel[3];
void app_main(){
        ledc_timer_config_t timer1 = {
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 5000, 
        .speed_mode = LEDC_HIGH_SPEED_MODE
    };
    ledc_timer_config(&timer1);

    for(int i = 0; i<3; i++){
        channel[i] = (ledc_channel_config_t){
            .channel = channel_[i],
            .duty = 0,
            .gpio_num = COLOR[i],
            .hpoint = 0,
            .intr_type = LEDC_INTR_DISABLE,
            .speed_mode = LEDC_HIGH_SPEED_MODE,
            .timer_sel = LEDC_TIMER_0
        };
        ledc_channel_config(&channel[i]);
    }



    esp_err_t err = nvs_flash_init(); 
    
    printf((err == ESP_OK) ? "nvs_flash OK\n":"nvs_flash ERR\n" ); 

    esp_netif_init(); 
    esp_event_loop_create_default();

    example_connect(); //iniciamos la red del protocol_example. Para que la interfaz de red esté disponible


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
