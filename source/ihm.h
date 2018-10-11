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
<<<<<<< HEAD
void findRecipesFromAvailableQuantity(MYSQL* connection, struct Ingredient* i);
void findRecipesById(MYSQL* connection, int id) ;
=======
>>>>>>> e1ac69c1c440954aa0ab954b8f630fbf6b086517

#endif //PISCINE_IHM_H
