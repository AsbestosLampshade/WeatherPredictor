#include "wdata.h"
#define HOME_LAT 13.07179
#define HOME_LON 77.64755

float wdata::homeLatitude = HOME_LAT;
float wdata::homeLongitude = HOME_LON;


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
}

int wdata::fillData(std::string val)
{
        JSONCPP_STRING err;
        Json::CharReaderBuilder builder;
        Json::Value root;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(val.c_str(), val.c_str() + val.length(), &root,&err)) {
                std::cout << "error" << std::endl;
                return EXIT_FAILURE;
        }
        std::cout<<root["coord"]["lon"].asFloat();
	//Storing data
	lon=root["coord"]["lon"].asFloat();
	lat=root["coord"]["lat"].asFloat();
	temp=root["main"]["temp"].asFloat();
	pressure=root["main"]["pressure"].asFloat();
	humidity=root["main"]["humidity"].asFloat();
	tempMin=root["main"]["temp_min"].asFloat();
	tempMax=root["main"]["temp_max"].asFloat();
	lvlSea=root["main"]["sea_level"].asFloat();
	lvlGnd=root["main"]["grnl_level"].asFloat();
	visibility=root["visibility"].asFloat();
	clouds=root["clouds"]["all"].asFloat();
	rain1=root["rain"]["1h"].asFloat();
	rain3=root["rain"]["3h"].asFloat();
	snow1=root["snow"]["1h"].asFloat();
	snow3=root["snow"]["3h"].asFloat();
	time=root["dt"].asFloat();
	timezone=root["timezone"].asFloat();
	windData.speed=root["wind"]["speed"].asFloat();
	windData.gust=root["wind"]["gust"].asFloat();
	windData.deg=root["wind"]["deg"].asFloat();
	display();
        return EXIT_SUCCESS;
}

int wdata::requestApiWeather(float lat,float lon){
	CURL *curl;
        CURLcode res;
        std::string readBuffer;
	std::string url="https://api.openweathermap.org/data/2.5/weather?appid={apikey}";
	url+="lat=";
	url+=std::to_string(lat);
	url+="&lon=";
        url+=std::to_string(lon);
	//std::cout<<url;

        curl = curl_easy_init();
        if(curl) {
                curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
		std::cout<<std::endl<<"Result is="<<res;
                //std::cout << readBuffer << std::endl;
		std::cout<<"###"<<std::endl;
                fillData(readBuffer);
        }
        return 0;
}

compass wdata::coordinateData(float latExt,float longExt){
	compass comp;
	float radlatHome= homeLatitude * (M_PI/180);
	float radlatExt= lat * (M_PI/180);
	float radDeltalat= (lat-homeLatitude) * (M_PI/180);
	float radDeltalon= (lon-homeLongitude) * (M_PI/180);
	float a = (sin(radDeltalat/2) * sin(radDeltalat/2)) + (cos(radlatHome) * cos(radlatExt) * sin(radDeltalon/2) * sin(radDeltalon/2));	
	comp.distance = ERadius *  (2 * atan2(sqrt(a),sqrt(1-a)));
	float theta = atan2(cos(homeLatitude) * sin(lat) - sin(homeLatitude) * cos(lat) * cos(lon - homeLongitude) , sin(lon-homeLongitude) * cos(lat));
	comp.bearing = fmod((theta * 180 / M_PI + 360),360);
	return comp;

}

int weightedAvg(wdata &primary,wdata secondary,float weight){
	primary.temp+=(secondary.temp*weight);
        primary.pressure+=(secondary.pressure*weight);
        primary.humidity+=(secondary.humidity*weight);
        primary.tempMin+=(secondary.tempMin*weight);
        primary.tempMax+=(secondary.tempMax*weight);
        primary.visibility+=(secondary.visibility*weight);
        primary.clouds+=(secondary.clouds*weight);
        primary.rain1+=(secondary.rain1*weight);
        primary.rain3+=(secondary.rain3*weight);
        primary.snow1+=(secondary.snow1*weight);
        primary.snow3+=(secondary.snow3*weight);
        primary.windData.speed+=(secondary.windData.speed*weight);
        primary.windData.gust+=(secondary.windData.gust*weight);
        primary.windData.deg+=(secondary.windData.deg*weight);

	return 0;

}

int wdata::fillTable(int ID){

	return SQLhandler.addData(time,ID,temp,tempMax,tempMin,pressure,humidity,lvlSea,lvlGnd,visibility,windData.speed,windData.deg,windData.gust,rain1,rain3,snow1,snow3,clouds,stamp);
}

int wdata::display(){

	std::cout<<std::endl<<"OUTPUTS"<<std::endl<<std::endl;
	std::cout<<temp<<std::endl;
	std::cout<<pressure<<std::endl;
	std::cout<<humidity<<std::endl;
	std::cout<<tempMax<<std::endl;
	std::cout<<tempMin<<std::endl;
	std::cout<<visibility<<std::endl;
	std::cout<<clouds<<std::endl;
	std::cout<<rain1<<std::endl;
	std::cout<<rain3<<std::endl;
	std::cout<<snow1<<std::endl;
	std::cout<<snow3<<std::endl;
	std::cout<<windData.speed<<std::endl;
	std::cout<<windData.gust<<std::endl;
	std::cout<<windData.deg<<std::endl;

	return 0;

}

wdata::wdata(){
	temp=0;
	pressure=0;
	humidity=0;
	tempMax=0;
	tempMin=0;
	visibility=0;
	clouds=0;
	rain1=0;
	rain3=0;
	snow1=0;
	windData.speed=0;
	windData.gust=0;
	windData.deg=0;
	
}

int wdata::reset(){
	temp=0;
        pressure=0;
        humidity=0;
        tempMax=0;
        tempMin=0;
        visibility=0;
        clouds=0;
        rain1=0;
        rain3=0;
        snow1=0;
        windData.speed=0;
        windData.gust=0;
        windData.deg=0;

	return 0;
}
