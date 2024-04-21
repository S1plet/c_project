#ifndef CDATAFRAME_H
#define CDATAFRAME_H

struct dataframe{
    COLUMN **columns;
    int num_columns;
};
typedef struct dataframe DATAFRAME;

DATAFRAME *create_dataframe(int num_columns);

void fill_dataframe(DATAFRAME *dataframe);

void hardfill_dataframe(DATAFRAME *dataframe, int num_rows);

void display_dataframe(DATAFRAME *dataframe);

void display_partial_dataframe_rows(DATAFRAME *dataframe, int num_rows);

void display_partial_dataframe_columns(DATAFRAME *dataframe, int num_columns);

void add_row(DATAFRAME *dataframe, int *row);

void delete_row(DATAFRAME *dataframe, int row_index);

void add_column(DATAFRAME *dataframe);

void delete_column_at_index(DATAFRAME *dataframe, int column_index);

void rename_column(DATAFRAME *dataframe, int column_index, const char* title);

void check_if_value_in_dataframe(DATAFRAME *dataframe, int value);

void replace_value(DATAFRAME *dataframe, int column_index, int row_index, int value);

int get_value(DATAFRAME *dataframe, int column_index, int row_index);

void display_column_names(DATAFRAME *dataframe);

void display_number_of_rows(DATAFRAME *dataframe);

void display_number_of_columns(DATAFRAME *dataframe);

int display_number_of_cells_equal(DATAFRAME *dataframe, int value);

int display_number_of_cells_less_than(DATAFRAME *dataframe, int value);

int display_number_of_cells_greater_than(DATAFRAME *dataframe, int value);

#endif
