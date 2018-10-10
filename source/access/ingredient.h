#ifndef PISCINE_INGREDIENT_H
#define PISCINE_INGREDIENT_H

#include "../../include/mysql.h"


/**
 * I'm using a linked list here because that allows us to have
 * a very dynamic list of ingredients without pre-allocating memory
 */
struct Ingredient
{
    int id;
    char* name;
    char* description;
    double price;
    struct Ingredient* next;
};

/**
 * Return a linked list of all ingredients in the database ?
 * @param MYSQL con
 * @return
 */
struct Ingredient* getAllIngredients(MYSQL* connection);

void freeIngredientList(struct Ingredient* i);

void displayIngredientsList(struct Ingredient* i);

#endif //PISCINE_INGREDIENT_H
