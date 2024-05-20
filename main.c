#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"
#include "column.h"

int main(){
    DATAFRAME* df = create_dataframe(3);

    fill_dataframe(df);

    rename_column(df, 2, "col_3");

    display_dataframe(df);

    display_number_of_cells_equal(df, 4);

    return 0;
}
