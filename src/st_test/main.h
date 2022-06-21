//
// Created by Nana Daughterless on 6/18/22.
//

#ifndef S21_DECIMAL_MAIN_H
#define S21_DECIMAL_MAIN_H


#define PYTHON "python3"
#define TRUNCATE_PATH " py_test/print_truncate_testcase.py"
#define ROUND_PATH " py_test/print_round_testcase.py"
#define FLOOR_PATH " py_test/print_floor_testcase.py"
#define NEGATE_PATH " py_test/print_negate_testcase.py"
#define DEC_TO_FLOAT_PATH " py_test/print_dec_to_float_testcase.py"

#define REDIRECT " >> "
#define REDIRECT_FILE "input"

#include "../s21_decimal.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EPS 1e-7

static long long cur_testcase = 0;
static char ** numbers;
static char ** results;

#define BUFFER_SIZE 1024

s21_decimal str2decimal(const char *number);

void generate_testcase(int count, char *command_path);
void free_testcase(int count);
void get_testcase(char **number, char **result);

// another
void run_truncate_test(int count);
void run_round_test(int count);
void run_floor_test(int count);
void run_negate_test(int count);

// conversion
void run_dec_to_float_test(int count);

#endif //S21_DECIMAL_MAIN_H
