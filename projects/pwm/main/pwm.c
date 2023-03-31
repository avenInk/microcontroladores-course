#include <stdio.h> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/adc.h"	

#define LEDC_TIMER LEDC_TIMER_0// Timer que usarémos
#define LEDC_MODE LEDC_HIGH_SPEED_MODE // Modo de velocidad
#define LEDC_OUTPUT 5 // Pin de salida
#define LEDC_CHANNEL LEDC_CHANNEL_0 // Canal de control
#define LEDC_DUTY_RES LEDC_TIMER_12_BIT // Resolución en bits
#define LEDC_FREQUENCY 5000 // Frecuencia de funcionamiento
#define LEDC_DUTY 0 // Valor inicial
#define LEDC_HPOINT 0 // Ajuste de fase


int32_t raw_value;



void app_main(void)
{
    ledc_timer_config_t ledc_config = {
        .timer_num = LEDC_TIMER,
        .speed_mode = LEDC_MODE,
        .freq_hz = 5000, 
        .
    }
    adc2_config_channel_atten(ADC2_CHANNEL_5, ADC_ATTEN_DB_0);

    while(1){
        adc2_get_raw(ADC2_CHANNEL_5, ADC_WIDTH_BIT_12, &raw_value);
        printf("Trimpot raw value: %ld\n", raw_value);
        vTaskDelay(400/ portTICK_PERIOD_MS);
    }
}
