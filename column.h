#ifndef COLUMN_H
#define COLUMN_H

struct column {
    int phys_size;
    int log_size;
    int *data;
    char *title;
};
typedef struct column COLUMN;

COLUMN *create_column(char *title);

int insert_value(COLUMN *col, int value);

void delete_column(COLUMN *col);

void print_col(COLUMN *col);

int num_occurrences(COLUMN *col, int value);

int value_at_index(COLUMN *col, int index);

int num_values_greater(COLUMN *col, int value);

int num_values_smaller(COLUMN *col, int value);

#endif
