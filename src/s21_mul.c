#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal big_dec_1 = {0}, big_dec_2 = {0}, big_result = {0};

  int sign_bit_1 = check_sign_bit(value_1);
  int sign_bit_2 = check_sign_bit(value_2);

  from_decimal_to_big_decimal(value_1, &big_dec_1);
  from_decimal_to_big_decimal(value_2, &big_dec_2);

  int s1 = check_scaling_factor(value_1);
  int s2 = check_scaling_factor(value_2);

  if ((s1 > 0 || s2 > 0))
    equalizing_exponent_in_the_mul_big(&big_dec_1, &big_dec_2, &big_result);

  for (int k = 0; k < 7; k++) {
    for (int i = 0; i <= 31; i++) {
      int current_bit = check_bit(big_dec_2.bytes[k], i);
      if (current_bit) add_big_decimal(big_result, big_dec_1, &big_result);

      shift_bits_big_decimal_left(&big_dec_1, 1);
    }
  }

  int code = 0;
  if ((sign_bit_1 && !sign_bit_2) || (!sign_bit_1 && sign_bit_2))
    big_result.sign = 1;

  if (big_decimal_overflow(big_result) || big_result.scale > 28) {
    squeeze_up_of_mantiss_big_decimal(&big_result, 0) == 1 ? code = 1 : 0;
    if (code == 1) code = (big_result.sign == 1) ? 2 : 1;
  }

  if (code == 0) from_big_decimal_to_decimal(big_result, result);

  result_is_zero(result);

  return code;
}