#include "decimal_another.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (get_sign(value) && !is_zero(value)) {
    s21_decimal one = {INT32_MIN, 0, 0, 0};
    s21_truncate(value, result);
    very_stupid_add(*result, one, result);
  } else
    s21_truncate(value, result);
  return 0;
}