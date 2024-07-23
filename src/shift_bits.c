#include "s21_decimal.h"

int shift_bits(s21_decimal *num, int index) {
  if (index < 0 || index > 31) return 0;
  int copy_0, copy_1;

  for (int i = 0; i < index; i++) {
    copy_0 = num->bits[0];
    num->bits[0] <<= 1;
    copy_1 = num->bits[1];
    num->bits[1] <<= 1;
    num->bits[2] <<= 1;

    if (check_bit(copy_0, 31))
      set_bit(&num->bits[1], 0, 1);
    else
      set_bit(&num->bits[1], 0, 0);

    if (check_bit(copy_1, 31))
      set_bit(&num->bits[2], 0, 1);
    else
      set_bit(&num->bits[2], 0, 0);
  }
  return 1;
}

int shift_bits_big_decimal_left(big_decimal *num, int index) {
  int copy_0, copy_1, copy_2, copy_3, copy_4, copy_5;

  for (int i = 0; i < index; i++) {
    copy_0 = num->bytes[0];
    num->bytes[0] <<= 1;

    copy_1 = num->bytes[1];
    num->bytes[1] <<= 1;

    copy_2 = num->bytes[2];
    num->bytes[2] <<= 1;

    copy_3 = num->bytes[3];
    num->bytes[3] <<= 1;

    copy_4 = num->bytes[4];
    num->bytes[4] <<= 1;

    copy_5 = num->bytes[5];
    num->bytes[5] <<= 1;

    num->bytes[6] <<= 1;

    if (check_bit(copy_0, 31))
      set_bit(&num->bytes[1], 0, 1);
    else
      set_bit(&num->bytes[1], 0, 0);

    if (check_bit(copy_1, 31))
      set_bit(&num->bytes[2], 0, 1);
    else
      set_bit(&num->bytes[2], 0, 0);

    if (check_bit(copy_2, 31))
      set_bit(&num->bytes[3], 0, 1);
    else
      set_bit(&num->bytes[3], 0, 0);

    if (check_bit(copy_3, 31))
      set_bit(&num->bytes[4], 0, 1);
    else
      set_bit(&num->bytes[4], 0, 0);

    if (check_bit(copy_4, 31))
      set_bit(&num->bytes[5], 0, 1);
    else
      set_bit(&num->bytes[5], 0, 0);

    if (check_bit(copy_5, 31))
      set_bit(&num->bytes[6], 0, 1);
    else
      set_bit(&num->bytes[6], 0, 0);
  }
  return 1;
}

int shift_bits_big_decimal_rigth(big_decimal *num, int index) {
  int copy_1, copy_2, copy_3, copy_4, copy_5, copy_6;

  for (int i = 0; i < index; i++) {
    num->bytes[0] >>= 1;
    copy_1 = num->bytes[1];

    num->bytes[1] >>= 1;
    copy_2 = num->bytes[2];
    num->bytes[2] >>= 1;
    copy_3 = num->bytes[3];
    num->bytes[3] >>= 1;
    copy_4 = num->bytes[4];
    num->bytes[4] >>= 1;
    copy_5 = num->bytes[5];
    num->bytes[5] >>= 1;

    copy_6 = num->bytes[6];
    num->bytes[6] >>= 1;

    if (check_bit(copy_1, 0))
      set_bit(&num->bytes[0], 31, 1);
    else
      set_bit(&num->bytes[0], 31, 0);

    if (check_bit(copy_2, 0))
      set_bit(&num->bytes[1], 31, 1);
    else
      set_bit(&num->bytes[1], 31, 0);

    if (check_bit(copy_3, 0))
      set_bit(&num->bytes[2], 31, 1);
    else
      set_bit(&num->bytes[2], 31, 0);

    if (check_bit(copy_4, 0))
      set_bit(&num->bytes[3], 31, 1);
    else
      set_bit(&num->bytes[3], 31, 0);

    if (check_bit(copy_5, 0))
      set_bit(&num->bytes[4], 31, 1);
    else
      set_bit(&num->bytes[4], 31, 0);

    if (check_bit(copy_6, 0))
      set_bit(&num->bytes[5], 31, 1);
    else
      set_bit(&num->bytes[5], 31, 0);
  }
  return 1;
}