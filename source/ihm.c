#include <memory.h>
#include <stdio.h>

#include "access/ingredient.h"
#include "access/recipe.h"
#include "access/quantity.h"
#include "ihm.h"


void findQuantityFromRecipe(MYSQL *connection, struct Recipe *r);


void help() {
    printf(
            "Options :\n"
            "  help show this help\n"
            "  list-recipe list all available recipes\n"
            "  price <value> return ingredients below that price\n"
            "  name <name> return info about one ingredient\n"
            "  recipe <name> return info about recipes matching that name\n"
            "  leftover return recipes from available ingredients\n"
            "\n"
            "NB : most commands have a short version composed of their initials\n"
    );
}


bool argIs(char *given_arg, char *long_arg, char *short_arg) {
    if (0 == strcmp(given_arg, long_arg)) return true;
    if (0 == strcmp(given_arg, short_arg)) return true;
    return false;
}


void getIngredientsBelowPrice(MYSQL *connection, long price) {
    struct Ingredient *i = getAllIngredients(connection);
    while (i) {
        if (i->price > price) {
            i = i->next;
            continue;
        }
        fprintf(stdout, "%s - {%.2lf€}\n", i->name, i->price);
        i = i->next;
    }
    freeIngredientList(i);
}


void getIngredientsName(MYSQL *connection, char *name) {
    struct Ingredient *i = getAllIngredients(connection);
    while (i) {
        if (NULL == strstr(i->name, name)) {
            i = i->next;
            continue;
        }
        fprintf(stdout, "%s - %s - {%.2lf€}\n", i->name, i->description, i->price);
        break;
    }
    freeIngredientList(i);
}


void listRecipes(MYSQL *connection) {
    struct Recipe *i = getAllRecipes(connection);
    displayRecipesList(i);
    freeRecipesList(i);
}


void getRecipeByName(MYSQL *connection, char *name) {
    struct Recipe *r = getAllRecipes(connection);
    while (r) {
        if (NULL == strstr(r->name, name)) {
            r = r->next;
            continue;
        }
        fprintf(stdout, "Recipe :\n");
        fprintf(stdout, " %s, %s\n", r->name, r->description);
        findQuantityFromRecipe(connection, r);
        break;
    }
    freeRecipesList(r);
}

void getRecipesFromAvailableQuantity(MYSQL *connection) {
    struct Recipe *r = getAllRecipes(connection);
    struct Quantity *q = getAllQuantities(connection);
    while (r) {
        if (q->recipe == r->id && q->amount == 0) {
            q = q->next;
            continue;
        }
        fprintf(stdout, "Recipe available :\n");
        fprintf(stdout, " %s, %s\n", r->name, r->description);
        r = r->next;
    }
    freeRecipesList(r);
    freeQuantitiesList(q);
}


void findQuantityFromRecipe(MYSQL *connection, struct Recipe *r) {
    struct Quantity *q = getAllQuantities(connection);
    while (q) {
        if (q->recipe != r->id) {
            q = q->next;
            continue;
        }
        findIngredientsFromQuantity(connection, q);
        q = q->next;
    }
    freeQuantitiesList(q);
}


void findIngredientsFromQuantity(MYSQL *connection, struct Quantity *q) {
    struct Ingredient *i = getAllIngredients(connection);
    while (i) {
        if (q->ingredient == i->id) {
            fprintf(stdout, " gs %s, %s - {%0.2lf€}\n", i->name, i->description, i->price);
        }
        i = i->next;
    }
    freeIngredientList(i);
}
