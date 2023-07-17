#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico/cyw43_arch.h"


#define MISO 3 // DIN data line
#define CS 5   // comms open low, comms closed high
#define SCLK 2 // CLK
#define MOSI 6 //

#define DC 8    // command low, data high
#define RST 9   //

#define SPI_PORT spi0

void SendCommand(uint8_t cmd){
  //set to command
  gpio_put(DC, 0);
  //open commas
  gpio_put(CS,0);

  uint8_t msg[1];
  msg[0] = cmd;

  spi_write_blocking(SPI_PORT, msg, 1);
  gpio_put(CS,1);
}

void SendData(uint8_t data){
  //set to command
  gpio_put(DC, 1);
  //open commas
  gpio_put(CS,0);

  uint8_t msg[1];
  msg[0] = data;

  spi_write_blocking(SPI_PORT, msg, 1);
  gpio_put(CS,1);
}

void SendPixel(int X, int Y, uint8_t color){
  SendCommand(0x15);  // Set column address
  SendData(X);
  SendData(X);

  SendCommand(0x75);  // Set row address
  SendData(Y);
  SendData(Y);

  SendCommand(0x5c);  // Write RAM
  SendData(color);
}

int main(){
  stdio_init_all(); //Intialise I/O for USB Serial
  cyw43_arch_init();
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

  spi_init(SPI_PORT, 40000); //Intialise (spi port) at (speed Hz)

  //Configure GPIO pins for SPI
  gpio_set_function(MISO, GPIO_FUNC_SPI);
  gpio_set_function(SCLK, GPIO_FUNC_SPI);
  gpio_set_function(MOSI, GPIO_FUNC_SPI);

  //Configure Chip Select
  gpio_init(CS); //Initialise CS pin
  gpio_set_dir(CS, GPIO_OUT); //Set CS pin as output
  gpio_put(CS, 0); //Set CS high to close SPI communication

  //Configure DC pin
  gpio_init(DC);
  gpio_set_dir(DC, GPIO_OUT);
  gpio_put(DC, 1);

  //Configure RST pins
  gpio_init(RST);
  gpio_set_dir(RST, GPIO_OUT);

  //Reset display
  gpio_put(RST, 1);
  sleep_ms(100);
  gpio_put(RST, 0);
  sleep_ms(100);
  gpio_put(RST, 1);

  gpio_put(DC, 0);

  //Initialisation commands
  SendCommand(0xfd);  // Command lock
  SendData(0x12);     // Allow commands
  SendCommand(0xfd);  // Command lock
  SendData(0xb1);     // Command A2,B1,B3,BB,BE,C1 unlocked

  SendCommand(0xae);  //Sleep mode on, display off
  SendCommand(0xa4);  //Display mode all off

  SendCommand(0x15);  // Set column address
  SendData(0x00);
  SendData(0x7f);

  SendCommand(0x75);  // Set row address
  SendData(0x00);
  SendData(0x7f);

  SendCommand(0xb3); // Front clock divider / oscillator frequency
  SendData(0xf1);

  SendCommand(0xca);  // Set MUX ratio
  SendData(0x7f);

  SendCommand(0xa0);  // Set remap / color depth
  SendData(0x74);

  SendCommand(0xa1);  // Set display start line
  SendData(0x00);

  SendCommand(0xa2);  // Set display offset
  SendData(0x00);

  SendCommand(0xab);  // Function selection
  SendData(0x01);     // 16-bit parallel interface

  SendCommand(0xb4);  // Set segment low voltage
  SendData(0xa0);
  SendData(0xb5);
  SendData(0x55);

  SendCommand(0xc1);  // Set contrast for current color
  SendData(0xc8);
  SendData(0x80);
  SendData(0xc0);

  SendCommand(0xc7);  // Master contrast current control
  SendData(0x0f);     // No change

  SendCommand(0xb1);  // Set reset (Phase 1) / Pre-charge (Phase 2) period
  SendData(0x32);     // Phase 1, 3 = 7 display clock ticks Phase 2, 2 = invalid

  SendCommand(0xb2);  // Display enhancement
  SendData(0xa4);     // Enhancement
  SendData(0x00);     // Display
  SendData(0x00);     // Performance

  SendCommand(0xbb);  // Set pre-charge voltage
  SendData(0x17);

  SendCommand(0xb6);  // Set second precharge period
  SendData(0x01);     // 1 display ticks

  SendCommand(0xa6);
  //End initialisation

  sleep_ms(200);

  SendCommand(0xa6);  // Reset to normal display
  //Init done

  SendPixel(5, 5, 0xff);
}


//int main(){
//  stdio_init_all();
//  cyw43_arch_init();
//  while(true){
//    BLINK(LOW);
//    sleep_ms(250);
//    BLINK(HIGH);
//    sleep_ms(250);
//  }
//  return 0;
//}
