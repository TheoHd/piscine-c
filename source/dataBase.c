#include <stdlib.h>
#include <stdio.h>

#include "dataBase.h"
#include "configuration.h"
#include "../include/mysql.h"


MYSQL* connectToDatabase()
{
    MYSQL* connection = NULL;
    connection = mysql_init(connection);

    if (!connection) {
        fprintf(stderr, "Init failed, out of memory?");
        return NULL;
    }

    if (!mysql_real_connect(
        connection,  /* MYSQL structure to use */
        MYSQL_HOST,  /* server hostname or IP address */
        MYSQL_USER,  /* connection user */
        MYSQL_PWD,   /* password */
        MYSQL_DB,    /* default database to use, NULL for none */
        0,           /* port number, 0 for default */
        NULL,        /* socket file or named pipe name */
        CLIENT_FOUND_ROWS /* connection flags */ )) {
        fprintf(stderr, "%s\n", mysql_error(connection));
        fprintf(stderr, "Connect failed\n");
        return NULL;
    }

    return connection;
}
