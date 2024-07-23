#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_f_d_t_f_pos) {
  s21_decimal result_1 = {15625, 0, 0, 0};
  change_the_exponent(&result_1.bits[3], 5);
  float input_1 = 0;

  ck_assert_int_eq(s21_from_decimal_to_float(result_1, &input_1), 0);
  ck_assert_float_eq(input_1, 0.15625);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_2 = {25275, 0, 0, 0};
  change_the_exponent(&result_2.bits[3], 2);
  float input_2 = 0;
  ck_assert_int_eq(s21_from_decimal_to_float(result_2, &input_2), 0);
  ck_assert_float_eq(input_2, 252.75);

  ////////////////////////////////////////////////////////////////////
  s21_decimal result_3 = {10001625, 0, 0, 0};
  change_the_exponent(&result_3.bits[3], 4);
  float input_3 = 0;

  ck_assert_int_eq(s21_from_decimal_to_float(result_3, &input_3), 0);
  ck_assert_float_eq_tol(input_3, 1000.1625, 0.0001);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_4 = {1000000, 0, 0, 0};
  change_the_exponent(&result_4.bits[3], 1);
  float input_4 = 0;

  ck_assert_int_eq(s21_from_decimal_to_float(result_4, &input_4), 0);
  ck_assert_float_eq(input_4, 100000.0);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_5 = {1234555, 0, 0, 0};
  change_the_exponent(&result_5.bits[3], 3);
  float input_5 = 0;
  ;

  ck_assert_int_eq(s21_from_decimal_to_float(result_5, &input_5), 0);
  ck_assert_float_eq_tol(input_5, 1234.555, 0.001);
}
END_TEST

START_TEST(test_s21_f_d_t_f_neg) {
  s21_decimal result_1 = {152152, 0, 0, 0};
  change_the_exponent(&result_1.bits[3], 6);
  float input_1 = 0;

  ck_assert_int_eq(s21_from_decimal_to_float(result_1, &input_1), 0);
  ck_assert_float_eq_tol(input_1, 0.152152, 0.000001);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_2 = {75, 0, 0, 0};
  change_the_exponent(&result_2.bits[3], 8);
  float input_2 = 0;

  ck_assert_int_eq(s21_from_decimal_to_float(result_2, &input_2), 0);
  ck_assert_float_eq_tol(input_2, 0.00000075, 0.00000001);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_3 = {13137, 0, 0, 2147483648};
  change_the_exponent(&result_3.bits[3], 4);
  float input_3 = 0;

  ck_assert_int_eq(s21_from_decimal_to_float(result_3, &input_3), 0);
  ck_assert_float_eq_tol(input_3, -1.3137, 0.0001);
}
END_TEST

START_TEST(test_s21_f_d_t_f_errors) {
  s21_decimal result_1 = {1, 0, 0, 0};
  change_the_exponent(&result_1.bits[3], 30);
  float input_1 = 0;

  ck_assert_int_eq(s21_from_decimal_to_float(result_1, &input_1), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal result_2 = {232232, 0, 0, 0};
  change_the_exponent(&result_2.bits[3], 3);
  float input_2 = 0;

  ck_assert_int_eq(s21_from_decimal_to_float(result_2, &input_2), 0);
  ck_assert_float_eq_tol(input_2, 232.232, 0.001);
  ////////////////////////////////////////////////////////////////
  s21_decimal result_3 = {232232625, 0, 0, 0};
  change_the_exponent(&result_3.bits[3], 3);
  float input_3 = 0;

  ck_assert_int_eq(s21_from_decimal_to_float(result_3, &input_3), 0);
  ck_assert_float_eq_tol(input_3, 232232.625, 0.001);
  ////////////////////////////////////////////////////////////////
  s21_decimal result_4 = {23223, 0, 0, 0};
  change_the_exponent(&result_4.bits[3], 3);
  float *input_4 = NULL;

  ck_assert_int_eq(s21_from_decimal_to_float(result_4, input_4), 1);
}
END_TEST

Suite *from_float_to_decimal_suite(void) {
  Suite *suite = suite_create("s21_from_decimal_to_float");
  TCase *test_case = tcase_create("case_from_decimal_to_float");

  tcase_add_test(test_case, test_s21_f_d_t_f_pos);
  tcase_add_test(test_case, test_s21_f_d_t_f_neg);
  tcase_add_test(test_case, test_s21_f_d_t_f_errors);

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