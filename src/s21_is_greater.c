#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int sign_bit_1 = check_sign_bit(value_1);
  int sign_bit_2 = check_sign_bit(value_2);

  if (sign_bit_1 && !sign_bit_2)
    return 0;
  else if (!sign_bit_1 && sign_bit_2)
    return 1;
  int n = 0, m = 1;
  if (sign_bit_1 && sign_bit_2) {
    n = 1;
    m = 0;
  }
  big_decimal a_1 = {0}, b_2 = {0};
  from_decimal_to_big_decimal(value_1, &a_1);
  from_decimal_to_big_decimal(value_2, &b_2);

  equalizing_exponent_in_the_comparison_big(&a_1, &b_2);

  for (int k = 6; k >= 0; k--) {
    if (a_1.bytes[k] > b_2.bytes[k])
      return m;  // 1;
    else if (a_1.bytes[k] < b_2.bytes[k])
      return n;  // 0;
  }

  return 0;  // n;  // 0
}
