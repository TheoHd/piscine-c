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
    /** example of filter on the list */
    while (i) {
        if (i->price != 0) {
            i = i->next;
            continue; // if price isn't 0, don't print it
        }
        fprintf(stdout, "%s\n", i->name);
        i = i->next;
    }
    freeIngredientList(i);


    mysql_close(dataBase);
    return EXIT_SUCCESS;
}
