//
// Created by Theo Lincke on 4/1/24.
//

#ifndef TEST_DYNAMIC_STRINGS_H
#define TEST_DYNAMIC_STRINGS_H

#include "dynamic_strings.h"
#include <stdlib.h>

#define TEST_PASSED 0
#define TEST_FAILED -1

int test_free_string();

int test_append_string();

int test_delete_string();

int test_new_string();

int test_new_random_string();

int test_copy_string();

#endif // TEST_DYNAMIC_STRINGS_H
