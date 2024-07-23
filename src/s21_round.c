#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  reset_result(result);

  int sign_bit = check_sign_bit(value);
  int scale = check_scaling_factor(value), greater_than_zero = 0;
  set_bit(&value.bits[3], 31, 0);
  change_the_exponent(&value.bits[3], 0);

  s21_decimal rest = {0}, five = {{5, 0, 0, 0}};
  while (scale > 0) {
    division_by_ten_with_reduction(&value, &rest);
    if (scale == 1 && s21_is_greater_or_equal(rest, five))
      greater_than_zero = 1;

    scale--;
  }
  if (greater_than_zero == 1) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_add(value, one, result);

  } else
    replace_two_decimal(&value, result);

  change_the_exponent(&result->bits[3], 0);

  if (sign_bit) set_bit(&result->bits[3], 31, 1);
  result_is_zero(result);
  return 0;
}