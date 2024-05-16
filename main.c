#include "dynamic_strings.h"
#include <stdio.h>
#include <string.h>

int main()
{
  struct string a;

  /**
   * Create a new string
   */
  new_string(&a, "", 0); // Don't initialize a string 2x. 
  printf("%s %zu %zu\n", a.head, a.size, a.capacity);

  /**
   * Append one string to another string
   */
  append_string(&a, "Hello Worldy", strlen("Hello Worldy")); 
  printf("%s %zu %zu\n", a.head, a.size, a.capacity);

  append_string(&a, ", My name is theo lincke", strlen(", My name is theo lincke"));
  printf("%s %zu %zu\n", a.head, a.size, a.capacity);

  /**
   * Generate random strings
   */
  free_string(&a); // Every call to new_..._string should be paired with a call to free_string
  new_random_string(&a, 200);
  printf("%s %zu %zu\n", a.head, a.size, a.capacity);

  /**
   * Copy strings. [to] needs to be initialized (undefined behavior else)
   */
  struct string b;
  new_string(&b, "Foo bar", strlen("Foo bar"));
  copy_string(&a, &b);
  printf("%s %zu %zu\n", b.head, b.size, b.capacity);
  free_string(&b);

  /**
    * Delete elements from strings - can't delete more than size
    */
  delete_string(&a, 199);
  printf("%s %zu %zu\n", a.head, a.size, a.capacity);
  delete_string(&a, 20);
  printf("%s %zu %zu\n", a.head, a.size, a.capacity);

  free_string(&a);
  return 0;
}
