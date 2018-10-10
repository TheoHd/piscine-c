#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../source/database.h"
#include "../source/access/ingredient.h"
#include "../source/access/recipe.h"


void test_ingredients(MYSQL* co)
{
    struct Ingredient* i = getAllIngredients(co);
    displayIngredientsList(i);
    freeIngredientList(i);
}


void test_recipes(MYSQL* co)
{
    struct Recipe* i = getAllRecipes(co);
    displayRecipesList(i);
    freeRecipesList(i);
}


int main(int argc, char** argv)
{
    MYSQL* connection = connectToDatabase();
    test_ingredients(connection);
    test_recipes(connection);
    mysql_close(connection);
    return EXIT_SUCCESS;
}

