#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int code = 0;
  if (dst == NULL) {
    code = 1;
  } else {
    *dst = 0;
    long double tmp = 0;
    int exp = 0, current_bit;

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 32; j++) {
        current_bit = check_bit(src.bits[i], j);
        if (current_bit) tmp += pow(2, j + (32 * i));
      }
    }

    if ((exp = check_scaling_factor(src)) > 0) {
      for (int i = exp; i > 0; i--, tmp /= 10.0)
        ;
    }

    *dst = (float)tmp;
    if (check_sign_bit(src)) *dst *= -1;
  }
  return code;
}