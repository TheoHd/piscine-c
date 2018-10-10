
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "ingredient.h"
#include "../../include/mysql.h"


#define __INGREDIENT_STRING_MAX 2048


struct Ingredient* newIngredient(char* name, char* description, double price)
{
    /** allocation */
    struct Ingredient* i = malloc(sizeof(struct Ingredient));
    size_t nameLen = strnlen(name, __INGREDIENT_STRING_MAX);
    size_t descLen = strnlen(description, __INGREDIENT_STRING_MAX);
    /** add +1 for the NULL terminating byte */
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

/**
 * Adds ing to the list
 * @param base
 * @param ing
 * @return always return the base
 */
struct Ingredient* addIngredientToList(struct Ingredient* base, struct Ingredient* ing)
{
    if (!base) return ing;
    _subAdd_private(base, ing);
    return base;
}


MYSQL_RES* queryIngredients(MYSQL* connection)
{
    const char* query = "SELECT name, description, price FROM ingredients;";
    if (mysql_query(connection, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(connection));
        return NULL;
    }
    return mysql_store_result(connection);
}


struct Ingredient* getAllIngredients(MYSQL* connection)
{
    MYSQL_RES* res = queryIngredients(connection);
    if (!res) {
        fprintf(stderr, "Couldn't get results set: %s\n", mysql_error(connection));
        return NULL;
    }

    struct Ingredient* ingredient = NULL;
    MYSQL_ROW row = NULL;
    while (NULL != (row = mysql_fetch_row(res))) {
        double price = strtod(row[2], NULL); // strtod => "string to double"
        ingredient = addIngredientToList(ingredient, newIngredient(row[0], row[1], price));
    }

    mysql_free_result(res);
    return ingredient;
}
