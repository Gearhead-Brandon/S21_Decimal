#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int code = 0;
  if (dst == NULL || s21_is_inf(src) || (src > 0.0f && src < 1e-28) ||
      (src > 1e+28) || (src != src)) {
    code = 1;
  } else {
    reset_result(dst);
    if (src == 0.0f) return 0;

    char str[14], f[8] = {0};

    sprintf(str, "%e", src);

    int size = src < 0 ? 13 : 12;
    int j = src < 0 ? 1 : 0;

    for (int iter = 0; j < size - 4; j++) {
      if (str[j] == '.') continue;

      f[iter++] = str[j];
    }

    int scale_e = (str[size - 1] - '0') + (str[size - 2] - '0') * 10;
    char sign_scale_e = str[size - 3];

    int res = atoi(f);
    int count_zero = sign_scale_e == '+' ? 6 - scale_e : 6 + scale_e;

    dst->bits[0] = res;

    if (count_zero < 0) multiplication_by_ten(dst, abs(count_zero));

    if (count_zero > 0) change_the_exponent(&dst->bits[3], count_zero);

    big_decimal a = {0};
    from_decimal_to_big_decimal(*dst, &a);
    delete_trailing_zeroes(&a);
    from_big_decimal_to_decimal(a, dst);

    if (src < 0) set_bit(&dst->bits[3], 31, 1);
  }
  return code;
}