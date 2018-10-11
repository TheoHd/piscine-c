#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#include "database.h"
#include "access/ingredient.h"
#include "access/recipe.h"


void help()
{
    printf(
        "Options :\n"
        "  help show this help\n"
        "  list-recipe list all available recipes\n"
        "  price <value> return ingredients below that price\n"
        "  name <name> return info about one ingredient\n"
        "\n"
        "NB : most commands have a short version composed of their initials\n"
    );
}


bool argIs(char* given_arg, char* long_arg, char* short_arg)
{
    if (0 == strcmp(given_arg, long_arg)) return true;
    if (0 == strcmp(given_arg, short_arg)) return true;
    return false;
}


void getIngredientsBelowPrice(MYSQL* connection, long price)
{
    struct Ingredient* i = getAllIngredients(connection);
    while (i) {
        if (i->price > price) {
            i = i->next;
            continue;
        }
        fprintf(stdout, "%s - {%.2lf€}\n", i->name, i->price);
        i = i->next;
    }
    freeIngredientList(i);
}


void getIngredientsName(MYSQL* connection, char* name)
{
    struct Ingredient* i = getAllIngredients(connection);
    while (i) {
        if (0 != strcmp(i->name, name)) {
            i = i->next;
            continue;
        }
        fprintf(stdout, "%s - %s - {%.2lf€}\n", i->name, i->description, i->price);
        break;
    }
    freeIngredientList(i);
}


void listRecipes(MYSQL* connection)
{
    struct Recipe* i = getAllRecipes(connection);
    displayRecipesList(i);
    freeRecipesList(i);
}


int main(int argc, char** argv)
{
    if (argc > 1 && 0 == strcmp(argv[1], "help")) {
        help();
        return EXIT_SUCCESS;
    }

    MYSQL* connection = connectToDatabase();

    if (argc > 1) {
        if (argIs(argv[1], "list-recipes", "lr")) {
            listRecipes(connection);
        }
    }

    if (argc > 2) {
        if (argIs(argv[1], "price", "p")) {
            getIngredientsBelowPrice(connection, strtol(argv[2], NULL, 10));
        }
        if (argIs(argv[1], "name", "n")) {
            getIngredientsName(connection, argv[2]);
        }
    }

    mysql_close(connection);
    return EXIT_SUCCESS;
}
