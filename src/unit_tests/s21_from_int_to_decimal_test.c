#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_f_i_t_d_pos) {
  s21_decimal result_1 = {0};
  int input_1 = 132;

  ck_assert_int_eq(s21_from_int_to_decimal(input_1, &result_1), 0);
  ck_assert_int_eq(result_1.bits[0], input_1);
  ck_assert_int_eq(check_sign_bit(result_1), 0);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_2 = {0};
  int input_2 = 2147483647;

  ck_assert_int_eq(s21_from_int_to_decimal(input_2, &result_2), 0);
  ck_assert_int_eq(result_2.bits[0], input_2);
  ck_assert_int_eq(check_sign_bit(result_2), 0);
}
END_TEST

START_TEST(test_s21_f_i_t_d_neg) {
  s21_decimal result_1 = {0};
  int input_1 = -777777;

  ck_assert_int_eq(s21_from_int_to_decimal(input_1, &result_1), 0);
  ck_assert_int_eq(result_1.bits[0], input_1 * -1);
  ck_assert_int_eq(check_sign_bit(result_1), 1);
  ////////////////////////////////////////////////////////////////////
  s21_decimal result_2 = {0};
  int input_2 = -2147483648;

  ck_assert_int_eq(s21_from_int_to_decimal(input_2, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], 2147483647);
  ck_assert_int_eq(check_sign_bit(result_2), 1);
}
END_TEST

Suite *from_int_to_decimal_suite(void) {
  Suite *suite = suite_create("s21_from_int_to_decimal");
  TCase *test_case = tcase_create("case_from_int_to_decimal");

  tcase_add_test(test_case, test_s21_f_i_t_d_pos);
  tcase_add_test(test_case, test_s21_f_i_t_d_neg);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = from_int_to_decimal_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}