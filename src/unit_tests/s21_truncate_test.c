#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_truncate_1) {
  s21_decimal val_1 = {1001234, 0, 0, 2147483648}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);

  ck_assert_uint_eq(s21_truncate(val_1, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], 100);
  ck_assert_uint_eq(check_sign_bit(result_1), 1);
  ////////////////////////////////////////////////////////
  s21_decimal val_2 = {10, 0, 0, 0}, result_2 = {0};
  change_the_exponent(&val_2.bits[3], 0);

  ck_assert_uint_eq(s21_truncate(val_2, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], 10);
  ck_assert_uint_eq(check_sign_bit(result_2), 0);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal val_1 = {1, 0, 0, 0}, result_1 = {0};

  ck_assert_uint_eq(s21_truncate(val_1, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], 1);
  ck_assert_uint_eq(check_sign_bit(result_1), 0);
  ////////////////////////////////////////////////////////
  s21_decimal val_2 = {3777777777, 0, 0, 0}, result_2 = {0};
  change_the_exponent(&val_2.bits[3], 9);

  ck_assert_uint_eq(s21_truncate(val_2, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], 3);
  ck_assert_uint_eq(check_sign_bit(result_2), 0);
  ////////////////////////////////////////////////////////
  s21_decimal val_3 = {4093430568, 3, 0, 0}, result_3 = {0};  // 16,978,332,456
  change_the_exponent(&val_3.bits[3], 2);

  ck_assert_uint_eq(s21_truncate(val_3, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], 169783324);
  ck_assert_uint_eq(check_sign_bit(result_3), 0);
}
END_TEST

Suite *truncate_suite(void) {
  Suite *suite = suite_create("s21_truncate");
  TCase *test_case = tcase_create("case_truncate");

  tcase_add_test(test_case, test_s21_truncate_1);
  tcase_add_test(test_case, test_s21_truncate_2);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = truncate_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}