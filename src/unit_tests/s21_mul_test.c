#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_mul_1) {
  s21_decimal val_1 = {1001234, 0, 0, 2147483648}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);
  s21_decimal val_2 = {1001000, 0, 0, 2147483648};
  change_the_exponent(&val_2.bits[3], 4);
  s21_decimal original_result_0 = {0};
  from_char_to_decimal("1110100101011001111000000000011011010000",
                       &original_result_0);
  // -100.1234 * -100.1000 = 10022.35234000 | Scale: 8
  ck_assert_uint_eq(s21_mul(val_1, val_2, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], original_result_0.bits[0]);
  ck_assert_uint_eq(result_1.bits[1], original_result_0.bits[1]);
  ck_assert_uint_eq(result_1.bits[2], original_result_0.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_1), 8);
  ck_assert_uint_eq(check_sign_bit(result_1), 0);
  ////////////////////////////////////////////////////////////
  s21_decimal val_3 = {1, 0, 0, 0}, result_2 = {0};
  s21_decimal val_4 = {2, 0, 0, 0};
  int result_code_2 = s21_mul(val_3, val_4, &result_2);
  // 1 * 2 = 2
  ck_assert_uint_eq(result_code_2, 0);
  ck_assert_uint_eq(result_2.bits[0], 2);
  ck_assert_uint_eq(check_scaling_factor(result_2), 0);
  ck_assert_uint_eq(check_sign_bit(result_2), 0);
  ////////////////////////////////////////////////////////////
  s21_decimal val_5 = {1, 0, 0, 2147483648}, result_3 = {0};
  s21_decimal val_6 = {2, 0, 0, 0};
  // -1 * 2 = -2
  ck_assert_uint_eq(s21_mul(val_5, val_6, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], 2);
  ck_assert_uint_eq(check_scaling_factor(result_3), 0);
  ck_assert_uint_eq(check_sign_bit(result_3), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_7 = {1, 0, 0, 2147483648}, result_4 = {0};
  s21_decimal val_8 = {1, 0, 0, 0};
  // -1 * 1 = -1
  ck_assert_uint_eq(s21_mul(val_7, val_8, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], 1);
  ck_assert_uint_eq(check_scaling_factor(result_4), 0);
  ck_assert_uint_eq(check_sign_bit(result_4), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_9 = {1000000000, 0, 0, 0}, result_5 = {0};
  s21_decimal val_10 = {3, 0, 0, 0};
  // 1000000000 * 3 = +3000000000 | Scale: 0
  ck_assert_uint_eq(s21_mul(val_9, val_10, &result_5), 0);
  ck_assert_uint_eq(result_5.bits[0], 3000000000);
  ck_assert_uint_eq(check_scaling_factor(result_5), 0);
  ck_assert_uint_eq(check_sign_bit(result_5), 0);
  ////////////////////////////////////////////////////////////
  s21_decimal val_11 = {18, 0, 0, 2147483648}, result_6 = {0};
  s21_decimal val_12 = {35, 0, 0, 2147483648};
  // -18 * -35 = +630
  ck_assert_uint_eq(s21_mul(val_11, val_12, &result_6), 0);
  ck_assert_uint_eq(result_6.bits[0], 630);
  ck_assert_uint_eq(check_scaling_factor(result_6), 0);
  ck_assert_uint_eq(check_sign_bit(result_6), 0);
}
END_TEST

START_TEST(test_s21_mul_first_neg) {
  s21_decimal val_1 = {567812, 0, 0, 2147483648}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);
  s21_decimal val_2 = {1001000, 0, 0, 0};
  change_the_exponent(&val_2.bits[3], 6);
  s21_decimal original_result_0 = {0};
  from_char_to_decimal("1000010001010110000100111010100010100000",
                       &original_result_0);
  // -56.7812 * 1.001000 = -56.8379812000 | Scale = 10
  ck_assert_uint_eq(s21_mul(val_1, val_2, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], original_result_0.bits[0]);
  ck_assert_uint_eq(result_1.bits[1], original_result_0.bits[1]);
  ck_assert_uint_eq(result_1.bits[2], original_result_0.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_1), 10);
  ck_assert_uint_eq(check_sign_bit(result_1), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_3 = {556789, 0, 0, 2147483648}, result_2 = {0};
  change_the_exponent(&val_3.bits[3], 4);
  s21_decimal val_4 = {99345671, 0, 0, 0};
  change_the_exponent(&val_4.bits[3], 3);
  s21_decimal original_result_1 = {0};
  from_char_to_decimal("1100100100111011101101101100111010000110110011",
                       &original_result_1);
  // -55.6789 * 99345.671 = -5531457.6810419 | Scale = 7
  ck_assert_uint_eq(s21_mul(val_3, val_4, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], original_result_1.bits[0]);
  ck_assert_uint_eq(result_2.bits[1], original_result_1.bits[1]);
  ck_assert_uint_eq(result_2.bits[2], original_result_1.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_2), 7);
  ck_assert_uint_eq(check_sign_bit(result_2), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_5 = {1287231, 0, 0, 2147483648}, result_3 = {0};
  change_the_exponent(&val_5.bits[3], 2);
  s21_decimal val_6 = {1789901, 0, 0, 0};
  change_the_exponent(&val_6.bits[3], 3);
  s21_decimal original_result_2 = {0};
  from_char_to_decimal("100001100001110010000011101111011101110011",
                       &original_result_2);

  // -12872.31 * 1789.901 = -23040160.54131 | Scale = 5
  ck_assert_uint_eq(s21_mul(val_5, val_6, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], original_result_2.bits[0]);
  ck_assert_uint_eq(result_3.bits[1], original_result_2.bits[1]);
  ck_assert_uint_eq(result_3.bits[2], original_result_2.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_3), 5);
  ck_assert_uint_eq(check_sign_bit(result_3), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_7 = {123432, 0, 0, 2147483648}, result_4 = {0};
  change_the_exponent(&val_7.bits[3], 2);
  s21_decimal val_8 = {500356912, 0, 0, 0};
  change_the_exponent(&val_8.bits[3], 3);
  s21_decimal original_result_3 = {0};
  from_char_to_decimal("1110000010101110100010000110011111111110000000",
                       &original_result_3);
  //-1234.32 * 500356.912 = -617600543.61984 | Scale = 5
  ck_assert_uint_eq(s21_mul(val_7, val_8, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], original_result_3.bits[0]);
  ck_assert_uint_eq(result_4.bits[1], original_result_3.bits[1]);
  ck_assert_uint_eq(result_4.bits[2], original_result_3.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_4), 5);
  ck_assert_uint_eq(check_sign_bit(result_3), 1);
}
END_TEST

START_TEST(test_s21_mul_second_neg) {
  s21_decimal val_ = {5678, 0, 0, 0}, result_0 = {0};
  change_the_exponent(&val_.bits[3], 2);
  s21_decimal val_0 = {1001000, 0, 0, 2147483648};
  change_the_exponent(&val_0.bits[3], 4);
  s21_decimal original_result_0 = {0};
  from_char_to_decimal("101010010110001100000101100110000", &original_result_0);
  // 56.78 * -100.1000 = -5683.678000 | Scale = 6
  ck_assert_uint_eq(s21_mul(val_, val_0, &result_0), 0);
  ck_assert_uint_eq(result_0.bits[0], original_result_0.bits[0]);
  ck_assert_uint_eq(result_0.bits[1], original_result_0.bits[1]);
  ck_assert_uint_eq(result_0.bits[2], original_result_0.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_0), 6);
  ck_assert_uint_eq(check_sign_bit(result_0), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_1 = {567812, 0, 0, 0}, result_1 = {0};
  change_the_exponent(&val_1.bits[3], 4);
  s21_decimal val_2 = {1001000, 0, 0, 2147483648};
  change_the_exponent(&val_2.bits[3], 6);
  s21_decimal original_result_1 = {0};
  from_char_to_decimal("1000010001010110000100111010100010100000",
                       &original_result_1);
  // 56.7812 * -1.001000 = -56.8379812000 | Scale = 10
  ck_assert_uint_eq(s21_mul(val_1, val_2, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], original_result_1.bits[0]);
  ck_assert_uint_eq(result_1.bits[1], original_result_1.bits[1]);
  ck_assert_uint_eq(result_1.bits[2], original_result_1.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_1), 10);
  ck_assert_uint_eq(check_sign_bit(result_1), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_3 = {556789, 0, 0, 0}, result_2 = {0};
  change_the_exponent(&val_3.bits[3], 4);
  s21_decimal val_4 = {99345671, 0, 0, 2147483648};
  change_the_exponent(&val_4.bits[3], 3);
  s21_decimal original_result_2 = {0};
  from_char_to_decimal("1100100100111011101101101100111010000110110011",
                       &original_result_2);
  // 55.6789 * -99345.671 = -5531457.6810419 | Scale = 7
  ck_assert_uint_eq(s21_mul(val_3, val_4, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], original_result_2.bits[0]);
  ck_assert_uint_eq(result_2.bits[1], original_result_2.bits[1]);
  ck_assert_uint_eq(result_2.bits[2], original_result_2.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_2), 7);
  ck_assert_uint_eq(check_sign_bit(result_2), 1);
  ////////////////////////////////////////////////////////////
  s21_decimal val_5 = {8589741, 0, 0, 0}, result_3 = {0};
  change_the_exponent(&val_5.bits[3], 2);
  s21_decimal val_6 = {1789901, 0, 0, 2147483648};
  change_the_exponent(&val_6.bits[3], 3);
  s21_decimal original_result_3 = {0};
  from_char_to_decimal("11011111101110111000101010001000101010001001",
                       &original_result_3);
  // 85897.41 * -1789.901 = -153747860.05641 | Scale = 5
  ck_assert_uint_eq(s21_mul(val_5, val_6, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], original_result_3.bits[0]);
  ck_assert_uint_eq(result_3.bits[1], original_result_3.bits[1]);
  ck_assert_uint_eq(result_3.bits[2], original_result_3.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_3), 5);
  ck_assert_uint_eq(check_sign_bit(result_3), 1);
}
END_TEST

START_TEST(test_s21_mul_over_1_byte) {
  s21_decimal val_1 = {0}, result_0 = {0};
  from_char_to_decimal("1111010100110111111101101010100010", &val_1);
  change_the_exponent(&val_1.bits[3], 0);

  s21_decimal val_2 = {0};
  from_char_to_decimal("11110000011101001010110111001001", &val_2);
  change_the_exponent(&val_2.bits[3], 0);

  s21_decimal original_result_0 = {0};
  from_char_to_decimal(
      "111001100101010000111011000100010001011011111010100010001100110010",
      &original_result_0);
  // 16456342178 * 4034178505 = +66387821885412483890 | Scale = 0
  ck_assert_uint_eq(s21_mul(val_1, val_2, &result_0), 0);
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
  // change_the_exponent(&val_3.bits[3], 0);

  s21_decimal val_4 = {32, 0, 0, 0};
  // change_the_exponent(&val_4.bits[3], 0);

  s21_decimal original_result_1 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111100000",
      &original_result_1);

  // 18446744073709551615 * 32 = 590295810358705651680 | Scale = 0
  ck_assert_uint_eq(s21_mul(val_3, val_4, &result_1), 0);
  ck_assert_uint_eq(result_1.bits[0], original_result_1.bits[0]);
  ck_assert_uint_eq(result_1.bits[1], original_result_1.bits[1]);
  ck_assert_uint_eq(result_1.bits[2], original_result_1.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_1), 0);
  ck_assert_uint_eq(check_sign_bit(result_1), 0);
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

  // 79228162514264337593543950335 * 0.1 = +7922816251426433759354395033.5 |
  // Scale = 1
  ck_assert_uint_eq(s21_mul(val_5, val_6, &result_2), 0);
  ck_assert_uint_eq(result_2.bits[0], original_result_2.bits[0]);
  ck_assert_uint_eq(result_2.bits[1], original_result_2.bits[1]);
  ck_assert_uint_eq(result_2.bits[2], original_result_2.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_2), 1);
  ck_assert_uint_eq(check_sign_bit(result_2), 0);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_7 = {0}, result_3 = {0};
  from_char_to_decimal("11101000110101001010010100010000000000000", &val_7);
  change_the_exponent(&val_7.bits[3], 0);

  s21_decimal val_8 = {0, 0, 0, 2147483648};
  from_char_to_decimal("10111010010000111011011101000000000000000", &val_8);
  change_the_exponent(&val_8.bits[3], 0);

  s21_decimal original_result_3 = {0};
  from_char_to_decimal(
      "101010010110100000010110001111110000101001010111101101000000000000000000"
      "0000000000",
      &original_result_3);

  // 2000000000000 * -1600000000000 = -3200000000000000000000000 | Scale = 0
  ck_assert_uint_eq(s21_mul(val_7, val_8, &result_3), 0);
  ck_assert_uint_eq(result_3.bits[0], original_result_3.bits[0]);
  ck_assert_uint_eq(result_3.bits[1], original_result_3.bits[1]);
  ck_assert_uint_eq(result_3.bits[2], original_result_3.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_3), 0);
  ck_assert_uint_eq(check_sign_bit(result_3), 1);
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
      "1100001011111100001110100011000110000110011011000100110011110011001011",
      &original_result_4);

  // 0.99912312333313123123 * 0.9 = +0.899210810999818108107 | Scale: 21
  ck_assert_uint_eq(s21_mul(val_9, val_10, &result_4), 0);
  ck_assert_uint_eq(result_4.bits[0], original_result_4.bits[0]);
  ck_assert_uint_eq(result_4.bits[1], original_result_4.bits[1]);
  ck_assert_uint_eq(result_4.bits[2], original_result_4.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_4), 21);
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
      "101000111101010101011010010110010010010000100110111001001011011100000001"
      "11010101011",
      &original_result_5);

  // 123456789.987654321 * 50134.555 = +6189451227759.504877162155 | Scale: 12
  ck_assert_uint_eq(s21_mul(val_11, val_12, &result_5), 0);
  ck_assert_uint_eq(result_5.bits[0], original_result_5.bits[0]);
  ck_assert_uint_eq(result_5.bits[1], original_result_5.bits[1]);
  ck_assert_uint_eq(result_5.bits[2], original_result_5.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_5), 12);
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

  // -79228162514264337593543950323 * 79228162514264337593543950335 = -OVERFLOW
  // | Scale: 0
  ck_assert_uint_eq(s21_mul(val_13, val_14, &result_6), 2);

  ////////////////////////////////////////////////////////////////////////////////////
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

  // -0.9999999999999999 * -0.000000001 = +0.0000000009999999999999999 | Scale:
  // 25
  ck_assert_uint_eq(s21_mul(val_15, val_16, &result_7), 0);
  ck_assert_uint_eq(result_7.bits[0], original_result_7.bits[0]);
  ck_assert_uint_eq(result_7.bits[1], original_result_7.bits[1]);
  ck_assert_uint_eq(result_7.bits[2], original_result_7.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_7), 25);
  ck_assert_uint_eq(check_sign_bit(result_7), 0);
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
      "111111111111111111110111000010010001100110011010100100001010000010101010"
      "001110110101010111000101",
      &original_result_8);

  // 0.18446744078004584447 * -429496.50001 = -79228.120180831634447209813445 |
  // Scale: 25
  ck_assert_uint_eq(s21_mul(val_17, val_18, &result_8), 0);
  ck_assert_uint_eq(result_8.bits[0], original_result_8.bits[0]);
  ck_assert_uint_eq(result_8.bits[1], original_result_8.bits[1]);
  ck_assert_uint_eq(result_8.bits[2], original_result_8.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_8), 24);
  ck_assert_uint_eq(check_sign_bit(result_8), 1);
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
  from_char_to_decimal("11111101100001111011010111110100100",
                       &original_result_9);

  // 0.0000000018446744078004584447 * 0.0000000018446744078004584447 =
  // 0.0000000000000000034028236708 | Scale: 0
  ck_assert_uint_eq(s21_mul(val_19, val_20, &result_9), 0);
  ck_assert_uint_eq(result_9.bits[0], original_result_9.bits[0]);
  ck_assert_uint_eq(result_9.bits[1], original_result_9.bits[1]);
  ck_assert_uint_eq(result_9.bits[2], original_result_9.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_9), 28);
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
  from_char_to_decimal("11111101100001111011010111110100100",
                       &original_result_10);

  // 0.0000000018446744078004584447 * -0.0000000018446744078004584447 =
  // -0.0000000036893488156009168894 | Scale: 28
  ck_assert_uint_eq(s21_mul(val_21, val_22, &result_10), 0);
  ck_assert_uint_eq(result_10.bits[0], original_result_10.bits[0]);
  ck_assert_uint_eq(result_10.bits[1], original_result_10.bits[1]);
  ck_assert_uint_eq(result_10.bits[2], original_result_10.bits[2]);
  ck_assert_uint_eq(check_scaling_factor(result_10), 28);
  ck_assert_uint_eq(check_sign_bit(result_10), 1);
}
END_TEST

START_TEST(test_s21_mul_error_codes) {
  s21_decimal val_1 = {0xffffffff, 0xffffffff, 0xffffffff, 2147483648},
              result_0 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111",
      &val_1);
  change_the_exponent(&val_1.bits[3], 0);

  s21_decimal val_2 = {0};
  from_char_to_decimal("1010", &val_2);
  change_the_exponent(&val_2.bits[3], 0);

  // -79228162514264337593543950335 * 10 = -Overflow
  ck_assert_uint_eq(s21_mul(val_1, val_2, &result_0), 2);
  ////////////////////////////////////////////////////////////////////////////////////
  s21_decimal val_3 = {0xffffffff, 0xffffffff, 0xffffffff, 0}, result_1 = {0};
  from_char_to_decimal(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111",
      &val_3);
  change_the_exponent(&val_3.bits[3], 0);

  s21_decimal val_4 = {2, 0, 0, 0};
  from_char_to_decimal("10", &val_4);
  change_the_exponent(&val_4.bits[3], 0);

  // 79228162514264337593543950335 * 2 = +Overflow
  ck_assert_uint_eq(s21_mul(val_3, val_4, &result_1), 1);
}
END_TEST

Suite *mul_suite(void) {
  Suite *suite = suite_create("s21_mul");
  TCase *test_case = tcase_create("case_mul");

  tcase_add_test(test_case, test_s21_mul_1);
  tcase_add_test(test_case, test_s21_mul_first_neg);
  tcase_add_test(test_case, test_s21_mul_second_neg);
  tcase_add_test(test_case, test_s21_mul_over_1_byte);
  tcase_add_test(test_case, test_s21_mul_error_codes);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = mul_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}