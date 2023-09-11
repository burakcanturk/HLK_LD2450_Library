#ifndef _HLK_LD2450_
#define _HLK_LD2450_

#define HLK_LD2450_BAUD 256000

#define ld2450_begin_bytes_len 4
#define ld2450_end_bytes_len 2

#define ld2450_values_len 8

#define ld2450_trash_vals_len 16

#define ld2450_all_datas_len 30

#include <Arduino.h>
#ifndef _BOARD_GENERIC_STM32F103C_H_
#include <SoftwareSerial.h>
#endif

class HLK_LD2450 {

  public:
#ifndef ESP32
#ifndef _BOARD_GENERIC_STM32F103C_H_
    HLK_LD2450(SoftwareSerial *ssUart);
#endif
#else
    HLK_LD2450(EspSoftwareSerial::UART *ssEspUart);
    HLK_LD2450(uint8_t rx, uint8_t tx, EspSoftwareSerial::UART *ssEspUart);
    HLK_LD2450(uint8_t rx, uint8_t tx, HardwareSerial *hsUart);
#endif
    HLK_LD2450(HardwareSerial *hsUart);
    HLK_LD2450(uint8_t rx, uint8_t tx);
    void begin();
    void read();
    int16_t getTargetX();
    int16_t getTargetY();
    int16_t getSpeed();
    uint16_t getDistanceResolution();

  private:

    bool is_soft;

#ifndef ESP32
#ifndef _BOARD_GENERIC_STM32F103C_H_
    SoftwareSerial *SS;
#endif
#else
    EspSoftwareSerial::UART *SS;
#endif
    HardwareSerial *HS;

    bool with_pins;
    bool with_ser;

    uint16_t rx_pin;
    uint16_t tx_pin;

    const byte begin_bytes_len = 4;
    const byte end_bytes_len = 2;

    byte begin_bytes[ld2450_begin_bytes_len] = {0xAA, 0xFF, 0x03, 0x00};
    byte end_bytes[ld2450_end_bytes_len] = {0x55, 0xCC};

    uint32_t begin_bytes_sum = 0;
    uint16_t end_bytes_sum = 0;

    byte all_datas[ld2450_all_datas_len];

    struct ld2450_datas {
      int16_t target_x;
      int16_t target_y;
      int16_t speed;
      uint16_t distance_resolution;
    } ld2450_data;
};

#endif
