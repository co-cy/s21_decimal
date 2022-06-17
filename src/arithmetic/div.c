#include <stdint.h>

#include "decimal_arithmetic.h"

s21_decimal div_core(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result, int res_exp, int *status) {
  s21_decimal divcopy = value_2;
  s21_decimal temp = init_zero_decimal();
  s21_decimal temp2 = {1, 0, 0, 0};
  if (stupid_equal(value_1, value_2)) {
    return temp2;
  } else if (stupid_less(value_1, value_2)) {
    return temp;
  }
  while ((stupid_less(value_2, value_1) || stupid_equal(value_2, value_1)) &&
         !get_gbit(value_2, ALL_BIT - 1)) {
    left_shift(&value_2);
    left_shift(result);
  }
  if (stupid_less(value_1, value_2)) {
    right_shift(&value_2);
    right_shift(result);
  }
  // d_print_decimal(value_1);
  // d_print_decimal(value_2);
  // d_print_decimal(*result);
  // d_print_decimal(*result);
  very_stupid_sub(value_1, value_2, &temp);
  temp2 = div_core(temp, divcopy, &temp2, res_exp, status);
  *status = very_stupid_add(*result, temp2, result, 0, 0);
  return *result;
}

int int_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (is_zero(value_2)) return DIV_ZERO;
  int status = OK;
  *result = init_zero_decimal();
  s21_from_int_to_decimal(1, result);

  set_sign(result, get_sign(value_1) ^ get_sign(value_2));
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);

  int res_exp = get_exponent(value_1) - get_exponent(value_2);
  set_exponent(&value_1, 0);
  set_exponent(&value_2, 0);

  *result = div_core(value_1, value_2, result, res_exp, &status);
  set_exponent(result, res_exp);

  return status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  while (get_exponent(value_1) < get_exponent(value_2) && !status)
    status = shifting(&value_1, 1);
  if (!status) {
    status = int_div(value_1, value_2, result);
    s21_truncate(*result, result);
    s21_decimal mod_res = init_zero_decimal();
    s21_mod(value_1, value_2, &mod_res);
    d_print_decimal(*result);
    // d_print_decimal(mod_res);
    if (!is_zero(mod_res)) {
      s21_decimal div_res = init_zero_decimal(), ten = {10, 0, 0, 0},
                  tmp = init_zero_decimal();
      int exp = get_exponent(mod_res);
      for (int sub_stat = 0; !sub_stat; tmp = init_zero_decimal()) {
        sub_stat = stupid_mul(mod_res, ten, &tmp);
        if (!sub_stat) {
          mod_res = tmp;
          if (++exp < 29) set_exponent(&mod_res, exp);
        }
      }
      if (!get_exponent(mod_res)) set_exponent(&mod_res, 28);
      // d_print_decimal(mod_res);
      int_div(mod_res, value_2, &div_res);
      if (exp > 28) set_exponent(&div_res, exp - get_exponent(value_2));
      d_print_decimal(div_res);
      s21_add(div_res, *result, result);
    }
  } else if (get_sign(value_1) ^ get_sign(value_2))
    ++status;
  return status;
}
