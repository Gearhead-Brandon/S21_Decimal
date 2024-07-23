#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  reset_result(result);

  if (check_sign_bit(value)) {
    int scale = check_scaling_factor(value), greater_than_zero = 0;
    change_the_exponent(&value.bits[3], 0);
    if (scale > 0) {
      s21_decimal rest = {0}, zero = {0};
      while (scale > 0) {
        division_by_ten_with_reduction(&value, &rest);
        scale--;
        if (s21_is_greater(rest, zero)) {
          greater_than_zero = 1;
        }
      }
    }
    if (greater_than_zero) {
      s21_decimal one = {{1, 0, 0, 0}};
      set_bit(&value.bits[3], 31, 0);
      s21_add(value, one, result);
    } else
      replace_two_decimal(&value, result);

    set_bit(&result->bits[3], 31, 1);
    change_the_exponent(&result->bits[3], 0);
  } else
    return s21_truncate(value, result);

  result_is_zero(result);
  return 0;
}