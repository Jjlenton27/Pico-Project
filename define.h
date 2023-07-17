#include "pico/cyw43_arch.h"
#include "hardware/spi.h"

#define LED_PIN CYW43_WL_GPIO_LED_PIN
//#define SET_PIN(pinNum, state) cyw43_arch_gpio_put(pinNum, state);
#define BLINK(state) cyw43_arch_gpio_put(LED_PIN, state);

#define SPI_SPD     4000000     // Screen chip speed
//master (pico) TX -> MOSI wire -> slave RX
//master (pico) RX <- MISO wire <- slave TX

#define SCREEN_X 128
#define SCREEN_Y 128

#define HIGH 1
#define LOW 0

#define BYTE unit8_t
#define COLOR unit16_t
