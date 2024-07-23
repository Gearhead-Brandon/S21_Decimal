#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_f_f_t_d_pos) {
  s21_decimal result_1 = {0};
  float input_1 = 0.15625;

  ck_assert_int_eq(s21_from_float_to_decimal(input_1, &result_1), 0);
  ck_assert_int_eq(result_1.bits[0], 15625);
  ck_assert_int_eq(check_scaling_factor(result_1), 5);
  ck_assert_int_eq(check_sign_bit(result_1), 0);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_2 = {0};
  float input_2 = -2147483647;

  ck_assert_int_eq(s21_from_float_to_decimal(input_2, &result_2), 0);
  ck_assert_int_eq(result_2.bits[0], 2147484000);
  ck_assert_int_eq(check_scaling_factor(result_2), 0);
  ck_assert_int_eq(check_sign_bit(result_2), 1);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_3 = {0}, original_result_3 = {0};
  from_char_to_decimal("11101110000000101110011010001100000",
                       &original_result_3);
  float input_3 = 31945338371.45;

  ck_assert_int_eq(s21_from_float_to_decimal(input_3, &result_3), 0);
  // print_bin_decimal_2(result_3);
  ck_assert_int_eq(result_3.bits[0], original_result_3.bits[0]);
  ck_assert_int_eq(result_3.bits[1], original_result_3.bits[1]);
  ck_assert_int_eq(result_3.bits[2], original_result_3.bits[2]);
  ck_assert_int_eq(check_scaling_factor(result_3), 0);
  ck_assert_int_eq(check_sign_bit(result_3), 0);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_4 = {0};
  float input_4 = 345.12345;

  ck_assert_int_eq(s21_from_float_to_decimal(input_4, &result_4), 0);

  ck_assert_int_eq(result_4.bits[0], 3451234);
  ck_assert_int_eq(check_scaling_factor(result_4), 4);
  ck_assert_int_eq(check_sign_bit(result_4), 0);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_5 = {0};
  float input_5 = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(input_5, &result_5), 0);
  ck_assert_int_eq(result_5.bits[0], 0);
  ck_assert_int_eq(check_scaling_factor(result_5), 0);
  ck_assert_int_eq(check_sign_bit(result_5), 0);
}
END_TEST

START_TEST(test_s21_f_f_t_d_neg) {
  s21_decimal result_1 = {0};
  float input_1 = -777.777;

  ck_assert_int_eq(s21_from_float_to_decimal(input_1, &result_1), 0);
  ck_assert_int_eq(result_1.bits[0], 777777);
  ck_assert_int_eq(check_scaling_factor(result_1), 3);
  ck_assert_int_eq(check_sign_bit(result_1), 1);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_2 = {0};
  float input_2 = -21474836.48;

  ck_assert_int_eq(s21_from_float_to_decimal(input_2, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], 21474840);
  ck_assert_int_eq(check_scaling_factor(result_2), 0);
  ck_assert_int_eq(check_sign_bit(result_2), 1);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_3 = {0};
  float input_3 = -500561123340.145;
  s21_decimal original_result_0 = {0};
  from_char_to_decimal("111010010001011110001000011110011100000",
                       &original_result_0);

  ck_assert_int_eq(s21_from_float_to_decimal(input_3, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], original_result_0.bits[0]);
  ck_assert_uint_eq(result_3.bits[1], original_result_0.bits[1]);
  ck_assert_uint_eq(result_3.bits[2], original_result_0.bits[2]);
  ck_assert_int_eq(check_scaling_factor(result_3), 0);
  ck_assert_int_eq(check_sign_bit(result_3), 1);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_4 = {0};
  float input_4 = -1234567.8;

  ck_assert_int_eq(s21_from_float_to_decimal(input_4, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], 1234568);
  ck_assert_int_eq(check_scaling_factor(result_4), 0);
  ck_assert_int_eq(check_sign_bit(result_4), 1);
}
END_TEST

START_TEST(test_s21_f_f_t_d_errors) {
  s21_decimal result_1 = {0};
  float input_1 = (1e-29);

  ck_assert_int_eq(s21_from_float_to_decimal(input_1, &result_1), 1);
  ck_assert_int_eq(result_1.bits[0], 0);
  ck_assert_int_eq(check_scaling_factor(result_1), 0);
  ck_assert_int_eq(check_sign_bit(result_1), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal result_2 = {0};
  float input_2 = (1e+29);

  ck_assert_int_eq(s21_from_float_to_decimal(input_2, &result_2), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal result_3 = {0};
  float input_3 = NAN;

  ck_assert_int_eq(s21_from_float_to_decimal(input_3, &result_3), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal *result_4 = NULL;
  float input_4 = NAN;

  ck_assert_int_eq(s21_from_float_to_decimal(input_4, result_4), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal *result_5 = NULL;
  float input_5 = 1e+40;

  ck_assert_int_eq(s21_from_float_to_decimal(input_5, result_5), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal *result_6 = NULL;
  float input_6 = -1e+40;

  ck_assert_int_eq(s21_from_float_to_decimal(input_6, result_6), 1);
}
END_TEST

Suite *from_float_to_decimal_suite(void) {
  Suite *suite = suite_create("s21_from_float_to_decimal");
  TCase *test_case = tcase_create("case_from_float_to_decimal");

  tcase_add_test(test_case, test_s21_f_f_t_d_pos);
  tcase_add_test(test_case, test_s21_f_f_t_d_neg);
  tcase_add_test(test_case, test_s21_f_f_t_d_errors);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = from_float_to_decimal_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}