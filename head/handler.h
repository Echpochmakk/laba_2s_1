#ifndef HANDLER_H
#define HANDLER_H

#include "vector.h"
#include "Complex.h"
#include "Double.h"
#include "Integer.h"

void startInterface();

typedef struct {
    Vector** items;
    unsigned int size;
    unsigned int capacity;
} VectorList;

VectorList* createVectorList();

void pushVector(VectorList* list, Vector* vector);

void removeVector(VectorList* list, unsigned int index);


#endif 
