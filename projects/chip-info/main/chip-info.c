#include <stdio.h>
#include "esp_chip_info.h"

void app_main(void)
{
    esp_chip_info_t chip;
    esp_chip_info(&chip);
    printf("Esta placa tiene un procesador %s, con %d cores\n", 
    CONFIG_IDF_TARGET, chip.cores);

}
