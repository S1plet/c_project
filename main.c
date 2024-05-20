#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"
#include "column.h"

int main(){
    // Example of the use of a dataframe
    
    DATAFRAME* df = create_dataframe(3);

    fill_dataframe(df);

    // Choose the name you want instead of "col_3"
    rename_column(df, 2, "col_3");

    display_dataframe(df);

    // You can change the value from 4 to whatever you want
    display_number_of_cells_equal(df, 4);

    return 0;
}
