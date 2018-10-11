#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "quantity.h"
#include "../../include/mysql.h"


#define __QUANTITY_STRING_MAX 2048


struct Quantity* newQuantity(int recipe, int ingredient, int amount)
{
    /** allocation */
    struct Quantity* i = malloc(sizeof(struct Quantity));
    i->recipe = recipe;
    i->ingredient = ingredient;
    i->amount = amount;
    i->next = NULL;
    return i;
}


void freeQuantitiesList(struct Quantity* r)
{
    struct Quantity* tmp;
    while (r) {
        tmp = r;
        r = r->next;
        free(tmp);
    }
}


void displayQuantitiesList(struct Quantity* r)
{
    /**
     * NOTICE HERE, THIS IS A MODEL TO ITERATE OVER A LINKED LIST
     */
    fprintf(stdout, "List of quantities :\n");
    while (r) {
        fprintf(
            stdout,
            " Recipe:{%d} Ingredient:{%d} Amount:{%d}\n",
            r->recipe,
            r->ingredient,
            r->amount
        );
        r = r->next;
    }
}


void _subAddQuantity_private(struct Quantity* base, struct Quantity* rec)
{
    if (base->next) {
        _subAddQuantity_private(base->next, rec);
        return;
    }
    base->next = rec;
}


/**
 * Adds ing to the list
 * @param base
 * @param ing
 * @return always return the base
 */
struct Quantity* addQuantityToList(struct Quantity* base, struct Quantity* rec)
{
    if (!base) return rec;
    _subAddQuantity_private(base, rec);
    return base;
}


MYSQL_RES* queryQuantities(MYSQL* connection)
{
    const char* query = "SELECT recipe_id, ingredient_id, amount FROM quantity;";
    if (mysql_query(connection, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(connection));
        return NULL;
    }
    return mysql_store_result(connection);
}


struct Quantity* getAllQuantities(MYSQL* connection)
{
    MYSQL_RES* res = queryQuantities(connection);
    if (!res) {
        fprintf(stderr, "Couldn't get results set: %s\n", mysql_error(connection));
        return NULL;
    }

    struct Quantity* quantity = NULL;
    MYSQL_ROW row = NULL;
    while (NULL != (row = mysql_fetch_row(res))) {
        quantity = addQuantityToList(
            quantity,
            newQuantity(atoi(row[0]), atoi(row[1]), atoi(row[2]))
        );
    }

    mysql_free_result(res);
    return quantity;
}
