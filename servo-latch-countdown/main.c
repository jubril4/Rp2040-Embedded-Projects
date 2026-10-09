#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#define BUTTON_PIN 2
#define SERVO_PIN 3
#define DISPLAY_PINS {4, 5, 6, 7} // Example pins for the BCD-to-seven-segment decoder

// Servo PWM values for open and close positions
#define SERVO_OPEN_PWM 1000
#define SERVO_CLOSE_PWM 2000

bool latchOpen = false;
bool countdownActive = false;

void setup() {
    // Initialize stdio
    stdio_init_all();
    
    // Initialize button pin
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    
    // Initialize servo PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_wrap(slice_num, 20000);
    pwm_set_enabled(slice_num, true);
    
    // Initialize display pins (assuming a simple direct connection for demonstration)
    for (int i = 0; i < 4; i++) {
        gpio_init(DISPLAY_PINS[i]);
        gpio_set_dir(DISPLAY_PINS[i], GPIO_OUT);
    }
    
    // Start with the latch closed
    pwm_set_gpio_level(SERVO_PIN, SERVO_CLOSE_PWM);
}

void displayCountdown(int seconds) {
    for (int i = seconds; i >= 0; i--) {
        // Update the display with the current countdown value
        // This is a placeholder: Actual implementation will depend on your display setup
        printf("Countdown: %d\n", i);
        
        sleep_ms(1000);
        
        // Check if button is pressed during countdown
        if (!gpio_get(BUTTON_PIN)) {
            countdownActive = false;
            return; // Cancel countdown
        }
    }
}

void toggleLatch() {
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    
    if (latchOpen) {
        pwm_set_gpio_level(SERVO_PIN, SERVO_CLOSE_PWM);
        latchOpen = false;
    } else {
        pwm_set_gpio_level(SERVO_PIN, SERVO_OPEN_PWM);
        latchOpen = true;
    }
}

int main() {
    setup();
    
    while (true) {
        // Wait for button press
        if (!gpio_get(BUTTON_PIN)) {
            if (!countdownActive) {
                countdownActive = true;
                displayCountdown(5);
                if (countdownActive) { // Proceed if countdown wasn't canceled
                    toggleLatch();
                }
                countdownActive = false;
            }
        }
        sleep_ms(100); // Simple debouncing
    }
    
    return 0;
}
