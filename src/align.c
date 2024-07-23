#include "s21_decimal.h"

void multiplication_by_ten(s21_decimal *num, int m) {
  unsigned int exp = num->bits[3];
  num->bits[3] = 0;

  for (int i = 0; i < m; i++) {
    s21_decimal copy = *num;
    shift_bits(num, 3);
    shift_bits(&copy, 1);
    s21_add(*num, copy, num);
  }

  num->bits[3] = exp;
}

void result_is_zero(s21_decimal *value) {
  if (value->bits[0] == 0 && value->bits[1] == 0 && value->bits[2] == 0)
    value->bits[3] = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  \    /\     /
///////////////////////////////////////////////////
///////////////////////////////////   BIG DECIMAL
///////////////////////////////////////////////////
///////////////////////////////////  /    \/
///\  ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void equalizing_exponent_in_the_add_big(big_decimal *value_1,
                                        big_decimal *value_2,
                                        big_decimal *result) {
  int sc_fc_1 = value_1->scale;
  int sc_fc_2 = value_2->scale;
  int diff;
  if (value_1->sign && value_2->sign) result->sign = 1;

  if (sc_fc_1 == sc_fc_2) result->scale = sc_fc_2;

  if (sc_fc_1 > sc_fc_2) {
    diff = sc_fc_1 - sc_fc_2;
    result->scale = sc_fc_1;
    value_2->scale = sc_fc_1;
    multiplication_by_ten_big_decimal(value_2, diff);

  } else if (sc_fc_1 < sc_fc_2) {
    diff = sc_fc_2 - sc_fc_1;
    result->scale = sc_fc_2;
    value_2->scale = sc_fc_2;
    multiplication_by_ten_big_decimal(value_1, diff);
  }
}

void equalizing_exponent_in_the_mul_big(big_decimal *value_1,
                                        big_decimal *value_2,
                                        big_decimal *result) {
  int sc_fc_1 = value_1->scale;
  int sc_fc_2 = value_2->scale;

  if (sc_fc_1 == sc_fc_2) result->scale = sc_fc_2 + sc_fc_1;

  if (sc_fc_1 > sc_fc_2) {
    result->scale = sc_fc_1 + sc_fc_2;
    value_2->scale = sc_fc_1;

  } else if (sc_fc_1 < sc_fc_2) {
    result->scale = sc_fc_1 + sc_fc_2;
    value_1->scale = sc_fc_2;
  }
}

void equalizing_exponent_in_the_div_big(big_decimal *value_1,
                                        big_decimal *value_2,
                                        big_decimal *result) {
  multiplication_by_ten_big_decimal(value_1, 36);

  result->scale = 36 + (value_1->scale - value_2->scale);

  value_1->scale = 0;
  value_2->scale = 0;
}