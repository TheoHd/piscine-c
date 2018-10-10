#ifndef PISCINE_RECIPE_H
#define PISCINE_RECIPE_H

#include "../../include/mysql.h"


/**
 * I'm using a linked list here because that allows us to have
 * a very dynamic list of ingredients without pre-allocating memory
 */
struct Recipe
{
    char* name;
    char* description;
    struct Recipe* next;
};

/**
 * Return a linked list of all recipes in the database ?
 * @param MYSQL con
 * @return
 */
struct Recipe* getAllRecipes(MYSQL* connection);

void freeRecipesList(struct Recipe* i);

void displayRecipesList(struct Recipe* i);

#endif //PISCINE_RECIPE_H
