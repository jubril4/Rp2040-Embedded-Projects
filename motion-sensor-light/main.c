#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define PIR_SENSOR_PIN 2  // GPIO pin connected to the PIR sensor output
#define LED_PIN 3        // GPIO pin connected to the LED

int main() {
    // Initialize stdio and GPIOs
    stdio_init_all();
    gpio_init(PIR_SENSOR_PIN);
    gpio_set_dir(PIR_SENSOR_PIN, GPIO_IN);
    gpio_pull_down(PIR_SENSOR_PIN);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    printf("Motion Sensor LED Control\n");

    while (true) {
        // Check if motion detected
        if (gpio_get(PIR_SENSOR_PIN)) {
            printf("Motion detected! LED ON\n");
            gpio_put(LED_PIN, 1);  // Turn on LED
            sleep_ms(10000);       // Keep the LED on for 10 seconds
        } else {
            gpio_put(LED_PIN, 0);  // Turn off LED
        }

        sleep_ms(100);  // Small delay to debounce the sensor
    }

    return 0;
}
