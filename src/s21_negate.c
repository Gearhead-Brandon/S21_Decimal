#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  replace_two_decimal(&value, result);
  check_sign_bit(*result) == 1 ? set_bit(&result->bits[3], 31, 0)
                               : set_bit(&result->bits[3], 31, 1);
  return 0;
}