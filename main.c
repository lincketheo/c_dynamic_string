#include <stdio.h>
#include <dynamic_strings.h>

int main() {
    struct string a;
    create_string(&a, 10);
    append_string(&a, "Hello Worldy", sizeof("Hello Worldy"));
    printf("%s\n", a.head);
    append_string(&a, " My name is theo lincke", sizeof(" My name is theo lincke"));
    printf("%s\n", a.head);
    new_random_string(&a, 200);
    printf("%s\n", a.head);
    destroy_string(&a);
    return 0;
}
