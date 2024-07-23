#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_floor_1) {
  s21_decimal val_1 = {1001234, 0, 0, 2147483648}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);

  ck_assert_int_eq(s21_floor(val_1, &result_1), 0);
  ck_assert_int_eq(result_1.bits[0], 101);
  ck_assert_uint_eq(check_sign_bit(result_1), 1);
  //////////////////////////////////////////////////////////
  s21_decimal val_2 = {5678, 0, 0, 0}, result_2 = {0};
  change_the_exponent(&val_2.bits[3], 2);

  ck_assert_int_eq(s21_floor(val_2, &result_2), 0);
  ck_assert_int_eq(result_2.bits[0], 56);
  ck_assert_uint_eq(check_sign_bit(result_2), 0);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal val_1 = {123, 0, 0, 2147483648}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 1);

  ck_assert_int_eq(s21_floor(val_1, &result_1), 0);
  ck_assert_int_eq(result_1.bits[0], 13);
  ck_assert_uint_eq(check_sign_bit(result_1), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_2 = {3777777777, 0, 0, 0}, result_2 = {0};
  change_the_exponent(&val_2.bits[3], 9);

  ck_assert_int_eq(s21_floor(val_2, &result_2), 0);
  ck_assert_int_eq(result_2.bits[0], 3);
  ck_assert_uint_eq(check_sign_bit(result_2), 0);
  ////////////////////////////////////////////////////////////
  s21_decimal val_3 = {4093430568, 3, 0, 2147483648},
              result_3 = {0};  // 16,978,332,456
  change_the_exponent(&val_3.bits[3], 2);

  ck_assert_int_eq(s21_floor(val_3, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], 169783325);
  ck_assert_uint_eq(check_sign_bit(result_3), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_4 = {123456000, 0, 0, 2147483648},
              result_4 = {0};  // 16,978,332,456
  change_the_exponent(&val_4.bits[3], 3);

  ck_assert_int_eq(s21_floor(val_4, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], 123456);
  ck_assert_uint_eq(check_sign_bit(result_4), 1);
}
END_TEST

Suite *floor_suite(void) {
  Suite *suite = suite_create("s21_floor");
  TCase *test_case = tcase_create("case_floor");

  tcase_add_test(test_case, test_s21_floor_1);
  tcase_add_test(test_case, test_s21_floor_2);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = floor_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}