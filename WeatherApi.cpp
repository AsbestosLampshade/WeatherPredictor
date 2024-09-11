#include <iostream>
#include <string>
#include <curl/curl.h>
#include "wdata.h"
#include <json/json.h>
#include <memory>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define LocationNo 4
#define LOC1_LAT 13.24049
#define LOC1_LON 77.70271
#define LOC2_LAT 12.9801
#define LOC2_LON 77.58534
#define LOC3_LAT 13.07312
#define LOC3_LON 77.79064
#define LOC4_LAT 13.09646
#define LOC4_LON 77.38847


int stamp=0;
wdata wOriginal,wTemp,w;
compass c1,c2,c3,c4;
float totalDist;
boost::asio::io_service io;
boost::asio::deadline_timer timer(io, boost::posix_time::seconds(60));

void work_for_io_service(const boost::system::error_code& /*e*/)
{
	
	timer.expires_from_now(boost::posix_time::seconds(10));
	timer.async_wait(&work_for_io_service);
	//Non-blocking wait
	//HOME
	wOriginal.requestApiWeather(w.homeLatitude,w.homeLongitude);
	wOriginal.fillTable(2);
	//NORTH
	w.requestApiWeather(LOC1_LAT,LOC1_LON);
	w.fillTable(5);
	weightedAvg(wTemp,w,c1.distance/totalDist);
	//SOUTH
	w.requestApiWeather(LOC2_LAT,LOC2_LON);
	w.fillTable(4);
	weightedAvg(wTemp,w,c2.distance/totalDist);
	//EAST
	w.requestApiWeather(LOC3_LAT,LOC3_LON);
	w.fillTable(3);
	weightedAvg(wTemp,w,c3.distance/totalDist);
	//WEST
	w.requestApiWeather(LOC4_LAT,LOC4_LON);
	w.fillTable(6);
	weightedAvg(wTemp,w,c4.distance/totalDist);
	wTemp.display();
	wTemp.fillTable(7);
	wTemp.reset();
	stamp++;
}

int main()
{
	//Preparation for distances
        c1=wOriginal.coordinateData(LOC1_LAT,LOC1_LON);
        c2=wOriginal.coordinateData(LOC2_LAT,LOC2_LON);
        c3=wOriginal.coordinateData(LOC3_LAT,LOC3_LON);
        c4=wOriginal.coordinateData(LOC4_LAT,LOC4_LON);
	totalDist=c1.distance+c2.distance+c3.distance+c4.distance;
	std::cout<<c1.distance<<"   "<<totalDist<<std::endl;


	timer.async_wait(&work_for_io_service);
	io.run();
	return 0;

}
