#ifndef WDATA_H
#define WDATA_H

#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <memory>
#include <iostream>
#include <math.h>
#include "SQLhandler.h"

#define ERadius 6371000

struct wind{
float speed,gust;
int deg;
};

struct compass{
float distance;
float bearing;
};

typedef struct wind wind;
typedef struct compass compass;

class wdata{
float lon,lat,temp,pressure,humidity,tempMin,tempMax,lvlSea,lvlGnd,visibility,clouds,rain1,rain3,snow1,snow3,time,timezone;
std::string wname;
wind windData;

int fillData(std::string);
	
public:
wdata();
float localLat,localLong;
static float homeLatitude,homeLongitude;
int requestApiWeather(float,float);
compass coordinateData(float,float);
friend int weightedAvg(wdata&,wdata,float);
friend int windPrediction(wdata&,wdata);
int display();
int fillTable(int ID);
int reset();
};

extern int stamp;

#endif
