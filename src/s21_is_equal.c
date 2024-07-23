#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  big_decimal a_1 = {0}, b_2 = {0};
  int sign_bit_1 = check_sign_bit(value_1);
  int sign_bit_2 = check_sign_bit(value_2);

  if ((sign_bit_1 && !sign_bit_2) || (!sign_bit_1 && sign_bit_2)) return 0;

  from_decimal_to_big_decimal(value_1, &a_1);
  from_decimal_to_big_decimal(value_2, &b_2);
  equalizing_exponent_in_the_comparison_big(&a_1, &b_2);
  int code = 1;

  for (int i = 0; i < 7 && code; i++) {
    if (a_1.bytes[i] != b_2.bytes[i]) code = 0;
  }

  return code;
}