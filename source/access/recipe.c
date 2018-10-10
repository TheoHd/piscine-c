
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "recipe.h"
#include "../../include/mysql.h"


#define __RECIPE_STRING_MAX 2048


struct Recipe* newIngredient(char* name, char* description)
{
    /** allocation */
    struct Recipe* i = malloc(sizeof(struct Recipe));
    size_t nameLen = strnlen(name, __RECIPE_STRING_MAX);
    size_t descLen = strnlen(description, __RECIPE_STRING_MAX);
    /** add +1 for the NULL terminating byte */
    i->name = calloc(nameLen + 1, sizeof(char));
    i->description = calloc(descLen + 1, sizeof(char));
    /** assigning */
    strcpy(i->name, name);
    strcpy(i->description, description);
    i->next = NULL;
    return i;
}


void freeRecipe(struct Recipe* toDestroy)
{
    free(toDestroy->name);
    free(toDestroy->description);
    free(toDestroy);
}


void freeRecipeList(struct Recipe* i)
{
    struct Recipes* tmp;
    while (i) {
        tmp = i;
        i = i->next;
        freeRecipe(tmp);
    }
}


void displayRecipesList(struct Recipe* i)
{
    /**
     * NOTICE HERE, THIS IS A MODEL TO ITERATE OVER A LINKED LIST
     */
    while (i) {
        fprintf(stdout, "Name : {%s}\n", i->name);
        fprintf(stdout, "  Description : {%s}\n", i->description);
        i = i->next;
    }
}


void _subAdd_private(struct Recipe* base, struct Recipe* ing)
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
struct Recipe* addRecipeToList(struct Recipe* base, struct Recipe* rec)
{
    if (!base) return rec;
    _subAdd_private(base, rec);
    return base;
}


MYSQL_RES* queryRecipes(MYSQL* connection)
{
    const char* query = "SELECT name, description FROM recipes;";
    if (mysql_query(connection, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(connection));
        return NULL;
    }
    return mysql_store_result(connection);
}


struct Recipe* getAllRecipes(MYSQL* connection)
{
    MYSQL_RES* res = queryRecipes(connection);
    if (!res) {
        fprintf(stderr, "Couldn't get results set: %s\n", mysql_error(connection));
        return NULL;
    }

    struct Recipe* recipe = NULL;
    MYSQL_ROW row = NULL;
    while (NULL != (row = mysql_fetch_row(res))) {
        double price = strtod(row[2], NULL); // strtod => "string to double"
        recipe = addRecipeToList(recipe, newIngredient(row[0], row[1]));
    }

    mysql_free_result(res);
    return recipe;
}
