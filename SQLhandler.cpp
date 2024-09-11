#include "SQLhandler.h"
#include <string.h>

SQLhandler_t::SQLhandler_t(){

        /* Open database */
        rc = sqlite3_open("test.db", &db);

        if( rc ) {
                fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        } else {
                fprintf(stdout, "Opened database successfully\n");
        }

}

int SQLhandler_t::addLoc(int ID,std::string NAME,float LATITUDE,float LONGITUDE){

	std::string temp = "INSERT INTO LOC_DATA(ID,NAME,LATITUDE,LONGITUDE)"\
			"VALUES(";
	temp+=std::to_string(ID);
	temp+=",\'";
	temp+=NAME;
	temp+="\',";
	temp+=std::to_string(LATITUDE);
	temp+=",";
	temp+=std::to_string(LONGITUDE);
	temp+=");";
	sql = (char *)temp.data();

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


        if( rc != SQLITE_OK ){
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
		return(-1);
        }
        else {
                fprintf(stdout, "Location Entered successfully\n");
        }

	return(0);
}

int SQLhandler_t::addData(float TIME,int ID,float TEMP,float TEMP_MAX,float TEMP_MIN,float PRESS,float HUMIDITY,float SEA_LEV,float GND_LEV,float VISIBILITY,float WIND_SPEED,float WIND_DEG,float WIND_GUST,float RAIN_1,float RAIN_3,float SNOW_1,float SNOW_3,float CLOUDS,int STAMP){
	std::string temp = "INSERT INTO TIME_TABLE(TIME,ID,TEMP,TEMP_MAX,TEMP_MIN,PRESS,HUMIDITY,SEA_LEV,GND_LEV,VISIBILITY,WIND_SPEED,WIND_DEG,WIND_GUST,RAIN_1,RAIN_3,SNOW_1,SNOW_3,CLOUDS,STAMP)"\
                        "VALUES(";
	temp+=std::to_string(TIME);
	temp+=",";
        temp+=std::to_string(ID);
        temp+=",";
        temp+=std::to_string(TEMP);
        temp+=",";
        temp+=std::to_string(TEMP_MAX);
        temp+=",";
        temp+=std::to_string(TEMP_MIN);
        temp+=",";
        temp+=std::to_string(PRESS);
        temp+=",";
        temp+=std::to_string(HUMIDITY);
        temp+=",";
        temp+=std::to_string(SEA_LEV);
        temp+=",";
        temp+=std::to_string(GND_LEV);
        temp+=",";
        temp+=std::to_string(VISIBILITY);
        temp+=",";
        temp+=std::to_string(WIND_SPEED);
        temp+=",";
        temp+=std::to_string(WIND_DEG);
        temp+=",";
        temp+=std::to_string(WIND_GUST);
        temp+=",";
        temp+=std::to_string(RAIN_1);
        temp+=",";
        temp+=std::to_string(RAIN_3);
        temp+=",";
        temp+=std::to_string(SNOW_1);
        temp+=",";
        temp+=std::to_string(SNOW_3);
        temp+=",";
        temp+=std::to_string(CLOUDS);
	temp+=",";
        temp+=std::to_string(STAMP);
        temp+=");";
        sql = (char *)temp.data();

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


        if( rc != SQLITE_OK ){
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                return(-1);
        }
        else {
                fprintf(stdout, "Location Entered successfully\n");
        }

	return(0);
}

SQLhandler_t SQLhandler;
