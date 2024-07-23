#include "s21_decimal.h"

int add_big_decimal(big_decimal value_1, big_decimal value_2,
                    big_decimal *result) {
  int one_in_mind = 0, bit1 = 0, bit2 = 0;

  for (int k = 0; k < 7; k++) {
    for (int i = 0; i < 32; i++) {
      bit1 = check_bit(value_1.bytes[k], i);
      bit2 = check_bit(value_2.bytes[k], i);

      if (bit1 + bit2 == 1) {
        set_bit(&result->bytes[k], i, one_in_mind ? 0 : 1);

      } else if (bit1 + bit2 == 0) {
        one_in_mind == 1    ? set_bit(&result->bytes[k], i, 1),
            one_in_mind = 0 : set_bit(&result->bytes[k], i, 0);

      } else if (bit1 + bit2 == 2) {
        set_bit(&result->bytes[k], i, one_in_mind ? 1 : 0);
        one_in_mind = 1;
      }
    }
  }

  return 0;
}

int sub_big_decimal(big_decimal value_1, big_decimal value_2,
                    big_decimal *result) {
  int minus_one_in_mind = 0;

  for (int k = 0; k < 7; k++) {
    for (int i = 0; i < 32; i++) {
      int bit1 = check_bit(value_1.bytes[k], i);
      int bit2 = check_bit(value_2.bytes[k], i);

      if (bit1 - bit2 == 0) {
        set_bit(&result->bytes[k], i, minus_one_in_mind ? 1 : 0);

      } else if (bit1 - bit2 == 1) {
        minus_one_in_mind == 1    ? set_bit(&result->bytes[k], i, 0),
            minus_one_in_mind = 0 : set_bit(&result->bytes[k], i, 1);

      } else if (bit1 - bit2 == -1) {
        set_bit(&result->bytes[k], i, minus_one_in_mind ? 0 : 1);
        minus_one_in_mind = 1;
      }
    }
  }
  return 0;
}

int division_by_ten_with_reduction_big_decimal(big_decimal *value_1,
                                               big_decimal *rest) {
  big_decimal value_2 = {{10, 0, 0, 0, 0, 0, 0}, 0, 0};
  big_decimal temp = {0};

  char bits[400] = {0};
  int current_bit = 0;
  int begin = 0;
  int j = 0;

  for (int k = 6; k >= 0; k--) {
    for (int i = 31; i >= 0; i--) {
      current_bit = check_bit(value_1->bytes[k], i);

      set_bit(&temp.bytes[0], 0, current_bit);

      if (current_bit || begin) {
        begin = 1;
        if (is_greater_big_decimal(value_2, temp))
          bits[j++] = '0';
        else {
          bits[j++] = '1';
          sub_big_decimal(temp, value_2, &temp);
        }
      }
      shift_bits_big_decimal_left(&temp, 1);
    }
  }
  from_char_to_big_decimal(bits, value_1);
  shift_bits_big_decimal_rigth(&temp, 1);
  rest->bytes[0] = temp.bytes[0];

  return 0;
}

void from_char_to_big_decimal(char *arr, big_decimal *num) {
  int j = strlen(arr) - 1;
  for (int k = 0; k < 7; k++) {
    for (int i = 0; i < 32; i++) {
      set_bit(&num->bytes[k], i, arr[j--] - '0');
      if (j == -1) break;
    }
    if (j == -1) break;
  }
}

void multiplication_by_ten_big_decimal(big_decimal *num, int m) {
  for (int i = 0; i < m; i++) {
    big_decimal copy = *num;

    shift_bits_big_decimal_left(num, 3);
    shift_bits_big_decimal_left(&copy, 1);
    add_big_decimal(*num, copy, num);
  }
}

int squeeze_up_of_mantiss_big_decimal(big_decimal *value, int div) {
  big_decimal one = {{1, 0, 0, 0, 0, 0, 0}, 0, 0};
  int round = 0, banking = 0, rest_n = 0;

  while ((value->scale > 0 && big_decimal_overflow(*value)) ||
         value->scale > 28) {
    big_decimal rest = {0};

    division_by_ten_with_reduction_big_decimal(value, &rest);

    if (!big_decimal_overflow(*value)) rest_n = 1;

    if (value->scale > 1 && rest.bytes[0] > 0) {
      round = 2;
      banking = 0;
    }

    if ((value->scale == 1 || rest_n) && rest.bytes[0] >= 6) round = 2;

    if ((value->scale == 1 || rest_n) && round == 0 &&
        check_bit(value->bytes[0], 0) == 1 && rest.bytes[0] == 5)
      banking = 1;

    if ((rest_n || value->scale == 0) && rest.bytes[0] < 5) round = 0;

    value->scale--;
  }

  if ((round == 2 || banking == 1) && !div) add_big_decimal(*value, one, value);

  return big_decimal_overflow(*value) ? 1 : 0;
}

void delete_trailing_zeroes(big_decimal *value) {
  int n = 20;
  big_decimal temp = {0};

  for (int i = 0; i < 7; i++) temp.bytes[i] = value->bytes[i];

  while (value->scale > 0) {
    big_decimal rest = {0};
    division_by_ten_with_reduction_big_decimal(&temp, &rest);
    if (rest.bytes[0] == 0)
      division_by_ten_with_reduction_big_decimal(value, &rest);
    else
      break;
    value->scale--;
    n++;
  }
}

int big_decimal_overflow(big_decimal value) {
  return (value.bytes[3] > 0 || value.bytes[4] > 0 || value.bytes[5] > 0 ||
          value.bytes[6] > 0);
}

int is_greater_big_decimal(big_decimal value_1, big_decimal value_2) {
  int sign_bit_1 = value_1.sign;
  int sign_bit_2 = value_2.sign;

  if (sign_bit_1 && !sign_bit_2)
    return 0;
  else if (!sign_bit_1 && sign_bit_2)
    return 1;
  int n = 0, m = 1;
  if (sign_bit_1 && sign_bit_2) {
    n = 1;
    m = 0;
  }
  equalizing_exponent_in_the_comparison_big(&value_1, &value_2);

  for (int k = 6; k >= 0; k--) {
    if (value_1.bytes[k] > value_2.bytes[k])
      return m;  // 1;
    else if (value_1.bytes[k] < value_2.bytes[k])
      return n;  // 0;
  }

  return 0;  // n;  // 0
}

void equalizing_exponent_in_the_comparison_big(big_decimal *value_1,
                                               big_decimal *value_2) {
  int sc_fc_1 = value_1->scale;
  int sc_fc_2 = value_2->scale;
  int diff;
  if (sc_fc_1 > sc_fc_2) {
    diff = sc_fc_1 - sc_fc_2;
    value_2->scale = sc_fc_1;
    multiplication_by_ten_big_decimal(value_2, diff);
  }
  if (sc_fc_1 < sc_fc_2) {
    diff = sc_fc_2 - sc_fc_1;
    value_1->scale = sc_fc_2;
    multiplication_by_ten_big_decimal(value_1, diff);
  }
}