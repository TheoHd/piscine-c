
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "ingredient.h"
#include "../../include/mysql.h"


#define __INGREDIENT_STRING_MAX 2048


struct Ingredient* newIngredient(char* name, char* description, double price)
{
    /** allocation */
    struct Ingredient* i = calloc(1, sizeof(struct Ingredient));
    size_t nameLen = strnlen(name, __INGREDIENT_STRING_MAX);
    size_t descLen = strnlen(description, __INGREDIENT_STRING_MAX);
    i->name = calloc(nameLen + 1, sizeof(char));
    i->description = calloc(descLen + 1, sizeof(char));
    /** assigning */
    strcpy(i->name, name);
    strcpy(i->description, description);
    i->price = price;
    i->next = NULL;
    return i;
}


void freeIngredient(struct Ingredient* toDestroy)
{
    free(toDestroy->name);
    free(toDestroy->description);
    free(toDestroy);
}


void freeIngredientList(struct Ingredient* i)
{
    struct Ingredient* tmp;
    while (i) {
        tmp = i;
        i = i->next;
        freeIngredient(tmp);
    }
}


void displayIngredientsList(struct Ingredient* i)
{
    /**
     * NOTICE HERE, THIS IS A MODEL TO ITERATE OVER A LINKED LIST
     */
    while (i) {
        fprintf(stdout, "Name : {%s}\n", i->name);
        fprintf(stdout, "  Description : {%s}\n", i->description);
        fprintf(stdout, "  Price : {%0.2lf}€\n", i->price);
        i = i->next;
    }
}


void _subAdd_private(struct Ingredient* base, struct Ingredient* ing)
{
    if (base->next) {
        _subAdd_private(base->next, ing);
        return;
    }
    base->next = ing;
}


struct Ingredient* addIngredientToList(struct Ingredient* base, struct Ingredient* ing)
{
    if (!base) return ing;
    _subAdd_private(base, ing);
    return base;
}


struct Ingredient* getAllIngredients(MYSQL* connection)
{
    char* query = "WRITE SQL QUERY HERE";
    struct Ingredient* ingredient = NULL;

    /**
     * TODO: Do the database querying here, get back the data
     *       store it there, return linked list
     */
    for (int i = 0; i < 5; i += 1) {
        ingredient = addIngredientToList(ingredient, newIngredient("name", "description", 0));
    }

    return ingredient;
}
