#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_is_not_equal_sign) {
  s21_decimal val_1 = {1, 0, 0, 2147483648}, val_2 = {1, 0, 0, 0};

  ck_assert_int_eq(s21_is_not_equal(val_1, val_2), 1);
  ////////////////////////////////////////////////////////
  s21_decimal val_3 = {1, 0, 0, 0}, val_4 = {1, 0, 0, 2147483648};

  ck_assert_int_eq(s21_is_not_equal(val_3, val_4), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_whole) {
  s21_decimal val_1 = {1, 0, 0, 2147483648}, val_2 = {1, 0, 0, 2147483648};

  ck_assert_int_eq(s21_is_not_equal(val_1, val_2), 0);
  ////////////////////////////////////////////////////////
  s21_decimal val_3 = {0xffffffff, 0xffffffff, 1, 0};
  s21_decimal val_4 = {0xffffffff, 0xffffffff, 1, 0};

  ck_assert_int_eq(s21_is_not_equal(val_3, val_4), 0);
  ////////////////////////////////////////////////////////
  s21_decimal val_5 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  s21_decimal val_6 = {1, 0, 0, 0};

  ck_assert_int_eq(s21_is_not_equal(val_5, val_6), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_fraction) {
  s21_decimal val_1 = {5667894, 0, 0, 0};
  change_the_exponent(&val_1.bits[3], 7);
  s21_decimal val_2 = {1, 0, 0, 0};
  change_the_exponent(&val_2.bits[3], 7);

  ck_assert_int_eq(s21_is_not_equal(val_1, val_2), 1);
  ////////////////////////////////////////////////////////
  s21_decimal val_3 = {0xffffffff, 0xffffffff, 1, 0};
  change_the_exponent(&val_3.bits[3], 10);
  s21_decimal val_4 = {0xffffffff, 0xffffffff, 1, 0};
  change_the_exponent(&val_4.bits[3], 10);

  ck_assert_int_eq(s21_is_not_equal(val_3, val_4), 0);
  ////////////////////////////////////////////////////////
  s21_decimal val_5 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&val_5.bits[3], 20);
  s21_decimal val_6 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&val_6.bits[3], 19);

  ck_assert_int_eq(s21_is_not_equal(val_5, val_6), 1);
}
END_TEST

Suite *is_not_equal_suite(void) {
  Suite *suite = suite_create("s21_is_not_equal");
  TCase *test_case = tcase_create("case_is_not_equal");

  tcase_add_test(test_case, test_s21_is_not_equal_sign);
  tcase_add_test(test_case, test_s21_is_not_equal_whole);
  tcase_add_test(test_case, test_s21_is_not_equal_fraction);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = is_not_equal_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}