#include "integer.h"

void intAdd(const void* arg1, const void* arg2, void* result) {
    *(int*)result = *(int*)arg1 + *(int*)arg2;
}

void intMultiply(const void* arg1, const void* arg2, void* result) {
    *(int*)result = *(int*)arg1 * *(int*)arg2;
}



void intPrint(const void* data) {
    printf("%d", *(const int*)data);
}

void intabs(const void* arg, void* result){
    int* i1 = (int*)arg;
    double* absResult = (double*)result;

    *absResult += (*i1) * (*i1);
}

TypeInfo* GetIntTypeInfo() {
    if (INT_TYPE_INFO == NULL) {
        INT_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        if (!INT_TYPE_INFO) return NULL;
        INT_TYPE_INFO->size = sizeof(int);
        INT_TYPE_INFO->add = intAdd;
        INT_TYPE_INFO->multiply = intMultiply;
        INT_TYPE_INFO->print = intPrint;
        INT_TYPE_INFO->abs = intabs;
    }
    return INT_TYPE_INFO;
}
