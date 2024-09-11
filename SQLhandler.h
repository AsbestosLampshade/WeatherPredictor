#ifndef SQLHANDLER_H
#define SQLHANDLER_H
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string>


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        int i;
        for(i = 0; i<argc; i++) {
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
}

class SQLhandler_t{
	char *zErrMsg = 0;
        int rc;
        char *sql,*sql_1;

	sqlite3 *db;
	public:
		SQLhandler_t();
		int addLoc(int,std::string,float,float);
		int addData(float,int,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,int);

};


extern SQLhandler_t SQLhandler;
#endif
