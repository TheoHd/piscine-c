#include <memory.h>
#include <stdio.h>

#include "access/ingredient.h"
#include "access/recipe.h"
#include "ihm.h"


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
