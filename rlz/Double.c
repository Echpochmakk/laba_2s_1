#include "double.h"

void doubleAdd(const void* arg1, const void* arg2, void* result) {
    *(double*)result = *(double*)arg1 + *(double*)arg2;
}

void doubleMultiply(const void* arg1, const void* arg2, void* result) {
    *(double*)result = *(double*)arg1 * *(double*)arg2;
}


void doublePrint(const void* data) {
    printf("%.3lf", *(const double*)data);
}

void doubleAbs(const void* arg, void* result){
    double* d1 = (double*)arg;
    double* absResult = (double*)result;

    *absResult += (*d1) * (*d1);
}

TypeInfo* GetDoubleTypeInfo() {
    if (DOUBLE_TYPE_INFO == NULL) {
        DOUBLE_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        if (!DOUBLE_TYPE_INFO) return NULL;
        DOUBLE_TYPE_INFO->size = sizeof(double);
        DOUBLE_TYPE_INFO->add = doubleAdd;
        DOUBLE_TYPE_INFO->multiply = doubleMultiply;
        DOUBLE_TYPE_INFO->print = doublePrint;
        DOUBLE_TYPE_INFO->abs = doubleAbs;
    }
    return DOUBLE_TYPE_INFO;
}
