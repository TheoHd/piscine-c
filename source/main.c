#include <stdlib.h>
#include <stdbool.h>

#include "database.h"
#include "ihm.h"


int main(int argc, char **argv) {
    if (argc > 1 && argIs(argv[1], "help", "h")) {
        help();
        return EXIT_SUCCESS;
    }

    MYSQL *connection = connectToDatabase();

    if (argc > 1) {
        if (argIs(argv[1], "list-recipes", "lr")) {
            listRecipes(connection);
        }
        if (argIs(argv[1], "leftover", "lo")) {
            getRecipesFromAvailableQuantity(connection);
        }
    }

    if (argc > 2) {
        if (argIs(argv[1], "price", "p")) {
            getIngredientsBelowPrice(connection, strtol(argv[2], NULL, 10));
        }
        if (argIs(argv[1], "name", "n")) {
            getIngredientsName(connection, argv[2]);
        }
        if (argIs(argv[1], "recipe", "r")) {
            getRecipeByName(connection, argv[2]);
        }
        if (argIs(argv[1], "id", "i")) {
            getRecipesById(connection, strtol(argv[2], NULL, 10));
        }
    }

    mysql_close(connection);
    return EXIT_SUCCESS;
}
