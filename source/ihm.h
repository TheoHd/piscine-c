#ifndef PISCINE_IHM_H
#define PISCINE_IHM_H

#include "../include/mysql.h"
#include <stdbool.h>


void help();
bool argIs(char* given_arg, char* long_arg, char* short_arg);
void getIngredientsBelowPrice(MYSQL* connection, long price);
void getIngredientsName(MYSQL* connection, char* name);
void listRecipes(MYSQL* connection);

#endif //PISCINE_IHM_H
