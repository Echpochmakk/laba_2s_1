#include <stdio.h>
#include <stdlib.h>
#include "Complex.h"

void complexAdd(const void* arg1, const void* arg2, void* result) {
    Complex* c1 = (Complex*)arg1;
    Complex* c2 = (Complex*)arg2;
    Complex* res = (Complex*)result;

    res->real = c1->real + c2->real;
    res->imag = c1->imag + c2->imag;
}

void complexMultiply(const void* arg1, const void* arg2, void* result) {
    Complex* c1 = (Complex*)arg1;
    Complex* c2 = (Complex*)arg2;
    Complex* scalarResult = (Complex*)result;

    scalarResult->real += c1->real * c2->real - c1->imag * c2->imag;
    scalarResult->imag += c1->real * c2->imag + c1->imag * c2->real;
}


void complexPrint(const void* data) {
    Complex* c = (Complex*)data;
    printf("%.3lf + %.3lfi", c->real, c->imag);
}

void complexabs(const void* arg, void* result){
    Complex* c1 = (Complex*)arg;
    Complex* absResult = (Complex*)result;

    absResult->real += c1->real * c1->real - c1->imag * c1->imag;
    absResult->imag += c1->real * c1->imag + c1->imag * c1->real;
}

TypeInfo* GetComplexTypeInfo() {
    if (COMPLEX_TYPE_INFO == NULL) {
        COMPLEX_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        if (!COMPLEX_TYPE_INFO) return NULL;
        COMPLEX_TYPE_INFO->size = sizeof(Complex);
        COMPLEX_TYPE_INFO->add = complexAdd;
        COMPLEX_TYPE_INFO->multiply = complexMultiply;
        COMPLEX_TYPE_INFO->print = complexPrint;
        COMPLEX_TYPE_INFO->abs = complexabs;
    }
    return COMPLEX_TYPE_INFO;
}
