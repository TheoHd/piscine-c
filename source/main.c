#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dataBase.h"


int main(int argc, char** argv)
{
    MYSQL* dataBase =  connectDataBase() ;



    mysql_close(dataBase);

    return EXIT_SUCCESS;
}






