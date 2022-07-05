#include <stdio.h>
#include "pciprop.h/stdio.h"
#include "hardware/adc.h"
#include <math.h>

int main () {
    float raux = 10000;
    float r0 = 10000;
    float temp0 = 298;
    float beta = 3950;
    float vcc = 3.3;

    adc_init();
    adc_gpio_init(27);
    adc_select_input(1);

    while(1) {

        float vntc = adc_read() * (vcc / 4096);
        float rntc = raux / ((vcc / vntc) - 1);
        float tempK = (beta * temp0) / (temp0 * log(rntc / r0) + beta);
        float tempC = tempK - 273.15;

        printf("La tensión es de: %.2f", vntc, "V\n");
        printf("La temperatura es de: %.2f", tempC, "ºC\n");
        printf("La resistencia es de: %.2f", rntc, "Ohms\n");

        sleep_ms(1000);
    }
}