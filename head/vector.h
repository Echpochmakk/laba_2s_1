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
void freeVector(Vector* v);
VectorErrors addVectors(const Vector* v1, const Vector* v2, Vector* result);
VectorErrors multiplyVectors(const Vector* v1, const Vector* v2, void* result);
VectorErrors printVector(const Vector* v);
VectorErrors findAbs(const Vector* v, void* result);
VectorErrors rewriteVector(TypeInfo* new_typeInfo, Vector *v, int new_size, void *new_data);

#endif
