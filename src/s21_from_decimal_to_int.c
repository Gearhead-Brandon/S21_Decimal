#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (check_scaling_factor(src) > 0) s21_truncate(src, &src);

  if (src.bits[1] > 0 || src.bits[2] > 0 || check_bit(src.bits[0], 31) ||
      dst == NULL)
    return 1;

  *dst = src.bits[0];

  if (check_sign_bit(src)) *dst = -*dst;

  return 0;
}