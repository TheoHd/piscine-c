#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#ifdef __APPLE__
    #define MYSQL_PWD "root"
#elif __linux__
    #define MYSQL_PWD "root"
#else
    #define MYSQL_PWD ""
#endif
#define MYSQL_DB "piscine"
