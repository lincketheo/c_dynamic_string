# Version 0.0.1

**State:** Pretty good. Just gotta add real tests

**Need to do Features:**

- Add real tests

# Usage:

The main object you're working with is `string`

Before using a string, you must `create_string` and after, you must `destroy_string`

Available API methods:

- `reset_string`
- `append_string`
- `delete_string`
- `new_random_string`
- `copy_string`

```c

#include
<stdio.h>
#include
<string.h> // strlen
#include
"dynamic_strings.h"

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

```