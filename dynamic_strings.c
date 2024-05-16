//
// Created by Theo Lincke on 4/1/24.
//
#include "dynamic_strings.h"
#include "test_dynamic_strings.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Prints an error originating from dynamic strings
 * @param msg_fmt The format of the message
 * @param ... Extra parameters to feed into msg_format
 */
static void ds_error(const char* msg_fmt, ...)
{
  va_list args;
  va_start(args, msg_fmt);
  printf("c_dynamic_string error: ");
  vprintf(msg_fmt, args);
}

void free_string(struct string* string)
{
  if (string) {
    if (string->capacity && string->head) {
      free(string->head);
      string->head = NULL;
    }
  }
}

int test_free_string()
{
  struct string str;

  // Green path, never created
  free_string(&str);
  if (str.head)
    return TEST_FAILED;

  // Green path, just created
  new_string(&str, "fooz", 4);
  free_string(&str);
  if (str.head)
    return TEST_FAILED;

  // Green path, created and appended
  new_string(&str, "fooz", 4);
  append_string(&str, "foo", 3);
  free_string(&str);
  if (str.head)
    return TEST_FAILED;

  return TEST_PASSED;
}

/**
 * Doubles string capacity if capacity > 0, else, sets capacity to 2
 */
static int double_array_size(struct string* array)
{
  size_t new_capacity = array->capacity * 2;

  char* new_head = realloc(array->head, new_capacity + 1);
  if (new_head == NULL) {
    ds_error("Failed to increase string size in memory\n");
    return -1;
  }
  array->head = new_head;
  array->capacity = new_capacity;
  return 0;
}

int append_string(
    struct string* string,
    const char* elements,
    size_t elements_size)
{
  size_t new_size = string->size + elements_size;
  while (!(new_size <= string->capacity - 1))
    if (double_array_size(string))
      return -1;

  memcpy(string->head + string->size, elements, elements_size);

  string->size = new_size;
  string->head[string->size] = '\0';

  return 0;
}

int test_append_string()
{
  struct string str;
  new_string(&str, "", 0);
  if (append_string(&str, "f", 1))
    return TEST_FAILED;
  if (str.size != 1)
    return TEST_FAILED;
  if (str.head[1] != '\0')
    return TEST_FAILED;
  if (strcmp("f", str.head))
    return TEST_FAILED;

  if (append_string(&str, "foo", 3))
    return TEST_FAILED;
  if (str.size != 4)
    return TEST_FAILED;
  if (str.head[4] != '\0')
    return TEST_FAILED;
  if (strcmp("ffoo", str.head))
    return TEST_FAILED;

  if (append_string(&str, "foobarbizbuzbaz", 15))
    return TEST_FAILED;
  if (str.size != 19)
    return TEST_FAILED;
  if (str.head[19] != '\0')
    return TEST_FAILED;
  if (strcmp("ffoofoobarbizbuzbaz", str.head))
    return TEST_FAILED;

  return TEST_PASSED;
}

int delete_string(struct string* string, size_t num_elements)
{
  if (num_elements > string->size) {
    ds_error("Trying to remove %zu elements, "
             "but string has %zu elements\n",
        num_elements, string->size);
    return -1;
  }

  string->size -= num_elements;
  string->head[string->size] = '\0';

  return 0;
}

int test_delete_string()
{
  struct string str;
  new_string(&str, "", 0);
  if (!delete_string(&str, 1))
    return TEST_FAILED;
  if (delete_string(&str, 0))
    return TEST_FAILED;

  append_string(&str, "fooz", 4);

  // Green path - delete 0 char from len 4
  if (delete_string(&str, 0))
    return TEST_FAILED;
  if (str.size != 4)
    return TEST_FAILED;
  if (str.head[4] != '\0')
    return TEST_FAILED;
  if (strcmp("fooz", str.head))
    return TEST_FAILED;

  // Green path - delete 1 char from len 4
  if (delete_string(&str, 1))
    return TEST_FAILED;
  if (str.size != 3)
    return TEST_FAILED;
  if (str.head[3] != '\0')
    return TEST_FAILED;
  if (strcmp("foo", str.head))
    return TEST_FAILED;

  // Green path - delete 2 char from len 3
  if (delete_string(&str, 2))
    return TEST_FAILED;
  if (str.size != 1)
    return TEST_FAILED;
  if (str.head[1] != '\0')
    return TEST_FAILED;
  if (strcmp("f", str.head))
    return TEST_FAILED;

  append_string(&str, "bar", 3);

  // Red path - delete 5 char from len 4
  if (!delete_string(&str, 5))
    return TEST_FAILED;
  if (str.size != 4)
    return TEST_FAILED;
  if (str.head[4] != '\0')
    return TEST_FAILED;
  if (strcmp("fbar", str.head))
    return TEST_FAILED;

  // Green path - delete 4 char from len 4
  if (delete_string(&str, 4))
    return TEST_FAILED;
  if (str.size != 0)
    return TEST_FAILED;
  if (str.head[0] != '\0')
    return TEST_FAILED;

  return TEST_PASSED;
}

static char random_alpha_numeric_char()
{
  return (char)((long)'a' + (rand() % 26));
}

static int string_init(struct string* str, size_t initial_capacity)
{
  memset(str, 0, sizeof(struct string));

  if (initial_capacity < 1) {
    ds_error("Initial string capacity must be > 0\n");
    return -1;
  }

  str->head = malloc(initial_capacity);
  if (!str->head) {
    ds_error("Failed to allocate memory for string in string_init\n");
    return -1;
  }
  str->capacity = initial_capacity;
  return 0;
}

int new_string(struct string* str, const char* elements, size_t num_elements)
{
  size_t cap = num_elements == 0 ? 1 : num_elements * 2;
  if (string_init(str, cap))
    return -1;

  if (append_string(str, elements, num_elements))
    return -1;

  return 0;
}

static int test_string_init()
{
  // Green path size 10
  struct string str;
  if (string_init(&str, 10))
    return TEST_FAILED;
  if (str.capacity != 10)
    return TEST_FAILED;
  if (str.size != 0)
    return TEST_FAILED;
  if (!str.head)
    return TEST_FAILED;

  // Green path size 1
  free_string(&str);
  if (string_init(&str, 1))
    return TEST_FAILED;
  if (str.capacity != 1)
    return TEST_FAILED;
  if (str.size != 0)
    return TEST_FAILED;
  if (!str.head)
    return TEST_FAILED;

  // Red path size 0
  free_string(&str);
  memset(&str, 0, sizeof(struct string));
  if (!string_init(&str, 0))
    return TEST_FAILED;
  // make sure no mallocs are called on error
  if (str.head)
    return TEST_FAILED;

  return TEST_PASSED;
}

int test_new_string()
{
  int ret = test_string_init();

  if (ret != TEST_PASSED)
    return ret;

  struct string str;
  if (new_string(&str, "foo", 3))
    return TEST_FAILED;

  return TEST_PASSED;
}

int new_random_string(struct string* string, size_t num_elements)
{
  if (string_init(string, num_elements))
    return -1;

  char* elem = malloc(num_elements * sizeof(char));
  if (!elem) {
    ds_error("Failed to allocate random string\n");
    return -1;
  }

  for (int i = 0; i < num_elements; ++i)
    elem[i] = random_alpha_numeric_char();

  if (new_string(string, elem, num_elements)) {
    free(elem);
    return -1;
  }

  free(elem);
  return 0;
}

int test_new_random_string()
{
  int ret = test_string_init();
  if (ret != TEST_PASSED)
    return ret;

  struct string str;
  if (new_random_string(&str, 3))
    return TEST_FAILED;

  return TEST_PASSED;
}

int copy_string(const struct string* from, struct string* to)
{
  free_string(to);
  return new_string(to, from->head, from->size);
}

int test_copy_string()
{
  struct string from;
  struct string to;
  new_string(&to, "", 0);
  new_string(&from, "foo", 3);

  // Green path - Works with uninitialized string to
  if (copy_string(&from, &to))
    return TEST_FAILED;
  if (from.size != to.size)
    return TEST_FAILED;
  if (strcmp(from.head, to.head))
    return TEST_FAILED;

  free_string(&to);

  // Green path - Works with initialized string to
  new_string(&to, "barz", 4);
  if (copy_string(&from, &to))
    return TEST_FAILED;
  if (from.size != to.size)
    return TEST_FAILED;
  if (strcmp(from.head, to.head))
    return TEST_FAILED;

  return TEST_PASSED;
}
