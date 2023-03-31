#include <stdio.h> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"	

int32_t raw_value;

void app_main(void)
{
    adc2_config_channel_atten(ADC2_CHANNEL_5, ADC_ATTEN_DB_0);

    while(1){
        adc2_get_raw(ADC2_CHANNEL_5, ADC_WIDTH_BIT_12, &raw_value);
        printf("Trimpot raw value: %ld\n", raw_value);
        vTaskDelay(400/ portTICK_PERIOD_MS);
    }
}
