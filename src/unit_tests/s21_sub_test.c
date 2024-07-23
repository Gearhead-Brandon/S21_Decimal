#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_sub_1) {
  s21_decimal val_1 = {1001234, 0, 0, 2147483648}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);
  s21_decimal val_2 = {1001000, 0, 0, 2147483648};
  change_the_exponent(&val_2.bits[3], 4);
  // -100.1234 - -100.1000 = -0.0234
  ck_assert_uint_eq(s21_sub(val_1, val_2, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], 234);
  ck_assert_uint_eq(check_scaling_factor(result_1), 4);
  ck_assert_uint_eq(check_sign_bit(result_1), 1);
  //////////////////////////////////////////////////////////////
  s21_decimal val_3 = {1, 0, 0, 0}, result_2 = {0};
  s21_decimal val_4 = {2, 0, 0, 0};
  // 1 - 2 = -1
  ck_assert_uint_eq(s21_sub(val_3, val_4, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], 1);
  ck_assert_uint_eq(check_scaling_factor(result_2), 0);
  ck_assert_uint_eq(check_sign_bit(result_2), 1);
  //////////////////////////////////////////////////////////
  s21_decimal val_5 = {1, 0, 0, 2147483648}, result_3 = {0};
  s21_decimal val_6 = {2, 0, 0, 0};
  // -1 - 2 = -1
  ck_assert_uint_eq(s21_sub(val_5, val_6, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], 3);
  ck_assert_uint_eq(check_scaling_factor(result_3), 0);
  ck_assert_uint_eq(check_sign_bit(result_3), 1);
  //////////////////////////////////////////////////////////////
  s21_decimal val_7 = {1, 0, 0, 2147483648}, result_4 = {0};
  s21_decimal val_8 = {1, 0, 0, 0};
  // -1 - 1 = -2
  ck_assert_uint_eq(s21_sub(val_7, val_8, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], 2);
  ck_assert_uint_eq(check_scaling_factor(result_4), 0);
  ck_assert_uint_eq(check_sign_bit(result_4), 1);
  //////////////////////////////////////////////////////////////
  s21_decimal val_9 = {1000000000, 0, 0, 0}, result_5 = {0};
  s21_decimal val_10 = {3000000000, 0, 0, 0};
  // 1000000000 - 3000000000 = -2000000000
  ck_assert_uint_eq(s21_sub(val_9, val_10, &result_5), 0);
  ck_assert_uint_eq(result_5.bits[0], 2000000000);
  ck_assert_uint_eq(check_scaling_factor(result_5), 0);
  ck_assert_uint_eq(check_sign_bit(result_5), 1);
  //////////////////////////////////////////////////////////
  s21_decimal val_11 = {18, 0, 0, 2147483648}, result_6 = {0};
  s21_decimal val_12 = {35, 0, 0, 2147483648};
  // -18 - -35 = +17
  ck_assert_uint_eq(s21_sub(val_11, val_12, &result_6), 0);
  ck_assert_uint_eq(result_6.bits[0], 17);
  ck_assert_uint_eq(check_scaling_factor(result_6), 0);
  ck_assert_uint_eq(check_sign_bit(result_6), 0);
}
END_TEST

START_TEST(test_s21_sub_first_neg) {
  s21_decimal val_1 = {567812, 0, 0, 2147483648}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);
  s21_decimal val_2 = {1001000, 0, 0, 0};
  change_the_exponent(&val_2.bits[3], 6);
  // -56.7812 - 1.001000 = -57,782200 | Scale = 6
  ck_assert_uint_eq(s21_sub(val_1, val_2, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], 57782200);
  ck_assert_uint_eq(check_scaling_factor(result_1), 6);
  ck_assert_uint_eq(check_sign_bit(result_1), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_3 = {556789, 0, 0, 2147483648}, result_2 = {0};
  change_the_exponent(&val_3.bits[3], 4);
  s21_decimal val_4 = {99345671, 0, 0, 0};
  change_the_exponent(&val_4.bits[3], 3);
  // -55.6789 - 99345.671 = -99401.3499 | Scale = 4
  ck_assert_uint_eq(s21_sub(val_3, val_4, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], 994013499);
  ck_assert_uint_eq(check_scaling_factor(result_2), 4);
  ck_assert_uint_eq(check_sign_bit(result_2), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_5 = {1287231, 0, 0, 2147483648}, result_3 = {0};
  change_the_exponent(&val_5.bits[3], 2);
  s21_decimal val_6 = {1789901, 0, 0, 0};
  change_the_exponent(&val_6.bits[3], 3);
  // -12872.31 - 1789.901 = -14662,211 | Scale = 3
  ck_assert_uint_eq(s21_sub(val_5, val_6, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], 14662211);
  ck_assert_uint_eq(check_scaling_factor(result_3), 3);
  ck_assert_uint_eq(check_sign_bit(result_3), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_7 = {123432, 0, 0, 2147483648}, result_4 = {0};
  change_the_exponent(&val_7.bits[3], 2);
  s21_decimal val_8 = {500356912, 0, 0, 0};
  change_the_exponent(&val_8.bits[3], 3);
  //-1234.32 - 500356.912 = -501591.232 | Scale = 3
  ck_assert_uint_eq(s21_sub(val_7, val_8, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], 501591232);
  ck_assert_uint_eq(check_scaling_factor(result_4), 3);
  ck_assert_uint_eq(check_sign_bit(result_4), 1);
}
END_TEST

START_TEST(test_s21_sub_second_neg) {
  s21_decimal val_ = {5678, 0, 0, 0}, result_0 = {0};
  change_the_exponent(&val_.bits[3], 2);
  s21_decimal val_0 = {1001000, 0, 0, 2147483648};
  change_the_exponent(&val_0.bits[3], 4);
  // 56.78 - -100.1000 = +156.8800 | Scale = 4
  ck_assert_uint_eq(s21_sub(val_, val_0, &result_0), 0);
  ck_assert_uint_eq(result_0.bits[0], 1568800);
  ck_assert_uint_eq(check_scaling_factor(result_0), 4);
  ck_assert_uint_eq(check_sign_bit(result_0), 0);
  ////////////////////////////////////////////////////////////
  s21_decimal val_1 = {567812, 0, 0, 0}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);
  s21_decimal val_2 = {1001000, 0, 0, 2147483648};
  change_the_exponent(&val_2.bits[3], 6);
  // 56.7812 - -1.001000 = +57.782200 | Scale = 6
  ck_assert_uint_eq(s21_sub(val_1, val_2, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], 57782200);
  ck_assert_uint_eq(check_scaling_factor(result_1), 6);
  ck_assert_uint_eq(check_sign_bit(result_1), 0);
  ////////////////////////////////////////////////////////////
  s21_decimal val_3 = {556789, 0, 0, 0}, result_2 = {0};
  change_the_exponent(&val_3.bits[3], 4);
  s21_decimal val_4 = {99345671, 0, 0, 2147483648};
  change_the_exponent(&val_4.bits[3], 3);
  // 55.6789 - -99345.671 = +99401.3499 | Scale = 4
  ck_assert_uint_eq(s21_sub(val_3, val_4, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], 994013499);
  ck_assert_uint_eq(check_scaling_factor(result_2), 4);
  ck_assert_uint_eq(check_sign_bit(result_2), 0);
  ////////////////////////////////////////////////////////////
  s21_decimal val_5 = {8589741, 0, 0, 0}, result_3 = {0};
  change_the_exponent(&val_5.bits[3], 2);
  s21_decimal val_6 = {1789901, 0, 0, 2147483648};
  change_the_exponent(&val_6.bits[3], 3);
  // 85897.41 - -1789.901 = +87687.311 | Scale = 3
  ck_assert_uint_eq(s21_sub(val_5, val_6, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], 87687311);
  ck_assert_uint_eq(check_scaling_factor(result_3), 3);
  ck_assert_uint_eq(check_sign_bit(result_3), 0);
}
END_TEST

START_TEST(test_s21_sub_over_1_byte) {
  s21_decimal val_1 = {0}, result_0 = {0};
  from_char_to_decimal("1111010100110111111101101010100010", &val_1);
  change_the_exponent(&val_1.bits[3], 0);

  s21_decimal val_2 = {0};
  from_char_to_decimal("11110000011101001010110111001001", &val_2);
  change_the_exponent(&val_2.bits[3], 0);

  s21_decimal original_result_0 = {0};
  from_char_to_decimal("1011100100011010110010110011011001",
                       &original_result_0);

  // 16456342178 - 4034178505 = +12422163673 | Scale = 0
  ck_assert_uint_eq(s21_sub(val_1, val_2, &result_0), 0);
  ck_assert_uint_eq(result_0.bits[0], original_result_0.bits[0]);
  ck_assert_uint_eq(result_0.bits[1], original_result_0.bits[1]);
  ck_assert_uint_eq(result_0.bits[2], original_result_0.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_0), 0);
  ck_assert_uint_eq(check_sign_bit(result_0), 0);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_3 = {0}, result_1 = {0};
  from_char_to_decimal(
      "1111111111111111111111111111111111111111111111111111111111111111",
      &val_3);
  change_the_exponent(&val_3.bits[3], 0);

  s21_decimal val_4 = {0};
  from_char_to_decimal(
      "11100001000111000001110100101010101000111011000010011001001010011",
      &val_4);
  change_the_exponent(&val_4.bits[3], 0);

  s21_decimal original_result_1 = {0};
  from_char_to_decimal(
      "1100001000111000001110100101010101000111011000010011001001010100",
      &original_result_1);

  // 18446744073709551615 - 32441744053707551315 = -13994999979997999700 | Scale
  // = 0
  ck_assert_uint_eq(s21_sub(val_3, val_4, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], original_result_1.bits[0]);
  ck_assert_uint_eq(result_1.bits[1], original_result_1.bits[1]);
  ck_assert_uint_eq(result_1.bits[2], original_result_1.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_1), 0);
  ck_assert_uint_eq(check_sign_bit(result_1), 1);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_5 = {0}, result_2 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111",
      &val_5);
  change_the_exponent(&val_5.bits[3], 0);

  s21_decimal val_6 = {0};
  from_char_to_decimal("01", &val_6);
  change_the_exponent(&val_6.bits[3], 1);

  s21_decimal original_result_2 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111",
      &original_result_2);

  // 79228162514264337593543950335 - 0.1 = +79228162514264337593543950335 |
  // Scale = 0
  ck_assert_uint_eq(s21_sub(val_5, val_6, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], original_result_2.bits[0]);
  ck_assert_uint_eq(result_2.bits[1], original_result_2.bits[1]);
  ck_assert_uint_eq(result_2.bits[2], original_result_2.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_2), 0);
  ck_assert_uint_eq(check_sign_bit(result_2), 0);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_7 = {0}, result_3 = {0};
  from_char_to_decimal("11101000110101001010010100010000000000000", &val_7);
  change_the_exponent(&val_7.bits[3], 0);

  s21_decimal val_8 = {0, 0, 0, 2147483648};
  from_char_to_decimal("10111010010000111011011101000000000000000", &val_8);
  change_the_exponent(&val_8.bits[3], 0);

  s21_decimal original_result_3 = {0};
  from_char_to_decimal("110100011000110000101110001010000000000000",
                       &original_result_3);

  // 2000000000000 - -1600000000000 = +3600000000000 | Scale = 0
  ck_assert_uint_eq(s21_sub(val_7, val_8, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], original_result_3.bits[0]);
  ck_assert_uint_eq(result_3.bits[1], original_result_3.bits[1]);
  ck_assert_uint_eq(result_3.bits[2], original_result_3.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_3), 0);
  ck_assert_uint_eq(check_sign_bit(result_3), 0);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_9 = {0}, result_4 = {0};
  from_char_to_decimal(
      "1010110101010001111110101101011010110000011000000100010001100110011",
      &val_9);
  change_the_exponent(&val_9.bits[3], 20);

  s21_decimal val_10 = {0};
  from_char_to_decimal("1001", &val_10);
  change_the_exponent(&val_10.bits[3], 1);

  s21_decimal original_result_4 = {0};
  from_char_to_decimal(
      "1000100110001111100110111000110010101001110110100010001100110011",
      &original_result_4);

  // 0.99912312333313123123 - 0.9 = +0.09912312333313123123 | Scale: 20
  ck_assert_uint_eq(s21_sub(val_9, val_10, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], original_result_4.bits[0]);
  ck_assert_uint_eq(result_4.bits[1], original_result_4.bits[1]);
  ck_assert_uint_eq(result_4.bits[2], original_result_4.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_4), 20);
  ck_assert_uint_eq(check_sign_bit(result_4), 0);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_11 = {0}, result_5 = {0};
  from_char_to_decimal(
      "110110110100110110100101111100000010100101111101010110001", &val_11);
  change_the_exponent(&val_11.bits[3], 9);

  s21_decimal val_12 = {0};
  from_char_to_decimal("10111111001111111000011011", &val_12);
  change_the_exponent(&val_12.bits[3], 3);

  s21_decimal original_result_5 = {0};
  from_char_to_decimal(
      "110110110011011011011001100000011111110110111110111110001",
      &original_result_5);

  // 123456789.987654321 - 50134.555 = +123406655.432654321 | Scale: 9
  ck_assert_uint_eq(s21_sub(val_11, val_12, &result_5), 0);
  ck_assert_uint_eq(result_5.bits[0], original_result_5.bits[0]);
  ck_assert_uint_eq(result_5.bits[1], original_result_5.bits[1]);
  ck_assert_uint_eq(result_5.bits[2], original_result_5.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_5), 9);
  ck_assert_uint_eq(check_sign_bit(result_5), 0);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_13 = {0, 0, 0, 2147483648}, result_6 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111110011",
      &val_13);
  change_the_exponent(&val_13.bits[3], 0);

  s21_decimal val_14 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111",
      &val_14);
  change_the_exponent(&val_14.bits[3], 0);

  // -79228162514264337593543950323 - 79228162514264337593543950335 = -OVERFLOW
  // | Scale: 0
  ck_assert_uint_eq(s21_sub(val_13, val_14, &result_6), 2);

  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_15 = {0, 0, 0, 2147483648}, result_7 = {0};
  from_char_to_decimal("100011100001101111001001101111110000001111111111111111",
                       &val_15);
  change_the_exponent(&val_15.bits[3], 16);

  s21_decimal val_16 = {0, 0, 0, 2147483648};
  from_char_to_decimal("01", &val_16);
  change_the_exponent(&val_16.bits[3], 9);

  s21_decimal original_result_7 = {0};
  from_char_to_decimal("100011100001101111001001101111001010000110100101111111",
                       &original_result_7);

  // -0.9999999999999999 - -0.000000001 = -0.9999999989999999 | Scale: 16
  ck_assert_uint_eq(s21_sub(val_15, val_16, &result_7), 0);
  ck_assert_uint_eq(result_7.bits[0], original_result_7.bits[0]);
  ck_assert_uint_eq(result_7.bits[1], original_result_7.bits[1]);
  ck_assert_uint_eq(result_7.bits[2], original_result_7.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_7), 16);
  ck_assert_uint_eq(check_sign_bit(result_7), 1);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_17 = {0, 0, 0, 0}, result_8 = {0};
  from_char_to_decimal(
      "10000000000000000000000000000000100000000000000001111111111111111",
      &val_17);
  change_the_exponent(&val_17.bits[3], 20);

  s21_decimal val_18 = {0, 0, 0, 2147483648};
  from_char_to_decimal("100111111111111111111010011001010001", &val_18);
  change_the_exponent(&val_18.bits[3], 5);

  s21_decimal original_result_8 = {0};
  from_char_to_decimal(
      "100011100001101111001000110001001000100011111100100101010110011100111101"
      "11111111111111",
      &original_result_8);

  // 0.18446744078004584447 - -429496.50001 = 429496.68447744078004584447 |
  // Scale: 20
  ck_assert_uint_eq(s21_sub(val_17, val_18, &result_8), 0);
  ck_assert_uint_eq(result_8.bits[0], original_result_8.bits[0]);
  ck_assert_uint_eq(result_8.bits[1], original_result_8.bits[1]);
  ck_assert_uint_eq(result_8.bits[2], original_result_8.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_8), 20);
  ck_assert_uint_eq(check_sign_bit(result_8), 0);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_19 = {0}, result_9 = {0};
  from_char_to_decimal(
      "10000000000000000000000000000000100000000000000001111111111111111",
      &val_19);
  change_the_exponent(&val_19.bits[3], 28);

  s21_decimal val_20 = {0};
  from_char_to_decimal(
      "10000000000000000000000000000000100000000000000001111111111111111",
      &val_20);
  change_the_exponent(&val_20.bits[3], 28);

  s21_decimal original_result_9 = {0};
  from_char_to_decimal("0", &original_result_9);

  // 0.0000000018446744078004584447 - 0.0000000018446744078004584447 =  0 |
  // Scale: 0
  ck_assert_uint_eq(s21_sub(val_19, val_20, &result_9), 0);
  ck_assert_uint_eq(result_9.bits[0], original_result_9.bits[0]);
  ck_assert_uint_eq(result_9.bits[1], original_result_9.bits[1]);
  ck_assert_uint_eq(result_9.bits[2], original_result_9.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_9), 0);
  ck_assert_uint_eq(check_sign_bit(result_9), 0);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_21 = {0}, result_10 = {0};
  from_char_to_decimal(
      "10000000000000000000000000000000100000000000000001111111111111111",
      &val_21);
  change_the_exponent(&val_21.bits[3], 28);

  s21_decimal val_22 = {0, 0, 0, 2147483648};
  from_char_to_decimal(
      "10000000000000000000000000000000100000000000000001111111111111111",
      &val_22);
  change_the_exponent(&val_22.bits[3], 28);

  s21_decimal original_result_10 = {0};
  from_char_to_decimal(
      "100000000000000000000000000000001000000000000000011111111111111110",
      &original_result_10);

  // 0.0000000018446744078004584447 - -0.0000000018446744078004584447 =
  // +0.0000000036893488156009168894 | Scale: 28
  ck_assert_uint_eq(s21_sub(val_21, val_22, &result_10), 0);
  ck_assert_uint_eq(result_10.bits[0], original_result_10.bits[0]);
  ck_assert_uint_eq(result_10.bits[1], original_result_10.bits[1]);
  ck_assert_uint_eq(result_10.bits[2], original_result_10.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_10), 28);
  ck_assert_uint_eq(check_sign_bit(result_10), 0);
}
END_TEST

START_TEST(test_s21_sub_error_codes) {
  s21_decimal val_1 = {0xffffffff, 0xffffffff, 0xffffffff, 2147483648},
              result_0 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111",
      &val_1);
  change_the_exponent(&val_1.bits[3], 0);

  s21_decimal val_2 = {10, 0, 0, 0};
  from_char_to_decimal("1010", &val_2);
  change_the_exponent(&val_2.bits[3], 0);

  // -79228162514264337593543950335 - 10 = -Overflow
  ck_assert_uint_eq(s21_sub(val_1, val_2, &result_0), 2);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_3 = {0xffffffff, 0xffffffff, 0xffffffff, 0}, result_1 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111",
      &val_3);
  change_the_exponent(&val_3.bits[3], 0);

  s21_decimal val_4 = {2, 0, 0, 2147483648};
  from_char_to_decimal("10", &val_4);
  change_the_exponent(&val_4.bits[3], 0);

  // 79228162514264337593543950335 - -2 = +Overflow
  ck_assert_uint_eq(s21_sub(val_3, val_4, &result_1), 1);
}
END_TEST

Suite *sub_suite(void) {
  Suite *suite = suite_create("s21_sub");
  TCase *test_case = tcase_create("case_sub");

  tcase_add_test(test_case, test_s21_sub_1);
  tcase_add_test(test_case, test_s21_sub_first_neg);
  tcase_add_test(test_case, test_s21_sub_second_neg);
  tcase_add_test(test_case, test_s21_sub_over_1_byte);
  tcase_add_test(test_case, test_s21_sub_error_codes);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = sub_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}