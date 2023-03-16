#include <stdio.h>
#include "pico/stdlib.h"
#include "ResetFromBoot.h"

int main(void)
{  
    stdio_init_all();
    sleep_ms(1000);
    set_sys_clock_khz(210000, true);
    printf("\n\nHello World\n");
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while (true)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(100);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(100);
        check_for_reset();
    }
}
