#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dataBase.h"
#include "access/ingredient.h"


int main(int argc, char** argv)
{
    MYSQL* dataBase = connectToDatabase();

    struct Ingredient* i = getAllIngredients(dataBase);
    displayIngredientsList(i);
    freeIngredientList(i);

    mysql_close(dataBase);
    return EXIT_SUCCESS;
}






