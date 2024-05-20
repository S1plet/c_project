// This file contains all the functions associated to the columns

#include <stdio.h>
#include <stdlib.h>
#include "column.h"
#include <string.h>
#define REALLOC_SIZE 256


// Create a columns
COLUMN* create_column(char* title) {
    COLUMN* ptr = malloc(sizeof(COLUMN));
    if (ptr == NULL) {
        printf("Memory allocation failed...\n");
        return NULL;
    }
    // Allocate memory for the title
    ptr->title = malloc(strlen(title) + 1); // "strlen(title)+1" as we take the last element "\0" into account
    if (ptr->title == NULL) {
        printf("Memory allocation failed...\n");
        free(ptr); // Frees allocated COLUMN structure's memory
        return NULL;
    }
    strcpy(ptr->title, title); // Fills the title by the one enterd by the user (not working with " = ")
    ptr->phys_size = 0;
    ptr->log_size = 0;
    ptr->data = NULL;
    return ptr;
}

// Allows to insert a value in a column
int insert_value(COLUMN* col, int value) {
    if (col->phys_size == 0) {
        col->data = (int*)malloc(REALLOC_SIZE * sizeof(int)); // Allocates memory for 256 integers
        if (col->data == NULL) {
            return 0;
        }
        col->phys_size = REALLOC_SIZE;
    }
    else if (col->log_size == col->phys_size) {
        int* temp = (int*)realloc(col->data, (col->phys_size + REALLOC_SIZE) * sizeof(int)); // Temp contains the memory of "col" + the memory of 256 new integers
        if (temp == NULL) {
            return 0;
        }
        else {
            col->data = temp;
            col->phys_size += REALLOC_SIZE; // Updates physical size
        }
    }
    col->data[col->log_size] = value;
    col->log_size++; // Updates logical size
    return 1;
}

// Deletes the column
void delete_column(COLUMN* col) { // Frees the data THEN the column itself as "col->data" memory would still be stored if only "col" was freed
    free(col->data);
    free(col);
}

// Displays the column
void print_col(COLUMN* col) {
    for (int i = 0; i < col->log_size; i++) {
        printf("[%d] [%d]\n", i, col->data[i]); // Displays columns as following : [index] [associated_value]
    }
}

// Counts the number of occurrence of a same value
int nb_occurrences(COLUMN* col, int value) {
    int cpt = 0;
    for (int i = 0; i < col->log_size; i++) {
        if (col->data[i] == value) {
            cpt++;
        }
    }
    return cpt;
}

// Returns the value from a given index
int value_at_index(COLUMN* col, int index) {
    return col->data[index];
}
// Returns the number of values greater than the one given
int nb_values_greater(COLUMN* col, int value) {
    int nbVal = 0;
    for (int i = 0; i < col->log_size; i++) {
        if (col->data[i] > value) {
            nbVal++;
        }
    }
    return nbVal;
}
// Returns the number of values smaller than the one given
int nb_values_smaller(COLUMN* col, int value) {
    int nbVal = 0;
    for (int i = 0; i < col->log_size; i++) {
        if (col->data[i] < value) {
            nbVal++;
        }
    }
    return nbVal;
}
