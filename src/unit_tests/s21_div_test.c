#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_div_1) {
  s21_decimal val_1 = {1001234, 0, 0, 2147483648}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);
  s21_decimal val_2 = {1001000, 0, 0, 2147483648};
  change_the_exponent(&val_2.bits[3], 4);
  s21_decimal original_result_0 = {0};
  from_char_to_decimal(
      "100000010100011011110101100011001011000000100001110000011001001010100110"
      "0111000100001001111110",
      &original_result_0);
  // -100.1234 / -100.1000 = 1.0002337662337662337662337662 | Scale: 28
  ck_assert_uint_eq(s21_div(val_1, val_2, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], original_result_0.bits[0]);
  ck_assert_uint_eq(result_1.bits[1], original_result_0.bits[1]);
  ck_assert_uint_eq(result_1.bits[2], original_result_0.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_1), 28);
  ck_assert_uint_eq(check_sign_bit(result_1), 0);
  //////////////////////////////////////////////////////////////////
  s21_decimal val_3 = {1, 0, 0, 0}, result_2 = {0};
  s21_decimal val_4 = {2, 0, 0, 0};
  // 1 / 2 = 0.5 | Scale: 1
  ck_assert_uint_eq(s21_div(val_3, val_4, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], 5);
  ck_assert_uint_eq(check_scaling_factor(result_2), 1);
  ck_assert_uint_eq(check_sign_bit(result_2), 0);
  // ////////////////////////////////////////////////////////////////
  s21_decimal val_5 = {7, 0, 0, 2147483648}, result_3 = {0};
  s21_decimal val_6 = {2, 0, 0, 0};
  // -7 / 2 = -3.5 | Scale: 1
  ck_assert_uint_eq(s21_div(val_5, val_6, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], 35);
  ck_assert_uint_eq(check_scaling_factor(result_3), 1);
  ck_assert_uint_eq(check_sign_bit(result_3), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal val_7 = {1, 0, 0, 2147483648}, result_4 = {0};
  s21_decimal val_8 = {1, 0, 0, 0};
  // -1 / 1 = -1 | Scale: 0
  ck_assert_uint_eq(s21_div(val_7, val_8, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], 1);
  ck_assert_uint_eq(check_scaling_factor(result_4), 0);
  ck_assert_uint_eq(check_sign_bit(result_4), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal val_9 = {1000000000, 0, 0, 0}, result_5 = {0};
  s21_decimal val_10 = {4, 0, 0, 0};
  // 1000000000 / 4 = +250000000 | Scale: 0
  ck_assert_uint_eq(s21_div(val_9, val_10, &result_5), 0);
  ck_assert_uint_eq(result_5.bits[0], 250000000);
  ck_assert_uint_eq(check_scaling_factor(result_5), 0);
  ck_assert_uint_eq(check_sign_bit(result_5), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal val_11 = {630, 0, 0, 2147483648}, result_6 = {0};
  s21_decimal val_12 = {35, 0, 0, 2147483648};
  // -630 / -35 = +18 | Scale: 0
  ck_assert_uint_eq(s21_div(val_11, val_12, &result_6), 0);
  ck_assert_uint_eq(result_6.bits[0], 18);
  ck_assert_uint_eq(check_scaling_factor(result_6), 0);
  ck_assert_uint_eq(check_sign_bit(result_6), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal val_13 = {1, 0, 0, 0}, result_7 = {0};
  s21_decimal val_14 = {3, 0, 0, 0};
  s21_decimal original_result_7 = {0};
  from_char_to_decimal(
      "101011000101010001001100101000010100101101110000000011001011000001010101"
      "01010101010101010101",
      &original_result_7);
  // 1 / 3 = +0.3333333333333333333333333333 | Scale: 28
  ck_assert_uint_eq(s21_div(val_13, val_14, &result_7), 0);
  ck_assert_uint_eq(result_7.bits[0], original_result_7.bits[0]);
  ck_assert_uint_eq(result_7.bits[1], original_result_7.bits[1]);
  ck_assert_uint_eq(result_7.bits[2], original_result_7.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_7), 28);
  ck_assert_uint_eq(check_sign_bit(result_7), 0);
}
END_TEST

START_TEST(test_s21_div_first_neg) {
  s21_decimal val_1 = {567812, 0, 0, 2147483648}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);
  s21_decimal val_2 = {28, 0, 0, 0};
  change_the_exponent(&val_2.bits[3], 0);

  // -56.7812 / 28 = 2.0279 | Scale: 4
  ck_assert_uint_eq(s21_div(val_1, val_2, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], 20279);
  ck_assert_uint_eq(check_scaling_factor(result_1), 4);
  ck_assert_uint_eq(check_sign_bit(result_1), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal val_3 = {556789, 0, 0, 2147483648}, result_2 = {0};
  change_the_exponent(&val_3.bits[3], 4);
  s21_decimal val_4 = {99345671, 0, 0, 0};
  change_the_exponent(&val_4.bits[3], 3);
  s21_decimal original_result_1 = {0};
  from_char_to_decimal(
      "100101000101100111111101110000001101011000001101101000101011011100011011"
      "11100001111",
      &original_result_1);
  // -55.6789 / 99345.671 = -0.0005604562276296870550101775 | Scale: 28
  ck_assert_uint_eq(s21_div(val_3, val_4, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], original_result_1.bits[0]);
  ck_assert_uint_eq(result_2.bits[1], original_result_1.bits[1]);
  ck_assert_uint_eq(result_2.bits[2], original_result_1.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_2), 28);
  ck_assert_uint_eq(check_sign_bit(result_2), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal val_5 = {4294967295, 0, 0, 0}, result_3 = {0};
  change_the_exponent(&val_5.bits[3], 2);
  s21_decimal val_6 = {15, 0, 0, 0};
  change_the_exponent(&val_6.bits[3], 3);
  // 42949672.95 / 0.015 = +2863311530 | Scale: 0
  ck_assert_uint_eq(s21_div(val_5, val_6, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], 2863311530);
  ck_assert_uint_eq(check_scaling_factor(result_3), 0);
  ck_assert_uint_eq(check_sign_bit(result_3), 0);
  ////////////////////////////////////////////////////////////////
  s21_decimal val_7 = {4998996, 0, 0, 2147483648}, result_4 = {0};
  change_the_exponent(&val_7.bits[3], 1);
  s21_decimal val_8 = {123432, 0, 0, 0};
  change_the_exponent(&val_8.bits[3], 2);
  // -499899.6 / 1234.32 = -405.0 | Scale: 1

  ck_assert_uint_eq(s21_div(val_7, val_8, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], 405);
  ck_assert_uint_eq(check_scaling_factor(result_4), 0);
  ck_assert_uint_eq(check_sign_bit(result_4), 1);
}
END_TEST

START_TEST(test_s21_div_second_neg) {
  s21_decimal val_ = {5678, 0, 0, 0}, result_0 = {0};
  change_the_exponent(&val_.bits[3], 2);
  s21_decimal val_0 = {1001000, 0, 0, 2147483648};
  change_the_exponent(&val_0.bits[3], 4);
  s21_decimal original_result_0 = {0};
  from_char_to_decimal(
      "100100101010000001010000110110100010011110101001000001000110011100010100"
      "000100110110111111000",
      &original_result_0);
  // 56.78 / -100.1000 = -0.5672327672327672327672327672 | Scale = 28
  ck_assert_uint_eq(s21_div(val_, val_0, &result_0), 0);
  ck_assert_uint_eq(result_0.bits[0], original_result_0.bits[0]);
  ck_assert_uint_eq(result_0.bits[1], original_result_0.bits[1]);
  ck_assert_uint_eq(result_0.bits[2], original_result_0.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_0), 28);
  ck_assert_uint_eq(check_sign_bit(result_0), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal val_1 = {567812, 0, 0, 0}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);
  s21_decimal val_2 = {2, 0, 0, 2147483648};
  change_the_exponent(&val_2.bits[3], 0);
  // 56.7812 / -2 = -28.3906 | Scale: 4
  ck_assert_uint_eq(s21_div(val_1, val_2, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], 283906);
  ck_assert_uint_eq(check_scaling_factor(result_1), 4);
  ck_assert_uint_eq(check_sign_bit(result_1), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal val_3 = {99345671, 0, 0, 0}, result_2 = {0};
  change_the_exponent(&val_3.bits[3], 3);
  s21_decimal val_4 = {17, 0, 0, 2147483648};
  change_the_exponent(&val_4.bits[3], 2);
  // 99345.671 / -0.17 = 584386.3 | Scale = 1
  ck_assert_uint_eq(s21_div(val_3, val_4, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], 5843863);
  ck_assert_uint_eq(check_scaling_factor(result_2), 1);
  ck_assert_uint_eq(check_sign_bit(result_2), 1);
  ////////////////////////////////////////////////////////////////
  s21_decimal val_5 = {8589741, 0, 0, 0}, result_3 = {0};
  change_the_exponent(&val_5.bits[3], 2);
  s21_decimal val_6 = {3, 0, 0, 0};
  change_the_exponent(&val_6.bits[3], 1);
  // 85897.41 / 0.3 = 286324.7 | Scale = 1
  ck_assert_uint_eq(s21_div(val_5, val_6, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], 2863247);
  ck_assert_uint_eq(check_scaling_factor(result_3), 1);
  ck_assert_uint_eq(check_sign_bit(result_3), 0);
}
END_TEST

START_TEST(test_s21_div_over_1_byte) {
  s21_decimal val_1 = {0}, result_0 = {0};
  from_char_to_decimal("1111010100110111111101101010100010", &val_1);
  change_the_exponent(&val_1.bits[3], 0);

  s21_decimal val_2 = {0};
  from_char_to_decimal("11101110011010110010100000000000", &val_2);
  change_the_exponent(&val_2.bits[3], 0);

  s21_decimal original_result_0 = {0};
  from_char_to_decimal("100110010100001011111010001010010101",
                       &original_result_0);

  // 16456342178 / 4000000000 = +4.1140855445 | Scale = 10
  ck_assert_uint_eq(s21_div(val_1, val_2, &result_0), 0);
  ck_assert_uint_eq(result_0.bits[0], original_result_0.bits[0]);
  ck_assert_uint_eq(result_0.bits[1], original_result_0.bits[1]);
  ck_assert_uint_eq(result_0.bits[2], original_result_0.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_0), 10);
  ck_assert_uint_eq(check_sign_bit(result_0), 0);
  ////////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_3 = {0}, result_1 = {0};
  from_char_to_decimal(
      "1111111111111111111111111111111111111111111111111111111111111111",
      &val_3);

  s21_decimal val_4 = {32, 0, 0, 0};

  s21_decimal original_result_1 = {0};
  from_char_to_decimal(
      "110000110100111111111111111111111111111111111111111111111111111100111100"
      "1011",
      &original_result_1);

  // 18446744073709551615 / 32 = 576460752303423487.96875 | Scale = 5
  ck_assert_uint_eq(s21_div(val_3, val_4, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], original_result_1.bits[0]);
  ck_assert_uint_eq(result_1.bits[1], original_result_1.bits[1]);
  ck_assert_uint_eq(result_1.bits[2], original_result_1.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_1), 5);
  ck_assert_uint_eq(check_sign_bit(result_1), 0);
  ////////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_5 = {0}, result_2 = {0};
  from_char_to_decimal(
      "110011001100110011001100110011001100110011001100110011001100110011001100"
      "110011001100110011001",
      &val_5);
  change_the_exponent(&val_5.bits[3], 0);

  s21_decimal val_6 = {0};
  from_char_to_decimal("01", &val_6);
  change_the_exponent(&val_6.bits[3], 1);

  s21_decimal original_result_2 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111010",
      &original_result_2);

  // 7922816251426433759354395033 / 0.1 = +79228162514264337593543950330 | Scale
  // = 0
  ck_assert_uint_eq(s21_div(val_5, val_6, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], original_result_2.bits[0]);
  ck_assert_uint_eq(result_2.bits[1], original_result_2.bits[1]);
  ck_assert_uint_eq(result_2.bits[2], original_result_2.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_2), 0);
  ck_assert_uint_eq(check_sign_bit(result_2), 0);
  ////////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_7 = {0}, result_3 = {0};
  from_char_to_decimal("11101000110101001010010100010000000000000", &val_7);
  change_the_exponent(&val_7.bits[3], 0);

  s21_decimal val_8 = {0, 0, 0, 2147483648};
  from_char_to_decimal("10111010010000111011011101000000000000000", &val_8);
  change_the_exponent(&val_8.bits[3], 0);

  s21_decimal original_result_3 = {0};
  from_char_to_decimal("1111101", &original_result_3);

  // 2000000000000 / -1600000000000 = -1.25 | Scale = 0
  ck_assert_uint_eq(s21_div(val_7, val_8, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], original_result_3.bits[0]);
  ck_assert_uint_eq(result_3.bits[1], original_result_3.bits[1]);
  ck_assert_uint_eq(result_3.bits[2], original_result_3.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_3), 2);
  ck_assert_uint_eq(check_sign_bit(result_3), 1);
  ////////////////////////////////////////////////////////////////////////////////////////
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
      "100011110111101101011000011111001010100110110000101011011010110100101001"
      "1000100011111111000111",
      &original_result_4);

  // 0.99912312333313123123 / 0.9 = +1.1101368037034791458111111111 | Scale: 28
  ck_assert_uint_eq(s21_div(val_9, val_10, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], original_result_4.bits[0]);
  ck_assert_uint_eq(result_4.bits[1], original_result_4.bits[1]);
  ck_assert_uint_eq(result_4.bits[2], original_result_4.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_4), 28);
  ck_assert_uint_eq(check_sign_bit(result_4), 0);
  ////
  ///////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_11 = {0}, result_5 = {0};
  from_char_to_decimal("111001100111100000001101111000100110", &val_11);
  change_the_exponent(&val_11.bits[3], 3);

  s21_decimal val_12 = {0};
  from_char_to_decimal("10111111001111111000011011", &val_12);
  change_the_exponent(&val_12.bits[3], 3);

  // 61866040.870 / 50134.555 = +1234 | Scale: 0
  ck_assert_uint_eq(s21_div(val_11, val_12, &result_5), 0);
  ck_assert_uint_eq(result_5.bits[0], 1234);
  ck_assert_uint_eq(check_scaling_factor(result_5), 0);
  ck_assert_uint_eq(check_sign_bit(result_5), 0);
  ////////////////////////////////////////////////////////////////////////////////////////
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
  s21_decimal original_result_5 = {0};
  from_char_to_decimal(
      "100000010011111100111001011110001111100010010100000010011000010000111111"
      "1111111111111111111110",
      &original_result_5);

  // -79228162514264337593543950323 / 79228162514264337593543950335
  // = -0.9999999999999999999999999998 | Scale: 28
  ck_assert_uint_eq(s21_div(val_13, val_14, &result_6), 0);
  ck_assert_uint_eq(result_6.bits[0], original_result_5.bits[0]);
  ck_assert_uint_eq(result_6.bits[1], original_result_5.bits[1]);
  ck_assert_uint_eq(result_6.bits[2], original_result_5.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_6), 28);
  ck_assert_uint_eq(check_sign_bit(result_6), 1);
  ////////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_15 = {0, 0, 0, 2147483648}, result_7 = {0};
  from_char_to_decimal("100011100001101111001001101111110000001111111111111111",
                       &val_15);
  change_the_exponent(&val_15.bits[3], 16);

  s21_decimal val_16 = {0, 0, 0, 2147483648};
  from_char_to_decimal("01", &val_16);
  change_the_exponent(&val_16.bits[3], 9);

  s21_decimal original_result_7 = {0};
  from_char_to_decimal("100011100001101111001001101111110000001111111111111111",
                       &original_result_7);

  // -0.9999999999999999 / -0.000000001 = 999999999.9999999 | Scale: 7
  ck_assert_uint_eq(s21_div(val_15, val_16, &result_7), 0);
  ck_assert_uint_eq(result_7.bits[0], original_result_7.bits[0]);
  ck_assert_uint_eq(result_7.bits[1], original_result_7.bits[1]);
  ck_assert_uint_eq(result_7.bits[2], original_result_7.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_7), 7);
  ck_assert_uint_eq(check_sign_bit(result_7), 0);
  ////////////////////////////////////////////////////////////////////////////////////////
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
      "11101000110101001010110100111001000001001111111010101101100011111010000"
      "1",
      &original_result_8);

  // 0.18446744078004584447 / -429496.50001 = -0.0000004294969592901243080609 |
  // Scale: 28
  ck_assert_uint_eq(s21_div(val_17, val_18, &result_8), 0);
  ck_assert_uint_eq(result_8.bits[0], original_result_8.bits[0]);
  ck_assert_uint_eq(result_8.bits[1], original_result_8.bits[1]);
  ck_assert_uint_eq(result_8.bits[2], original_result_8.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_8), 28);
  ck_assert_uint_eq(check_sign_bit(result_8), 1);
  ////////////////////////////////////////////////////////////////////////////////////////
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

  // 0.0000000018446744078004584447 / 0.0000000018446744078004584447 = +1 |
  // Scale: 0
  ck_assert_uint_eq(s21_div(val_19, val_20, &result_9), 0);
  ck_assert_uint_eq(result_9.bits[0], 1);
  ck_assert_uint_eq(check_scaling_factor(result_9), 0);
  ck_assert_uint_eq(check_sign_bit(result_9), 0);
  ////////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_21 = {0}, result_10 = {0};
  from_char_to_decimal(
      "10000000000000000000000000000000100000000000000001111111111111111",
      &val_21);
  change_the_exponent(&val_21.bits[3], 28);

  s21_decimal val_22 = {7, 0, 0, 2147483648};

  change_the_exponent(&val_22.bits[3], 28);

  s21_decimal original_result_10 = {0};
  from_char_to_decimal(
      "10010010010010010010010010010010110110110110111001001001001001",
      &original_result_10);

  // 0.0000000018446744078004584447 / -0.0000000000000000000000000007 =
  // -2635249154000654921 | Scale: 0
  ck_assert_uint_eq(s21_div(val_21, val_22, &result_10), 0);
  ck_assert_uint_eq(result_10.bits[0], original_result_10.bits[0]);
  ck_assert_uint_eq(result_10.bits[1], original_result_10.bits[1]);
  ck_assert_uint_eq(result_10.bits[2], original_result_10.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_10), 0);
  ck_assert_uint_eq(check_sign_bit(result_10), 1);
  ////////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_23 = {0xffffffff, 0xffffffff, 0xffffffff, 0}, result_11 = {0};
  s21_decimal val_24 = {10, 0, 0, 0};
  s21_decimal original_result_11 = {0xffffffff, 0xffffffff, 0xffffffff, 0};

  // 79228162514264337593543950335 / 10 = +7922816251426433759354395033.5 |
  // Scale: 1

  ck_assert_uint_eq(s21_div(val_23, val_24, &result_11), 0);

  ck_assert_uint_eq(result_11.bits[0], original_result_11.bits[0]);
  ck_assert_uint_eq(result_11.bits[1], original_result_11.bits[1]);
  ck_assert_uint_eq(result_11.bits[2], original_result_11.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_11), 1);
  ck_assert_uint_eq(check_sign_bit(result_11), 0);
}
END_TEST

START_TEST(test_s21_div_error_codes) {
  s21_decimal val_1 = {0, 0, 0, 2147483648}, result_0 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111",
      &val_1);
  change_the_exponent(&val_1.bits[3], 0);

  s21_decimal val_2 = {1, 0, 0, 0};
  change_the_exponent(&val_2.bits[3], 1);

  // -79228162514264337593543950335 / 0.1 = -Overflow
  ck_assert_uint_eq(s21_div(val_1, val_2, &result_0), 2);

  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_3 = {0}, result_1 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111",
      &val_3);
  change_the_exponent(&val_3.bits[3], 0);

  s21_decimal val_4 = {0, 0, 0, 2147483648};

  change_the_exponent(&val_4.bits[3], 0);

  // 79228162514264337593543950335 / -0 = error 3
  ck_assert_uint_eq(s21_div(val_3, val_4, &result_1), 3);
}
END_TEST

Suite *div_suite(void) {
  Suite *suite = suite_create("s21_div");
  TCase *test_case = tcase_create("case_div");

  tcase_add_test(test_case, test_s21_div_1);
  tcase_add_test(test_case, test_s21_div_first_neg);
  tcase_add_test(test_case, test_s21_div_second_neg);
  tcase_add_test(test_case, test_s21_div_over_1_byte);
  tcase_add_test(test_case, test_s21_div_error_codes);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = div_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}