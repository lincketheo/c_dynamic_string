#include "test_dynamic_strings.h"
#include <stdio.h>
#include <string.h>

int main()
{
  if (test_new_string() != TEST_PASSED)
    printf("test_new_string Failed!\n");
  if (test_copy_string() != TEST_PASSED)
    printf("test_copy_string Failed!\n");
  if (test_append_string() != TEST_PASSED)
    printf("test_append_string Failed!\n");
  if (test_delete_string() != TEST_PASSED)
    printf("test_delete_string Failed!\n");
  if (test_free_string() != TEST_PASSED)
    printf("test_free_string Failed!\n");
  if (test_new_random_string() != TEST_PASSED)
    printf("test_new_random_string Failed!\n");
  return 0;
}
