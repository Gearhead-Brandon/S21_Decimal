#include "s21_decimal.h"

void replace_two_decimal(s21_decimal *value_1, s21_decimal *value_2) {
  for (int i = 0; i < 4; i++) {
    int temp = value_1->bits[i];
    value_1->bits[i] = value_2->bits[i];
    value_2->bits[i] = temp;
  }
}

void from_char_to_decimal(char *arr, s21_decimal *num) {
  int sign_bit = check_sign_bit(*num);
  int scale = check_scaling_factor(*num);
  reset_result(num);

  int j = strlen(arr) - 1;

  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < 32; i++) {
      set_bit(&num->bits[k], i, arr[j--] - '0');
      if (j == -1) break;
    }
    if (j == -1) break;
  }
  set_bit(&num->bits[3], 31, sign_bit);
  change_the_exponent(&num->bits[3], scale);
}

void from_decimal_to_big_decimal(s21_decimal value_1, big_decimal *value_2) {
  value_2->bytes[0] = value_1.bits[0];
  value_2->bytes[1] = value_1.bits[1];
  value_2->bytes[2] = value_1.bits[2];
  value_2->scale = check_scaling_factor(value_1);
  value_2->sign = check_sign_bit(value_1);
}

void from_big_decimal_to_decimal(big_decimal value_1, s21_decimal *value_2) {
  value_2->bits[0] = value_1.bytes[0];
  value_2->bits[1] = value_1.bytes[1];
  value_2->bits[2] = value_1.bytes[2];
  value_2->bits[3] = 0;
  change_the_exponent(&value_2->bits[3], value_1.scale);
  if (value_1.sign) set_bit(&value_2->bits[3], 31, 1);
}

int check_bit(unsigned int num, int index) {
  return ((num >> index) & 1) == 1 ? 1 : 0;
}

int check_sign_bit(s21_decimal value) {
  return ((value.bits[3] >> 31) & 1) == 1 ? 1 : 0;
}

int check_scaling_factor(s21_decimal value) {
  return (value.bits[3] << 1) >> 17;
}

void change_the_exponent(unsigned int *num, int change) {
  *num = (((*num >> 24) << 8) + change) << 16;
}

void set_bit(unsigned int *num, int index, int bit) {
  if (bit) {
    *num |= 1 << index;
  } else
    *num &= ~(1 << index);
}

void reset_result(s21_decimal *num) {
  num->bits[0] = 0;
  num->bits[1] = 0;
  num->bits[2] = 0;
  num->bits[3] = 0;
}

int division_by_ten_with_reduction(s21_decimal *value_1, s21_decimal *rest) {
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal temp = {0};

  char bits[128] = {0};
  int current_bit = 0, begin = 0;
  int j = 0;
  for (int k = 2; k >= 0; k--) {
    for (int i = 31; i >= 0; i--) {
      current_bit = check_bit(value_1->bits[k], i);

      set_bit(&temp.bits[0], 0, current_bit);

      if (current_bit || begin) {
        begin = 1;
        if (s21_is_greater(value_2, temp))
          bits[j++] = '0';
        else {
          bits[j++] = '1';
          s21_sub(temp, value_2, &temp);
        }
        shift_bits(&temp, 1);
      }
    }
  }
  from_char_to_decimal(bits, value_1);
  temp.bits[0] >>= 1;
  rest->bits[0] = temp.bits[0];
  return 0;
}