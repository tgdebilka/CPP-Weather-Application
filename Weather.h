#ifndef WEATHER_WEATHER_H
#define WEATHER_WEATHER_H

#include <string>
#include <sstream>
#include <time.h>
#include <mutex>
#include <thread>

#include "pugixml.hpp"

template< typename T > inline bool ReadXmlChildValue(T& vars, pugi::xml_node node)
{
    std::stringstream stream;
    T data;
    int counter = 0;

    if (node == NULL) return false;

    stream << node.child_value();

    if (stream.str().empty()) return false;

    while (stream >> data)
    {
        vars = data;
    }

    return true;
}

struct WeatherDataStruct{
    float temperature;
    std::string weather_conditions;
    float wind_speed;

	float max_temperature;
	float min_temperature;
};

class Weather {
private:

	const int update_interval_seconds_ = 5;		//! interval in seconds to retrieve data from website
	
	const std::string nws_url_ = "http://forecast.weather.gov/MapClick.php?textField1=42.28&textField2=-83.74&FcstType=dwml";

    std::string body_;					//! string to store data retrived from NWS website
    pugi::xml_document xmldoc_;			//! pugixml object to load xml from string
	WeatherDataStruct weather_data_;	//! weather information for use

	//threading stuff
    time_t last_retrieved_;				//! time [s] for last successful completion of ParseXml()
	std::mutex mlock_;					//! mutex for weather_data_
	bool stop_thread_ = false;			//! flag to indicate if thread should be stopped
	std::thread thread_;				//! main update function is executed as thread
    
	//functions
    bool GetWeatherFromNatWeatherService();
    bool ParseXml();
    bool GetCurrentWeather();
	bool GetForecastWeather();
    bool PrintCurrentWeather();
	void RunThread();

public:

	Weather() : thread_() {}
	~Weather() {
		stop_thread_ = true;
		if (thread_.joinable()) thread_.join();
	}
	
	bool Start() {
		thread_ = std::thread(&Weather::RunThread, this);
	}
};

#endif //WEATHER_WEATHER_H
