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

VectorList* create_vector_list();

void push_vector(VectorList* list, Vector* vector);

void remove_vector(VectorList* list, unsigned int index);


#endif 
