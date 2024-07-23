#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  result_is_zero(&value_1);
  result_is_zero(&value_2);

  big_decimal big_dec_1 = {0}, big_dec_2 = {0}, big_result = {0};

  int sign_bit_1 = check_sign_bit(value_1),
      sign_bit_2 = check_sign_bit(value_2), sub = 0;

  if (!sign_bit_2 && sign_bit_1) {  // первое отрицательное
    set_bit(&value_1.bits[3], 31, 0);
    sub = 1;
    if (s21_is_greater_or_equal(value_1, value_2)) big_result.sign = 1;

    if (s21_is_less(value_1, value_2)) replace_two_decimal(&value_1, &value_2);
  }

  if (sign_bit_2 && !sign_bit_1) {  // второе отрицательное
    set_bit(&value_2.bits[3], 31, 0);
    sub = 1;
    if (s21_is_greater_or_equal(value_2, value_1)) {
      big_result.sign = 1;
      replace_two_decimal(&value_1, &value_2);
    }
  }
  from_decimal_to_big_decimal(value_1, &big_dec_1);
  from_decimal_to_big_decimal(value_2, &big_dec_2);

  equalizing_exponent_in_the_add_big(&big_dec_1, &big_dec_2, &big_result);

  if (!sub)
    add_big_decimal(big_dec_1, big_dec_2, &big_result);
  else
    sub_big_decimal(big_dec_1, big_dec_2, &big_result);

  int code = 0;
  if (big_decimal_overflow(big_result) || big_result.scale > 28) {
    squeeze_up_of_mantiss_big_decimal(&big_result, 0) == 1 ? code = 1 : 0;
    code = (code == 1) ? ((big_result.sign == 1) ? 2 : 1) : code;
  }

  if (code == 0) from_big_decimal_to_decimal(big_result, result);

  result_is_zero(result);

  return code;
}