#ifndef PISCINE_IHM_H
#define PISCINE_IHM_H

#include "../include/mysql.h"
#include <stdbool.h>
#include "access/quantity.h"


void help();
bool argIs(char* given_arg, char* long_arg, char* short_arg);
void getIngredientsBelowPrice(MYSQL* connection, long price);
void getIngredientsName(MYSQL* connection, char* name);
void listRecipes(MYSQL* connection);
void getRecipeByName(MYSQL* connection, char* name);
void getRecipesFromAvailableQuantity(MYSQL* connection);
void findIngredientsFromQuantity(MYSQL* connection, struct Quantity* q);
void findRecipesFromAvailableQuantity(MYSQL* connection, struct Ingredient* i);

#endif //PISCINE_IHM_H
