#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_result(result);
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0)
    return 3;

  int sign_bit_1 = check_sign_bit(value_1);
  int sign_bit_2 = check_sign_bit(value_2);

  big_decimal big_dec_1 = {0}, big_dec_2 = {0}, big_result = {0};

  from_decimal_to_big_decimal(value_1, &big_dec_1);
  from_decimal_to_big_decimal(value_2, &big_dec_2);

  sign_bit_2 == 1 ? big_dec_2.sign = 0 : 0;

  equalizing_exponent_in_the_div_big(&big_dec_1, &big_dec_2, &big_result);

  big_decimal temp = {0};
  char bits[500] = {0};
  int current_bit = 0;
  int begin = 0;
  int j = 0;

  for (int k = 6; k >= 0; k--) {
    for (int i = 31; i >= 0; i--) {
      current_bit = check_bit(big_dec_1.bytes[k], i);

      set_bit(&temp.bytes[0], 0, current_bit);

      if (current_bit || begin) {
        begin = 1;
        if (is_greater_big_decimal(big_dec_2, temp))
          bits[j++] = '0';
        else {
          bits[j++] = '1';
          sub_big_decimal(temp, big_dec_2, &temp);
        }
      }
      shift_bits_big_decimal_left(&temp, 1);
    }
  }

  int code = 0;
  from_char_to_big_decimal(bits, &big_result);

  if (big_decimal_overflow(big_result) || big_result.scale > 28) {
    squeeze_up_of_mantiss_big_decimal(&big_result, 0) == 1 ? code = 1 : 0;
    if (code == 1) code = (sign_bit_1 || sign_bit_2) ? 2 : 1;
  }

  if (code == 0) {
    delete_trailing_zeroes(&big_result);
    from_big_decimal_to_decimal(big_result, result);
  }

  if ((sign_bit_1 && !sign_bit_2) || (!sign_bit_1 && sign_bit_2))
    set_bit(&result->bits[3], 31, 1);

  result_is_zero(result);

  return code;
}