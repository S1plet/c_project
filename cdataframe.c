// This file contains all the functions associated to the dataframe (some use the ones in columns.c)

#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"
#include "string.h"

// Creates a dataframe
DATAFRAME* create_dataframe(int nb_columns) {
    DATAFRAME* df = malloc(sizeof(DATAFRAME));
    if (df == NULL) {
        printf("Memory allocation failed...\n");
        return NULL;
    }

    // Allocate memory for the array of column pointers
    df->columns = malloc(nb_columns * sizeof(COLUMN*));
    if (df->columns == NULL) {
        printf("Memory allocation failed...\n");
        free(df); // Free allocated DATAFRAME structure's memory
        return NULL;
    }

    // Initialize each column pointer to NULL
    for (int i = 0; i < nb_columns; i++) {
        df->columns[i] = NULL;
    }

    df->nb_columns = nb_columns;
    return df;
}

// Fills the dataframe with user inputs
void fill_dataframe(DATAFRAME* dataframe) {
    int nbValues;
    printf("Please enter the number of values for each column : ");
    scanf("%d", &nbValues);

    for (int i = 0; i < dataframe->nb_columns; i++) {
        dataframe->columns[i] = create_column("[title]");
        if (dataframe->columns[i] == NULL) {
            for (int j = 0; j < i; j++) {
                delete_column(dataframe->columns[j]); // Again, preventing memory used unnecessarely
            }
            return;
        }
        for (int j = 0; j < nbValues; j++) {
            int valueToAdd;
            printf("Please enter the value %d for the column %d : ", j, i); // Allows the user to fill the dataframe as he wants
            scanf("%d", &valueToAdd);
            insert_value(dataframe->columns[i], valueToAdd);
        }
    }
}

// Hardfills the dataframe with 0s (same reasoning as previous function
void hardfill_dataframe(DATAFRAME* dataframe, int nb_rows) {
    for (int i = 0; i < dataframe->nb_columns; i++) {
        dataframe->columns[i] = create_column("[title]");
        if (dataframe->columns[i] == NULL) {
            for (int j = 0; j < i; j++) {
                delete_column(dataframe->columns[j]);
            }
            return;
        }
        for (int j = 0; j < nb_rows; j++) {
            insert_value(dataframe->columns[i], 0);
        }
    }
}

// Displays the dataframe
void display_dataframe(DATAFRAME* dataframe) {
    if (dataframe == NULL) {
        printf("Dataframe is empty\n");
        return;
    }

    printf("Dataframe :\n");

    // Prints all columns titles
    for (int i = 0; i < dataframe->nb_columns; i++) {
        printf("%s\t", dataframe->columns[i]->title);
    }
    printf("\n");

    // Print values row by row
    for (int i = 0; i < dataframe->columns[0]->log_size; i++) { // We assume that each column has the same number of values (we tried without this assuption but got difficulties)
        for (int j = 0; j < dataframe->nb_columns; j++) {
            printf("%d\t", value_at_index(dataframe->columns[j], i));
        }
        printf("\n");
    }
}

// Displays the first "nb_rows" rows
void display_partial_dataframe_rows(DATAFRAME* dataframe, int nb_rows) {
    if (dataframe == NULL) {
        printf("DataFrame is empty\n");
        return;
    }

    printf("Dataframe :\n");

    // Prints columns titles
    for (int i = 0; i < dataframe->nb_columns; i++) {
        printf("%s\t", dataframe->columns[i]->title);
    }
    printf("\n");

    // Prints values row by row
    for (int i = 0; i < dataframe->columns[0]->log_size && i < nb_rows; i++) { // Again, we assume that each column has the same number of values
        for (int j = 0; j < dataframe->nb_columns; j++) {
            printf("%d\t", value_at_index(dataframe->columns[j], i));
        }
        printf("\n");
    }
}

// Displays the first "nb_colums" columns
void display_partial_dataframe_columns(DATAFRAME* dataframe, int nb_columns) {
    if (dataframe == NULL) {
        printf("Dataframe is empty\n");
        return;
    }

    printf("Dataframe :\n");

    // Prints columns titles
    for (int i = 0; i < dataframe->nb_columns && i < nb_columns; i++) {
        printf("%s\t", dataframe->columns[i]->title);
    }
    printf("\n");

    // Prints values column by column
    for (int i = 0; i < dataframe->columns[0]->log_size; i++) {
        for (int j = 0; j < dataframe->nb_columns && j < nb_columns; j++) {
            printf("%d\t", value_at_index(dataframe->columns[j], i));
        }
        printf("\n");
    }
}

// Adds a row to all the columns constituing the dataframe
void add_row(DATAFRAME* dataframe, int* row) { // Row is an array of integers constituing a row
    for (int i = 0; i < dataframe->nb_columns; i++) {
        insert_value(dataframe->columns[i], row[i]);
    }
}

// Allows to delete a whole row of numbers
void delete_row(DATAFRAME* dataframe, int row_index) {
    if (row_index < 0 || row_index >= dataframe->columns[0]->log_size) {
        printf("Invalid row index\n");
        return;
    }

    // "Deletes" the values at the specified row index for each column
    for (int i = 0; i < dataframe->nb_columns; i++) {
        for (int j = row_index; j < dataframe->columns[i]->log_size - 1; j++) {
            dataframe->columns[i]->data[j] = dataframe->columns[i]->data[j+1]; // Moves the values of a row upward in the rows
        }
        dataframe->columns[i]->data[dataframe->columns[i]->log_size - 1] = 0; // Doesn't really deletes the row but sets a row of 0s
        // Decrement the logical size of the column, so the row is indeed deleted
        dataframe->columns[i]->log_size--;
    }
}

// Allows to add a column
void add_column(DATAFRAME* dataframe) {
    // Allocate memory for the new column
    COLUMN* new_column = create_column("[title]");

    // "Copies" all the array of column pointers and adds the new column
    COLUMN** temp = realloc(dataframe->columns, (dataframe->nb_columns + 1) * sizeof(COLUMN*));
    if (temp == NULL) {
        printf("Unable to allocate memory for column pointers...\n");
        free(new_column); // Deletes both "temp" and "new_column" if problem
        return; 
    }
    free(dataframe->columns); // If no problem then we free all the columns in the dataframe and replace them by our "temp"
    dataframe->columns = temp;

    // Adds the new column pointer to the dataframe's array of column pointers
    dataframe->columns[dataframe->nb_columns] = new_column;

    // Updates the number of columns in the dataframe
    dataframe->nb_columns++;
}

void delete_column_at_index(DATAFRAME* dataframe, int column_index) {
    //Free the memory associated with the column's data and itself
    delete_column(dataframe->columns[column_index]);

    //Shift the column pointers in the array to remove the deleted column
    for (int i = column_index; i < dataframe->nb_columns - 1; i++) {
        dataframe->columns[i] = dataframe->columns[i + 1];
    }

    // Update the number of columns in the dataframe
    dataframe->nb_columns--;
}

// Allows the user to rename a column in the dataframe
void rename_column(DATAFRAME* dataframe, int column_index, char* title) {
    char* temp = malloc(strlen(title) + 1); // Allocates memory for the new ttile (we include the "\0" again)
    temp = title; // No need of "strcpy" as we did to create a name for a column in "column.c"
    free(dataframe->columns[column_index]->title);
    dataframe->columns[column_index]->title = temp;
}

// Allows to check the existence of a certain value in the whole dataframe
void check_if_value_in_dataframe(DATAFRAME* dataframe, int value) {
    int found = 0;
    int i = 0;
    while (!found || i < dataframe->nb_columns) {
        if (nb_occurrences(dataframe->columns[i], value) != 0) {
            found = 1;
        }
        i++;
    }
    if (found) {
        printf("Value successfully found");
    }
    else {
        printf("Value not found");
    }
}

// Allows to replace a value at a given position in the dataframe
void replace_value(DATAFRAME* dataframe, int column_index, int row_index, int value) {
    dataframe->columns[column_index]->data[row_index] = value;
}

// Allows to get a certain value at a given position in the dataframe
int get_value(DATAFRAME* dataframe, int column_index, int row_index) {
    return dataframe->columns[column_index]->data[row_index];
}

// Displays the name of each columns in the dataframe
void display_column_names(DATAFRAME* dataframe) {
    for (int i = 0; i < dataframe->nb_columns; i++) {
        printf("%s ", dataframe->columns[i]->title);
    }
}

// Displays the number of rows
void display_number_of_rows(DATAFRAME* dataframe) {
    printf("Number of rows : %d\n", dataframe->columns[0]->log_size);
}

// Displays the number of columns
void display_number_of_columns(DATAFRAME* dataframe) {
    printf("Number of columns : %d\n", dataframe->nb_columns);
}

// Displays the number of equal cells
void display_number_of_cells_equal(DATAFRAME* dataframe, int value) {
    int nbCells = 0;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        nbCells += nb_occurrences(dataframe->columns[i], value);
    }
    printf("Number of cells equel to %d : %d", value, nbCells);
}

// Display the number of cells having a value inferior than the one entered
int display_number_of_cells_less_than(DATAFRAME* dataframe, int value) {
    int numCells = 0;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        numCells += nb_values_smaller(dataframe->columns[i], value);
    }
    return numCells;
}

// Display the number of cells having a value superior than the one entered
int display_number_of_cells_greater_than(DATAFRAME* dataframe, int value) {
    int numCells = 0;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        numCells += nb_values_greater(dataframe->columns[i], value);
    }
    return numCells;
}

