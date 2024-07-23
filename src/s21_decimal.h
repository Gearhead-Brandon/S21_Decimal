#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_INFINITY (1.0f / 0.0f)
#define S21_NEGATIVE_INFINITY (-1.0f / 0.0f)

#define s21_is_inf(x) (x == S21_INFINITY || x == S21_NEGATIVE_INFINITY)

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bytes[7];
  unsigned int scale;
  unsigned int sign;
} big_decimal;

// arifthmetic

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// another arifthmetic

void multiplication_by_ten(s21_decimal *num, int m);

void multiplication_by_ten_big_decimal(big_decimal *num, int m);

int add_big_decimal(big_decimal value_1, big_decimal value_2,
                    big_decimal *result);

int sub_big_decimal(big_decimal value_1, big_decimal value_2,
                    big_decimal *result);

int division_by_ten_with_reduction(s21_decimal *value_1, s21_decimal *rest);

int division_by_ten_with_reduction_big_decimal(big_decimal *value_1,
                                               big_decimal *rest);

void replace_two_decimal(s21_decimal *value_1, s21_decimal *value_2);

void from_char_to_decimal(char *arr, s21_decimal *num);

void from_char_to_big_decimal(char *arr, big_decimal *num);

void from_decimal_to_big_decimal(s21_decimal value_1, big_decimal *value_2);

void from_big_decimal_to_decimal(big_decimal value_1, s21_decimal *value_2);

// equalizing

void equalizing_exponent_in_the_add_big(big_decimal *value_1,
                                        big_decimal *value_2,
                                        big_decimal *result);

void equalizing_exponent_in_the_mul_big(big_decimal *value_1,
                                        big_decimal *value_2,
                                        big_decimal *result);

void equalizing_exponent_in_the_div_big(big_decimal *value_1,
                                        big_decimal *value_2,
                                        big_decimal *result);

void equalizing_exponent_in_the_comparison_big(big_decimal *value_1,
                                               big_decimal *value_2);

// comparison

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);

int s21_is_not_equal(s21_decimal a, s21_decimal b);

int s21_is_greater(s21_decimal value_1, s21_decimal value_2);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// another comparison

int is_greater_big_decimal(big_decimal value_1, big_decimal value_2);

// convertors

int s21_from_int_to_decimal(int src, s21_decimal *dst);

int s21_from_float_to_decimal(float src, s21_decimal *dst);

int s21_from_decimal_to_int(s21_decimal src, int *dst);

int s21_from_decimal_to_float(s21_decimal src, float *dst);

// bits, sign, scale

int shift_bits(s21_decimal *num, int index);

int shift_bits_big_decimal_left(big_decimal *num, int index);

int shift_bits_big_decimal_rigth(big_decimal *num, int index);

int check_bit(unsigned int num, int index);

void set_bit(unsigned int *num, int index, int bit);

int check_sign_bit(s21_decimal value);

int check_scaling_factor(s21_decimal value);

void change_the_exponent(unsigned int *num, int change);

int big_decimal_overflow(big_decimal value);

int squeeze_up_of_mantiss_big_decimal(big_decimal *value, int div);

void delete_trailing_zeroes(big_decimal *value);

void result_is_zero(s21_decimal *value);

void reset_result(s21_decimal *num);

// another

int s21_floor(s21_decimal value, s21_decimal *result);

int s21_round(s21_decimal value, s21_decimal *result);

int s21_truncate(s21_decimal value, s21_decimal *result);

int s21_negate(s21_decimal value, s21_decimal *result);

#endif