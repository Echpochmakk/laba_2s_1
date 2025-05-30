#ifndef COMPLEX_H
#define COMPLEX_H

#include "TypeInfo.h"

typedef struct {
    double real;
    double imag;
} Complex;

extern TypeInfo* COMPLEX_TYPE_INFO;


void complexAdd(const void* arg1, const void* arg2, void* result);
void complexMultiply(const void* arg1, const void* arg2, void* result);
void complexPrint(const void* data);
void complexAbs(const void* arg, void* result);
TypeInfo* GetComplexTypeInfo();

#endif 
