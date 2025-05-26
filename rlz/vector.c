#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "VectorErrors.h"

Vector* createVector(TypeInfo* typeInfo, void *data, int size, VectorErrors* operationResult){
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    if (vector == NULL) {
        *operationResult = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    vector->typeInfo = typeInfo;
    vector->size = size;
    vector->data = malloc(typeInfo->size * vector->size);
    if (vector->data == NULL) {
        *operationResult = MEMORY_ALLOCATION_FAILED;
        free(vector);
        return NULL;
    }
    
    if (data != NULL) {
        memcpy(vector->data, data, typeInfo->size * vector->size);
    }

    *operationResult = VECTOR_OPERATION_OK;
    return vector;
}

void free_vector(Vector* v) {
    if (v) {
        free(v->data);
        free(v);
    }
}

VectorErrors add_vectors(const Vector* v1, const Vector* v2, Vector* result) {
    if (v1 == NULL || v2 == NULL || result == NULL) return VECTOR_NOT_DEFINED;
    if (v1->typeInfo != v2->typeInfo || v1->typeInfo != result->typeInfo) return INCOMPATIBLE_VECTOR_TYPES;
    if (v1->size != v2->size) return DIFFERENT_LENGHT_VECTORS;
    if (v1->typeInfo->add == NULL) return OPERATION_NOT_DEFINED;

    for (int i = 0; i < v1->size; i++) {
        v1->typeInfo->add(
            (char*)v1->data + i * v1->typeInfo->size,
            (char*)v2->data + i * v1->typeInfo->size,
            (char*)result->data + i * v1->typeInfo->size
        );
    }

    return VECTOR_OPERATION_OK;
}

VectorErrors multiply_vectors(const Vector* v1, const Vector* v2, void* result) {
    if (v1 == NULL || v2 == NULL || result == NULL) return VECTOR_NOT_DEFINED;
    if (v1->typeInfo != v2->typeInfo) return INCOMPATIBLE_VECTOR_TYPES;
    if (v1->size != v2->size) return DIFFERENT_LENGHT_VECTORS;
    if (v1->typeInfo->multiply == NULL) return OPERATION_NOT_DEFINED;
    
    memset(result, 0, v1->typeInfo->size);
    for(int i=0; i<v1->size; i++){
        void* arg1 = (char*)v1->data + i * v1->typeInfo->size;
        void* arg2 = (char*)v2->data + i * v2->typeInfo->size;
        void* temp_result = malloc(v1->typeInfo->size);
        if (temp_result == NULL) return MEMORY_ALLOCATION_FAILED; 
        v1->typeInfo->multiply(arg1, arg2, temp_result);  
        v1->typeInfo->add(result, temp_result, result);
        free(temp_result); 
    }
    return VECTOR_OPERATION_OK;
}



VectorErrors print_vector(const Vector* vector) {
    if (vector == NULL) return VECTOR_NOT_DEFINED;
    if (vector->typeInfo->print == NULL) return OPERATION_NOT_DEFINED;

    printf("Vector: (");
    for (int i = 0; i < vector->size; i++) {
        vector->typeInfo->print((char*)vector->data + i * vector->typeInfo->size);
        if (i < vector->size - 1) {
            printf(", ");
        }
    }
    printf(")");

    return VECTOR_OPERATION_OK;
}

VectorErrors find_abs(const Vector* vector, void* result){
    if (vector == NULL || result == NULL) return VECTOR_NOT_DEFINED;
    if (vector->typeInfo->abs == NULL) return OPERATION_NOT_DEFINED;
    
    for(int i=0; i < vector->size; i++){
        void* val = (char*)vector->data + i * vector->typeInfo->size;
        vector->typeInfo->abs(val, result);
    }

    return VECTOR_OPERATION_OK;
}

VectorErrors rewrite_vector(TypeInfo* new_typeInfo, Vector *v, int new_size, void *new_data){
    if (v == NULL || new_data == NULL) return VECTOR_NOT_DEFINED;
    free(v->data);
    v->typeInfo = new_typeInfo;
    v->size = new_size;
    v->data =  malloc(new_typeInfo->size * v->size);
    if (v->data == NULL) return VECTOR_NOT_DEFINED;
    memcpy(v->data, new_data, new_size * new_typeInfo->size);
    return VECTOR_OPERATION_OK;
}