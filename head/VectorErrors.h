#ifndef VECTORERRORS_H
#define VECTORERRORS_H

#include <stdio.h>

typedef enum {
    VECTOR_OPERATION_OK = 0,
    MEMORY_ALLOCATION_FAILED = 100,
    VECTOR_NOT_DEFINED = 200,
    OPERATION_NOT_DEFINED = 201,
    INCOMPATIBLE_VECTOR_TYPES = 300,
    DIFFERENT_LENGHT_VECTORS = 301
} VectorErrors;

typedef struct {
    VectorErrors code;
    const char* message;
} VectorErrorEntry;

static const VectorErrorEntry vector_error_table[] = {
    { MEMORY_ALLOCATION_FAILED,     "ERROR: memory allocation failed." },
    { VECTOR_NOT_DEFINED,           "ERROR: vector is not defined." },
    { OPERATION_NOT_DEFINED,        "ERROR: operation is not defined." },
    { INCOMPATIBLE_VECTOR_TYPES,    "ERROR: incompatible vector types." },
    { DIFFERENT_LENGHT_VECTORS,     "ERROR: different length of vectors." }
};

static const char* get_vector_error_message(VectorErrors code) {
    size_t count = sizeof(vector_error_table) / sizeof(vector_error_table[0]);
    for (size_t i = 0; i < count; ++i) {
        if (vector_error_table[i].code == code) {
            return vector_error_table[i].message;
        }
    }
    return "ERROR: unknown error.";
}

static inline int errors_handler(VectorErrors operation_result) {
    if (operation_result != VECTOR_OPERATION_OK) {
        fprintf(stderr, "%s\n", get_vector_error_message(operation_result));
        return 1;
    }
    return 0;
}

#endif
