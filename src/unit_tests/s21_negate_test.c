#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_negate_pos) {
  s21_decimal val_1 = {1, 0, 0, 0}, result = {0};

  ck_assert_int_eq(s21_negate(val_1, &result), 0);
  ck_assert_uint_eq(check_sign_bit(result), 1);
}
END_TEST

START_TEST(test_s21_negate_neg) {
  s21_decimal val_1 = {1, 0, 0, 2147483648}, result = {0};

  ck_assert_int_eq(s21_negate(val_1, &result), 0);
  ck_assert_uint_eq(check_sign_bit(result), 0);
}
END_TEST

Suite *negate_suite(void) {
  Suite *suite = suite_create("s21_negate");
  TCase *test_case = tcase_create("case_negate");

  tcase_add_test(test_case, test_s21_negate_pos);
  tcase_add_test(test_case, test_s21_negate_neg);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = negate_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}