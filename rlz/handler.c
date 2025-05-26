#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handler.h"
#include "VectorErrors.h"
#include <math.h>

VectorList* create_vector_list() {
    VectorList* list = malloc(sizeof(VectorList));
    list->size = 0;
    list->capacity = 4;
    list->items = malloc(sizeof(Vector*) * list->capacity);
    return list;
}

void push_vector(VectorList* list, Vector* vector) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->items = realloc(list->items, sizeof(Vector*) * list->capacity);
    }
    list->items[list->size++] = vector;
}

void remove_vector(VectorList* list, unsigned int index) {
    if (index >= list->size) return;
    free_vector(list->items[index]);
    for (unsigned int i = index; i < list->size - 1; i++) {
        list->items[i] = list->items[i + 1];
    }
    list->size--;
}

void startInterface() {
    VectorList* vector_list = create_vector_list();
    VectorErrors operation_result;

    while (1) {
        printf("\nChoose operation:\n");
        printf("1 - Addition\n");
        printf("2 - Scalar Product\n");
        printf("3 - Norm\n");
        printf("4 - Show all vectors\n");
        printf("5 - Modify a vector\n");
        printf("6 - Add a vector\n");
        printf("7 - Remove a vector\n");
        printf("8 - Exit\n");

        short operation;
        while (scanf("%hd", &operation) != 1 || operation < 1 || operation > 8) {
            printf("Invalid choice. Try again: ");
            while (getchar() != '\n');
        }

        unsigned int index1, index2;

        switch (operation) {
            case 1: // Addition
                if (vector_list->size < 2) {
                    printf("At least two vectors are required.\n");
                    break;
                }
                printf("Enter indices of two vectors to add (1 to %u): ", vector_list->size);
                while (scanf("%u %u", &index1, &index2) != 2 || index1 < 1 || index2 < 1 || index1 > vector_list->size || index2 > vector_list->size) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }

                index1--; index2--;
                Vector* add_result = createVector(
                    vector_list->items[index1]->typeInfo,
                    malloc(vector_list->items[index1]->size * vector_list->items[index1]->typeInfo->size),
                    vector_list->items[index1]->size,
                    &operation_result
                );
                if (errors_handler(add_vectors(vector_list->items[index1], vector_list->items[index2], add_result))) {
                    break;
                }

                printf("Result of addition:\n");
                print_vector(add_result);
                free_vector(add_result);
                break;

            case 2: // Scalar Product
                if (vector_list->size < 2) {
                    printf("At least two vectors are required.\n");
                    break;
                }
                printf("Enter indices of two vectors (1 to %u): ", vector_list->size);
                while (scanf("%u %u", &index1, &index2) != 2 || index1 < 1 || index2 < 1 || index1 > vector_list->size || index2 > vector_list->size) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }

                index1--; index2--;
                void* scalar_result = malloc(vector_list->items[index1]->typeInfo->size);
                if (errors_handler(multiply_vectors(vector_list->items[index1], vector_list->items[index2], scalar_result))) {
                    break;
                }

                printf("Scalar product result: ");
                vector_list->items[index1]->typeInfo->print(scalar_result);
                printf("\n");
                free(scalar_result);
                break;

            case 3: { // Norm
                if (vector_list->size == 0) {
                    printf("No vectors available.\n");
                    break;
                }
                unsigned short idx;
                printf("Enter vector index (1 to %u): ", vector_list->size);
                while (scanf("%hu", &idx) != 1 || idx < 1 || idx > vector_list->size) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }

                double pre_norm = 0;
                if (errors_handler(find_abs(vector_list->items[idx - 1], &pre_norm))) {
                    break;
                }

                printf("Vector norm: %.4lf\n", sqrt(pre_norm));
                break;
            }

            case 4: // Show all vectors
                if (vector_list->size == 0) {
                    printf("No vectors to display.\n");
                    break;
                }

                for (unsigned int i = 0; i < vector_list->size; i++) {
                    printf("Vector %u:\n", i + 1);
                    print_vector(vector_list->items[i]);
                    printf("\n");
                }
                break;

            case 5: { // Modify vector
                if (vector_list->size == 0) {
                    printf("No vectors to modify.\n");
                    break;
                }

                printf("Enter vector index (1 to %u): ", vector_list->size);
                while (scanf("%u", &index1) != 1 || index1 < 1 || index1 > vector_list->size) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }

                index1--;

                printf("Choose new type: 1 - Double, 2 - Complex, 3 - Integer: ");
                int new_type;
                while (scanf("%d", &new_type) != 1 || new_type < 1 || new_type > 3) {
                    printf("Invalid choice. Try again: ");
                    while (getchar() != '\n');
                }

                TypeInfo* new_typeInfo = NULL;
                if (new_type == 1) new_typeInfo = GetDoubleTypeInfo();
                else if (new_type == 2) new_typeInfo = GetComplexTypeInfo();
                else new_typeInfo = GetIntTypeInfo();

                int new_size;
                printf("Enter new vector size: ");
                while (scanf("%d", &new_size) != 1 || new_size <= 0) {
                    printf("Invalid size. Try again: ");
                    while (getchar() != '\n');
                }

                void* new_data = malloc(new_size * new_typeInfo->size);
                printf("Enter coordinates (%s):\n", (new_type == 2) ? "real imag pairs" : "one per element");

                for (int j = 0; j < new_size; j++) {
                    switch (new_type) {
                        case 1:
                            while (scanf("%lf", (double*)((char*)new_data + j * new_typeInfo->size)) != 1) {
                                printf("Invalid input. Try again: ");
                                while (getchar() != '\n');
                            }
                            break;
                        case 2: {
                            Complex* z = (Complex*)((char*)new_data + j * new_typeInfo->size);
                            while (scanf("%lf %lf", &z->real, &z->imag) != 2) {
                                printf("Invalid complex input. Try again: ");
                                while (getchar() != '\n');
                            }
                            break;
                        }
                        case 3:
                            while (scanf("%d", (int*)((char*)new_data + j * new_typeInfo->size)) != 1) {
                                printf("Invalid input. Try again: ");
                                while (getchar() != '\n');
                            }
                            break;
                    }
                }

                if (errors_handler(rewrite_vector(new_typeInfo, vector_list->items[index1], new_size, new_data))) {
                    break;
                }

                free(new_data);
                printf("Vector modified.\n");
                break;
            }

            case 6: { // Add vector
                int data_type;
                printf("Choose data type:\n1 - Double\n2 - Complex\n3 - Integer\n");
                while (scanf("%d", &data_type) != 1 || data_type < 1 || data_type > 3) {
                    printf("Invalid choice. Try again: ");
                    while (getchar() != '\n');
                }

                TypeInfo* type_info = NULL;
                if (data_type == 1) type_info = GetDoubleTypeInfo();
                else if (data_type == 2) type_info = GetComplexTypeInfo();
                else type_info = GetIntTypeInfo();

                int size;
                printf("Enter vector size: ");
                while (scanf("%d", &size) != 1 || size <= 0) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }

                void* data = malloc(size * type_info->size);
                printf("Enter coordinates (%s):\n", (data_type == 2) ? "real imag pairs" : "one per element");

                for (int j = 0; j < size; j++) {
                    switch (data_type) {
                        case 1:
                            while (scanf("%lf", (double*)((char*)data + j * type_info->size)) != 1) {
                                printf("Invalid input. Try again: ");
                                while (getchar() != '\n');
                            }
                            break;
                        case 2: {
                            Complex* z = (Complex*)((char*)data + j * type_info->size);
                            while (scanf("%lf %lf", &z->real, &z->imag) != 2) {
                                printf("Invalid input. Try again: ");
                                while (getchar() != '\n');
                            }
                            break;
                        }
                        case 3:
                            while (scanf("%d", (int*)((char*)data + j * type_info->size)) != 1) {
                                printf("Invalid input. Try again: ");
                                while (getchar() != '\n');
                            }
                            break;
                    }
                }

                Vector* new_vector = createVector(type_info, data, size, &operation_result);
                if (errors_handler(operation_result)) break;
                push_vector(vector_list, new_vector);
                printf("Vector added successfully.\n");
                break;
            }

            case 7: { // Remove vector
                if (vector_list->size == 0) {
                    printf("No vectors to remove.\n");
                    break;
                }

                printf("Enter index of vector to remove (1 to %u): ", vector_list->size);
                while (scanf("%u", &index1) != 1 || index1 < 1 || index1 > vector_list->size) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }

                remove_vector(vector_list, index1 - 1);
                printf("Vector removed.\n");
                break;
            }

            case 8: // Exit
                printf("Goodbye!\n");
                for (unsigned int i = 0; i < vector_list->size; i++) {
                    free_vector(vector_list->items[i]);
                }
                free(vector_list->items);
                free(vector_list);
                return;
        }
    }
}
