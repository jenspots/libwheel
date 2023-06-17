#include "../impl/vec_int.h"

int main() {
    vec_vec_int matrix = vec_vec_int_init();

    for (uint64_t i = 0; i < 10; ++i) {
        vec_int row = vec_int_init();

        for (uint64_t j = 0; j < 10; ++j) {
            vec_int_set(&row, j, i + j);
        }

        vec_vec_int_set(&matrix, i, row);
    }

    for (uint64_t i = 0; i < 10; ++i) {
        for (uint64_t j = 0; j < 10; ++j) {
            optional_vec_int row = vec_vec_int_get(&matrix, i);
            assert(row.present);
            optional_int element = vec_int_get(&row.value, j);
            assert(element.present);
            assert(element.value == i + j);
        }
    }

    vec_vec_int_delete(&matrix);
}
