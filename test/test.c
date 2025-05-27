#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "vector.h"
#include "VectorErrors.h"
#include "double.h"
#include "Complex.h"
#include "integer.h"
#include <stdbool.h>

#define EPS 1e-9

bool compareVectors(Vector* v1, Vector* v2) {
    if (v1 == NULL || v2 == NULL) return false;
    if (v1->size != v2->size) return false;
    if (v1->typeInfo != v2->typeInfo) return false;

    for (int i = 0; i < v1->size; i++) {
        if (v1->typeInfo == GetDoubleTypeInfo()) {
            double val1 = ((double*)v1->data)[i];
            double val2 = ((double*)v2->data)[i];
            if (fabs(val1 - val2) >= EPS) {
                return false;
            }
        } else if (v1->typeInfo == GetIntTypeInfo()) {
            int val1 = ((int*)v1->data)[i];
            int val2 = ((int*)v2->data)[i];
            if (val1 != val2) {
                return false;
            }
        } else if (v1->typeInfo == GetComplexTypeInfo()) {
            Complex val1 = ((Complex*)v1->data)[i];
            Complex val2 = ((Complex*)v2->data)[i];
            if (fabs(val1.real - val2.real) >= EPS || fabs(val1.imag - val2.imag) >= EPS) {
                return false;
            }
        } else {
            // Неизвестный тип данных
            return false;
        }
    }

    return true;
}


int performInvalidOperation(Vector* v) {
    return OPERATION_NOT_DEFINED;
}

void testDoubleOperations() {
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6, 5.9, -6.1};
    VectorErrors operation_result;
    
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 4, &operation_result);
    Vector* v2 = createVector(GetDoubleTypeInfo(), a2, 4, &operation_result);
    Vector* v_res = createVector(GetDoubleTypeInfo(), malloc(4 * sizeof(double)), 4, &operation_result);
    
    if (errorsHandler(operation_result)) return; 

    operation_result = addVectors(v1, v2, v_res);
    if (errorsHandler(operation_result)) return;
    
    double expected_sum[] = {9.7, 1.6, 9.4, -1.3};
    Vector* expected_vector = createVector(GetDoubleTypeInfo(), expected_sum, 4, &operation_result);
    if (errorsHandler(operation_result)) return;
    
    if (!compareVectors(v_res, expected_vector)) {
        printf("Error in addition: result vector doesn't match expected values.\n");
    }
    freeVector(expected_vector);
    

    double scalar_result = 0.0;
    operation_result = multiplyVectors(v1, v2, &scalar_result);
    if (errorsHandler(operation_result)) return;
    
    double expected_scalar = -4.91;
    if (fabs(scalar_result - expected_scalar) >= EPS) {
        printf("Error in scalar multiplication\n");
    }
    
    double module_result = 0.0;
    operation_result = findAbs(v1, &module_result);
    if (errorsHandler(operation_result)) return;
    
    if (fabs(sqrt(module_result) - sqrt(40.98)) >= EPS) {
        printf("Error in module calculation\n");
    }

    freeVector(v1);
    freeVector(v2);
    freeVector(v_res);
}

void testMemoryAllocationFailure() {
    VectorErrors operation_result;
    Vector* v1 = createVector(GetDoubleTypeInfo(), NULL, 0, &operation_result);
    if (errorsHandler(operation_result)) return;
}

void testVectorNotDefined() {
    VectorErrors operation_result;
    Vector* v1 = NULL;
    double scalar_result = 0.0;
    operation_result = multiplyVectors(v1, v1, &scalar_result);
    if (errorsHandler(operation_result)) return;
}

void testOperationNotDefined() {
    VectorErrors operation_result;
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 4, &operation_result);
    if (errorsHandler(operation_result)) return;
    
    freeVector(v1);
}

void testIncompatibleVectors() {
    double a1[] = {1.3, -2.0, 3.5};
    Complex a2[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};
    VectorErrors operation_result;
    
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 3, &operation_result);
    Vector* v2 = createVector(GetComplexTypeInfo(), a2, 3, &operation_result);
    Vector* v_res = createVector(GetComplexTypeInfo(), malloc(4 * sizeof(double)), 3, &operation_result);
    if (errorsHandler(operation_result)) return;

    operation_result = addVectors(v1, v2, v_res);
    if (errorsHandler(operation_result)) return;
    
    freeVector(v1);
    freeVector(v2);
    freeVector(v_res);
}

void testDifferentLengthVectors() {
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6};
    VectorErrors operation_result;
    
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 4, &operation_result);
    Vector* v2 = createVector(GetDoubleTypeInfo(), a2, 2, &operation_result);
    Vector* v_res = createVector(GetDoubleTypeInfo(), malloc(4 * sizeof(double)), 4, &operation_result);
    if (errorsHandler(operation_result)) return;

    operation_result = addVectors(v1, v2, v_res);
    if (errorsHandler(operation_result)) return;
    
    freeVector(v1);
    freeVector(v2);
    freeVector(v_res);
}

void testEmptyVector() {
    VectorErrors operation_result;
    Vector* v = createVector(GetDoubleTypeInfo(), malloc(4 * sizeof(double)), 0, &operation_result);
    if (errorsHandler(operation_result)) return;
    if (v == NULL || v->size != 0) {
        printf("Error in empty vector creation\n");
    }
    freeVector(v);
}

int main() {
    testDoubleOperations();
    testMemoryAllocationFailure();
    testVectorNotDefined();
    testOperationNotDefined();
    testIncompatibleVectors();
    testDifferentLengthVectors();
    testEmptyVector();
    printf("All tests completed.\n");
    return 0;
}
