#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_is_less_signs) {
  s21_decimal input_1 = {600, 1, 0, 2147483648};
  s21_decimal input_2 = {600, 2, 0, 0};

  ck_assert_int_eq(s21_is_less(input_1, input_2), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_3 = {600, 1, 0, 0};
  s21_decimal input_4 = {600, 2, 0, 2147483648};

  ck_assert_int_eq(s21_is_less(input_3, input_4), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_5 = {600, 1, 0, 2147483648};
  s21_decimal input_6 = {600, 2, 0, 2147483648};

  ck_assert_int_eq(s21_is_less(input_5, input_6), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_7 = {600, 3, 1, 2147483648};
  s21_decimal input_8 = {600, 2, 0, 2147483648};

  ck_assert_int_eq(s21_is_less(input_7, input_8), 1);
}
END_TEST

START_TEST(test_s21_is_less_whole) {
  s21_decimal input_1 = {600, 1, 0, 0};
  s21_decimal input_2 = {600, 2, 0, 0};

  ck_assert_int_eq(s21_is_less(input_1, input_2), 1);

  ////////////////////////////////////////////////////////////////
  s21_decimal input_3 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  s21_decimal input_4 = {0xffffffff, 0xffffffff, 0xffffffff, 0};

  ck_assert_int_eq(s21_is_less(input_3, input_4), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_5 = {600, 45, 0, 0};
  s21_decimal input_6 = {600, 2, 0, 0};

  ck_assert_int_eq(s21_is_less(input_5, input_6), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_7 = {0xffffffff, 0xffffffff, 4294967294, 0};
  s21_decimal input_8 = {0xffffffff, 0xffffffff, 0xffffffff, 0};

  ck_assert_int_eq(s21_is_less(input_7, input_8), 1);
}
END_TEST

START_TEST(test_s21_is_less_fraction) {
  s21_decimal input_1 = {600, 1, 0, 0};
  change_the_exponent(&input_1.bits[3], 10);
  s21_decimal input_2 = {600, 2, 0, 0};
  change_the_exponent(&input_2.bits[3], 5);

  ck_assert_int_eq(s21_is_less(input_1, input_2), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_3 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_3.bits[3], 27);
  s21_decimal input_4 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_4.bits[3], 27);

  ck_assert_int_eq(s21_is_less(input_3, input_4), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_5 = {600, 45, 0, 0};
  change_the_exponent(&input_5.bits[3], 1);
  s21_decimal input_6 = {600, 2, 0, 0};
  change_the_exponent(&input_6.bits[3], 1);

  ck_assert_int_eq(s21_is_less(input_5, input_6), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_7 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_7.bits[3], 1);
  s21_decimal input_8 = {0xffffffff, 0xffffffff, 4294967294, 0};
  change_the_exponent(&input_8.bits[3], 1);

  ck_assert_int_eq(s21_is_less(input_7, input_8), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_9 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_9.bits[3], 11);
  s21_decimal input_10 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_10.bits[3], 12);

  ck_assert_int_eq(s21_is_less(input_9, input_10), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_11 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_11.bits[3], 12);
  s21_decimal input_12 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_12.bits[3], 11);

  ck_assert_int_eq(s21_is_less(input_11, input_12), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_13 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_13.bits[3], 21);
  s21_decimal input_14 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_14.bits[3], 22);

  ck_assert_int_eq(s21_is_less(input_13, input_14), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal input_15 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_15.bits[3], 8);
  s21_decimal input_16 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_16.bits[3], 7);

  ck_assert_int_eq(s21_is_less(input_15, input_16), 1);
  ////////////////////////////////////////////////////////////////////
  s21_decimal input_17 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_17.bits[3], 1);
  s21_decimal input_18 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_18.bits[3], 27);

  ck_assert_int_eq(s21_is_less(input_17, input_18), 0);
  ////////////////////////////////////////////////////////////////////
  s21_decimal input_19 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_19.bits[3], 8);
  s21_decimal input_20 = {0xffffffff, 0xffffffff, 0xffffffff, 0};
  change_the_exponent(&input_20.bits[3], 27);

  ck_assert_int_eq(s21_is_less(input_19, input_20), 0);
}
END_TEST

Suite *is_less_suite(void) {
  Suite *suite = suite_create("s21_is_less");
  TCase *test_case = tcase_create("case_is_less");

  tcase_add_test(test_case, test_s21_is_less_signs);
  tcase_add_test(test_case, test_s21_is_less_whole);
  tcase_add_test(test_case, test_s21_is_less_fraction);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = is_less_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}