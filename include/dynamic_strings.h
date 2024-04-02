//
// Created by Theo Lincke on 4/1/24.
//

#ifndef DYNAMIC_STRINGS_H
#define DYNAMIC_STRINGS_H

#include <stdlib.h>

struct string {
    char *head;
    size_t size;
    size_t capacity;
};

void create_string(struct string *string, size_t initial_capacity);

void destroy_string(struct string *string);

void reset_string(struct string *string);

void append_string(struct string *string, const char *elements, size_t elements_size);

void delete_string(struct string *string, size_t num_elements);

void new_random_string(struct string *string, size_t num_elements);

void copy_string(const struct string *from, struct string *to);

#endif //DYNAMIC_STRINGS_H
