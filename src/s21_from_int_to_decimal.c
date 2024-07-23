#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int code = 0;
  if (dst == NULL)
    code = 1;
  else {
    reset_result(dst);
    if (src < 0) {
      if (src == -2147483648) src += 1;
      src *= -1;
      set_bit(&dst->bits[3], 31, 1);
    }

    dst->bits[0] = src;
  }
  return code;
}