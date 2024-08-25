#include "HLK_LD2450.h"

HLK_LD2450::HLK_LD2450(Stream *ser) {
  this->ser = ser;
}

void HLK_LD2450::read() {

  byte data = 0;

  while (data != begin_bytes[0])
    if (ser->available() > 0)
      data = ser->read();

  all_datas[0] = data;

  ser->readBytes((char*)(all_datas + 1), ld2450_all_datas_len - 1);

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
