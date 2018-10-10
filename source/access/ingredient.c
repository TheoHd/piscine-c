
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "ingredient.h"
#include "../../include/mysql.h"


#define __INGREDIENT_STRING_MAX 2048


struct Ingredient* initIngredient(char* name, char* description, double price)
{
    struct Ingredient* i = calloc(1, sizeof(struct Ingredient));
    strcpy(i->name, name);
    strcpy(i->description, description);
    i->price = price;
    i->next = NULL;
    return i;
}


void destroyIngredient(struct Ingredient* root, struct Ingredient* toDestroy)
{
    while (root->next != toDestroy) {
        root = root->next;
    }
    root->next = toDestroy->next;
    free(toDestroy->name);
    free(toDestroy->description);
    free(toDestroy);
}


void displayIngredientsList(struct Ingredient* i)
{
    while (i->next) {
        fprintf(stdout, "Name : {%s}", i->name);
        fprintf(stdout, "  Description : {%s}", i->description);
        fprintf(stdout, "  Price : {%lf}", i->price);
        i = i->next;
    }
}


void addIngredientToList(struct Ingredient* i1, struct Ingredient* i2)
{
    if (!i1) {
        i1 = i2;
        return;
    }
    while (i1->next != NULL) {
        i1 = i1->next;
    }
    i1->next = i2;
}


struct Ingredient* getAllIngredients(MYSQL connection)
{
    char* query = "WRITE SQL QUERY HERE";
    struct Ingredient* ingredient = NULL;

    /**
     * TODO: Do the database querying here, get back the data
     *       store it there, return linked list
     */
    for (int i = 0; i < 0; i += 1) {
        addIngredientToList(ingredient, initIngredient("name", "description", 0));
    }

    return ingredient;
}
