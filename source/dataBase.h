#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "../include/mysql.h"


/**
 * @return MYSQL database connection handle
 */
MYSQL* connectToDatabase();

#endif // DATABASE_H_INCLUDED
