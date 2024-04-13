#include "../impl/string.h"

int main() {
    char* hello = strdup("Hello, world!");

    rc_string p1 = rc_string_init(hello);
    assert(*p1.counter == 1);

    rc_string p2 = rc_string_copy(p1);
    assert(*p1.counter == 2);
    assert(*p2.counter == 2);

    rc_string_destroy(p1);
    assert(*p2.counter == 1);

    rc_string_destroy(p2);
    // TODO: Check manually with valgrind for memory leaks.
}
