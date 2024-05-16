//
// Created by Theo Lincke on 4/1/24.
//

#ifndef DYNAMIC_STRINGS_H
#define DYNAMIC_STRINGS_H

#include <stdlib.h>

/**
 * @var head - The data buffer
 * @var capacity - The length of head
 * @var size - The size of the string, which is <= capacity - 1
 * due to null terminator. size does not include null terminator
 *
 * @note head is always a char array of length capacity.
 * capacity is always >= 2
 *
 * @note capacity never shrinks (yet - there's been no need, maybe in the future?)
 */
struct string {
  char* head;
  size_t size;
  size_t capacity;
};

void free_string(struct string* string);

int append_string(struct string* string, const char* elements, size_t elements_size);

int delete_string(struct string* string, size_t num_elements);

int new_string(struct string* string, const char* elements, size_t num_elements);

int new_random_string(struct string* string, size_t num_elements);

int copy_string(const struct string* from, struct string* to);

#endif // DYNAMIC_STRINGS_H
