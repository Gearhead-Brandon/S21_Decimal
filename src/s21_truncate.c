#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  reset_result(result);
  int scale = check_scaling_factor(value);
  int sign_bit = check_sign_bit(value);

  s21_decimal rest = {0};

  while (scale > 0) {
    division_by_ten_with_reduction(&value, &rest);
    scale--;
  }

  replace_two_decimal(&value, result);
  set_bit(&result->bits[3], 31, sign_bit);
  result_is_zero(result);
  return 0;
}