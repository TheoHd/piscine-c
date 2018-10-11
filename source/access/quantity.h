#ifndef PISCINE_QUANTITY_H
#define PISCINE_QUANTITY_H

#include "../../include/mysql.h"


/**
 * I'm using a linked list here because that allows us to have
 * a very dynamic list of ingredients without pre-allocating memory
 */
struct Quantity
{
    int recipe;
    int ingredient;
    int amount;
    struct Quantity* next;
};

/**
 * Return a linked list of all quantities in the database
 * @param MYSQL con
 * @return
 */
struct Quantity* getAllQuantities(MYSQL* connection);

void displayQuantitiesList(struct Quantity* r);

void freeQuantitiesList(struct Quantity* r);

#endif //PISCINE_QUANTITY_H
