#include "HLK_LD2450.h"

#ifndef ESP32

#ifndef _BOARD_GENERIC_STM32F103C_H_

HLK_LD2450::HLK_LD2450(SoftwareSerial *ssUart) {
  is_soft = true;
  with_pins = false;
  with_ser = true;
  SS = ssUart;
}

#endif

#else

HLK_LD2450::HLK_LD2450(EspSoftwareSerial::UART *ssEspUart) {
  is_soft = true;
  with_pins = false;
  with_ser = true;
  SS = ssEspUart;
}

HLK_LD2450::HLK_LD2450(uint8_t rx, uint8_t tx, EspSoftwareSerial::UART *ssEspUart) {
  is_soft = true;
  with_pins = true;
  with_ser = true;
  rx_pin = rx;
  tx_pin = tx;
  SS = ssEspUart;
}

HLK_LD2450::HLK_LD2450(uint8_t rx, uint8_t tx, HardwareSerial *hsUart) {
  is_soft = false;
  with_pins = true;
  with_ser = true;
  rx_pin = rx;
  tx_pin = tx;
  HS = hsUart;
}

#endif

HLK_LD2450::HLK_LD2450(HardwareSerial *hsUart) {
  is_soft = false;
  with_pins = false;
  with_ser = true;
  HS = hsUart;
}

HLK_LD2450::HLK_LD2450(uint8_t rx, uint8_t tx) {
  is_soft = true;
  with_pins = true;
  with_ser = false;
  rx_pin = rx;
  tx_pin = tx;
}

void HLK_LD2450::begin() {

#ifndef ESP32

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {
    if (not with_pins)
      SS->begin(HLK_LD2450_BAUD);
    else {
      SoftwareSerial ssUart(rx_pin, tx_pin);
      SS = &ssUart;
      SS->begin(HLK_LD2450_BAUD);
    }
  }

#endif

  if (not is_soft)
    HS->begin(HLK_LD2450_BAUD);

#else

  if (is_soft) {
    if (not with_pins)
      SS->begin(HLK_LD2450_BAUD);
    else {
      if (with_ser)
        SS->begin(HLK_LD2450_BAUD, EspSoftwareSerial::SWSERIAL_8N1, rx_pin, tx_pin);
      else {
        EspSoftwareSerial::UART ssUart(rx_pin, tx_pin);
        SS = &ssUart;
        SS->begin(HLK_LD2450_BAUD);
      }
    }
  }

  else {
    if (not with_pins)
      HS->begin(HLK_LD2450_BAUD);
    else
      HS->begin(HLK_LD2450_BAUD, SERIAL_8N1, rx_pin, tx_pin);
  }

#endif

  for (int i = 0; i < ld2450_begin_bytes_len; i++) {
    begin_bytes_sum += begin_bytes[i] * (1 << 8 * i); // 1 << 8 * i
  }
  for (int i = 0; i < ld2450_end_bytes_len; i++) {
    end_bytes_sum += end_bytes[i] * (1 << 8 * i);
  }
}

void HLK_LD2450::read() {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    byte data = 0;

    while (data != begin_bytes[0])
      if (SS->available() > 0)
        data = SS->read();

    all_datas[0] = data;

    SS->readBytes((char*)(all_datas + 1), ld2450_all_datas_len - 1);

    uint32_t begin_bytes_sum_calc;
    uint16_t end_bytes_sum_calc;

    memcpy(&begin_bytes_sum_calc, all_datas, ld2450_begin_bytes_len);
    memcpy(&end_bytes_sum_calc, all_datas + ld2450_begin_bytes_len + ld2450_values_len + ld2450_trash_vals_len, ld2450_end_bytes_len);

    if (begin_bytes_sum_calc == begin_bytes_sum and end_bytes_sum_calc == end_bytes_sum) {
      ld2450_data.target_x = -(all_datas[ld2450_begin_bytes_len] + all_datas[ld2450_begin_bytes_len + 1] * 0x100);
      ld2450_data.target_y = (all_datas[ld2450_begin_bytes_len + 2] + all_datas[ld2450_begin_bytes_len + 3] * 0x100) - (1 << 15);
      ld2450_data.speed = -(all_datas[ld2450_begin_bytes_len + 4] + all_datas[ld2450_begin_bytes_len + 5] * 0x100);
      ld2450_data.distance_resolution = all_datas[ld2450_begin_bytes_len + 6] + all_datas[ld2450_begin_bytes_len + 7] * 0x100;
    }
  }

#endif

  if(not is_soft) {

    byte data = 0;

    while (data != begin_bytes[0])
      if (HS->available() > 0)
        data = HS->read();

    all_datas[0] = data;

    HS->readBytes(all_datas + 1, ld2450_all_datas_len - 1);

    uint32_t begin_bytes_sum_calc;
    uint16_t end_bytes_sum_calc;

    memcpy(&begin_bytes_sum_calc, all_datas, ld2450_begin_bytes_len);
    memcpy(&end_bytes_sum_calc, all_datas + ld2450_begin_bytes_len + ld2450_values_len + ld2450_trash_vals_len, ld2450_end_bytes_len);

    if (begin_bytes_sum_calc == begin_bytes_sum and end_bytes_sum_calc == end_bytes_sum) {
      ld2450_data.target_x = -(all_datas[ld2450_begin_bytes_len] + all_datas[ld2450_begin_bytes_len + 1] * 0x100);
      ld2450_data.target_y = (all_datas[ld2450_begin_bytes_len + 2] + all_datas[ld2450_begin_bytes_len + 3] * 0x100) - (1 << 15);
      ld2450_data.speed = -(all_datas[ld2450_begin_bytes_len + 4] + all_datas[ld2450_begin_bytes_len + 5] * 0x100);
      ld2450_data.distance_resolution = all_datas[ld2450_begin_bytes_len + 6] + all_datas[ld2450_begin_bytes_len + 7] * 0x100;
    }
  }
}

int16_t HLK_LD2450::getTargetX() {
  return ld2450_data.target_x;
}

int16_t HLK_LD2450::getTargetY() {
  return ld2450_data.target_y;
}

int16_t HLK_LD2450::getSpeed() {
  return ld2450_data.speed;
}

uint16_t HLK_LD2450::getDistanceResolution() {
  return ld2450_data.distance_resolution;
}
