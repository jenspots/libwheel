#include <assert.h>
#include <wheel/std/int.h>

void test_simple() {
    // Create vector [0, 1, 2, 3, 4].
    vec_int v = vec_int_init();
    for (int i = 0; i < 5; ++i) {
        vec_int_set(&v, i, i);
    }

    // Serialize to JSON.
    uint64_t output_size = vec_int_serialize_json(&v, NULL);
    char* output = malloc(output_size * sizeof(char));
    vec_int_serialize_json(&v, output);
    vec_int_destroy(&v);

    // Check the output.
    assert(strcmp(output, "[0,1,2,3,4]") == 0);
}

void test_empty() {
    // Create empty vector.
    vec_int v = vec_int_init();

    // Serialize to JSON.
    uint64_t output_size = vec_int_serialize_json(&v, NULL);
    char* output = malloc(output_size * sizeof(char));
    vec_int_serialize_json(&v, output);
    vec_int_destroy(&v);

    // Check the output.
    assert(strcmp(output, "[]") == 0);
}

void test_single_element() {
    // Create empty vector.
    vec_int v = vec_int_init();
    vec_int_set(&v, 0, 5);

    // Serialize to JSON.
    uint64_t output_size = vec_int_serialize_json(&v, NULL);
    char* output = malloc(output_size * sizeof(char));
    vec_int_serialize_json(&v, output);
    vec_int_destroy(&v);

    // Check the output.
    assert(strcmp(output, "[5]") == 0);
}

int main() {
    test_empty();
    test_single_element();
    test_simple();
}
