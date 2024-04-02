#include <stdio.h>
#include <string.h>
#include "dynamic_strings.h"

int main() {
    struct string a;
    create_string(&a, 10);
    append_string(&a, "Hello Worldy", strlen("Hello Worldy"));
    printf("%s %zu %zu\n", a.head, a.size, a.capacity);
    append_string(&a, " My name is theo lincke", strlen(" My name is theo lincke"));
    printf("%s %zu %zu\n", a.head, a.size, a.capacity);
    new_random_string(&a, 200);
    printf("%s %zu %zu\n", a.head, a.size, a.capacity);
    delete_string(&a, 199);
    printf("%s %zu %zu\n", a.head, a.size, a.capacity);
    delete_string(&a, 20);
    printf("%s %zu %zu\n", a.head, a.size, a.capacity);
    destroy_string(&a);
    return 0;
}
