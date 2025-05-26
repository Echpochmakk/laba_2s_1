#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include "TypeInfo.h"
#include "Integer.h"
#include "Double.h"
#include "Complex.h"
#include "VectorErrors.h"

typedef struct {
    void **data;
    TypeInfo* typeInfo;   
    int size;
} Vector;


Vector* createVector(TypeInfo* typeInfo, void *data, int size, VectorErrors* operationResult);
void free_vector(Vector* v);
VectorErrors add_vectors(const Vector* v1, const Vector* v2, Vector* result);
VectorErrors multiply_vectors(const Vector* v1, const Vector* v2, void* result);
VectorErrors print_vector(const Vector* v);
VectorErrors find_abs(const Vector* v, void* result);
VectorErrors rewrite_vector(TypeInfo* new_typeInfo, Vector *v, int new_size, void *new_data);

#endif
