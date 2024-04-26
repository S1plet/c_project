#include <stdio.h>
#include "cdataframe.h"
#include "column.h"

int main(){
    // Creating dataframe of 5 columns
    DATAFRAME df = create_dataframe(5);

    // Allows the user to fill our dataframe
    fill_dataframe(df);

    // Displays the number of columns
    display_number_of_columns(df);

    // Allows the user to check if 3 is in the dataframe
    check_if_value_in_dataframe(df, 3);

    return 0
}
