//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_comparison.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  //   balancing(&a, &b);

  bool res = get_sign(a) == get_sign(b);
  res = res && get_exponent(a) == get_exponent(b);
  res = res && a.bits[0] == b.bits[0];
  res = res && a.bits[1] == b.bits[1];
  res = res && a.bits[2] == b.bits[2];

  return res;
}
