#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_f_d_t_i_pos) {
  int result_1;
  s21_decimal input_1 = {600, 0, 0, 0};

  ck_assert_int_eq(s21_from_decimal_to_int(input_1, &result_1), 0);
  ck_assert_int_eq(result_1, input_1.bits[0]);
  ck_assert_int_eq(result_1 >= 0, 1);
  ////////////////////////////////////////////////////////////////
  int result_2 = {0};
  s21_decimal input_2 = {2147483647, 0, 0, 0};

  ck_assert_int_eq(s21_from_decimal_to_int(input_2, &result_2), 0);
  ck_assert_int_eq(result_2, input_2.bits[0]);
  ck_assert_int_eq(result_2 >= 0, 1);
  ////////////////////////////////////////////////////////////////
  int result_3 = {0};
  s21_decimal input_3 = {999, 0, 0, 0};
  change_the_exponent(&input_3.bits[3], 2);

  ck_assert_int_eq(s21_from_decimal_to_int(input_3, &result_3), 0);
  ck_assert_int_eq(result_3, input_3.bits[0] / 100);
  ck_assert_int_eq(result_3 >= 0, 1);
}
END_TEST

START_TEST(test_s21_f_d_t_i_neg) {
  int result_1;
  s21_decimal input_1 = {164745, 0, 0, 2147483648};

  ck_assert_int_eq(s21_from_decimal_to_int(input_1, &result_1), 0);
  ck_assert_int_eq(-result_1, input_1.bits[0]);
  ck_assert_int_eq(result_1 < 0, 1);
  ////////////////////////////////////////////////////////////////////
  int result_2 = {0};
  s21_decimal input_2 = {2147483647, 0, 0, 2147483648};

  ck_assert_int_eq(s21_from_decimal_to_int(input_2, &result_2), 0);
  ck_assert_uint_eq(-result_2, input_2.bits[0]);
  ck_assert_int_eq(result_2 < 0, 1);
  ////////////////////////////////////////////////////////////////////
  int result_3 = 0;
  s21_decimal input_3 = {{885678, 0, 0, 2147483648}};
  change_the_exponent(&input_3.bits[3], 3);

  ck_assert_int_eq(s21_from_decimal_to_int(input_3, &result_3), 0);
  ck_assert_int_eq(-result_3, 885);
  ck_assert_int_eq(result_3 < 0, 1);
}
END_TEST

START_TEST(test_s21_f_d_t_i_errors) {
  int result_1 = 0;
  s21_decimal input_1 = {600, 1, 0, 0};

  ck_assert_int_eq(s21_from_decimal_to_int(input_1, &result_1), 1);
  ck_assert_int_eq(result_1, 0);
  ////////////////////////////////////////////////////////////////////
  int result_2 = {0};
  s21_decimal input_2 = {1, 1, 1, 0};

  ck_assert_int_eq(s21_from_decimal_to_int(input_2, &result_2), 1);
  ck_assert_int_eq(result_2, 0);
  ////////////////////////////////////////////////////////////////////
  int result_3 = {0};
  s21_decimal input_3 = {4147483648, 0, 0, 2147483648};
  change_the_exponent(&input_3.bits[3], 2);

  ck_assert_int_eq(s21_from_decimal_to_int(input_3, &result_3), 0);
  ck_assert_int_eq(-result_3, input_3.bits[0] / 100);
  ck_assert_int_eq(result_3 < 0, 1);
  ////////////////////////////////////////////////////////////////////
  int *result_4 = NULL;
  s21_decimal input_4 = {414, 0, 0, 0};

  ck_assert_int_eq(s21_from_decimal_to_int(input_4, result_4), 1);
}
END_TEST

Suite *from_decimal_to_int_suite(void) {
  Suite *suite = suite_create("s21_from_decimal_to_int");
  TCase *test_case = tcase_create("case_from_decimal_to_int");

  tcase_add_test(test_case, test_s21_f_d_t_i_pos);
  tcase_add_test(test_case, test_s21_f_d_t_i_neg);
  tcase_add_test(test_case, test_s21_f_d_t_i_errors);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = from_decimal_to_int_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);

  return failures == 0 ? 0 : 1;
}