CXX = g++
CXXFLAGS = -lcurl -ljsoncpp -pthread -lsqlite3

all: hello Output

hello:
	@echo "--------------------------------------------------------------------------"
	@echo "Compilation has begun"
	@echo "--------------------------------------------------------------------------"

targets: wdata.cpp wdata.h WeatherApi.cpp SQLhandler.h SQLhandler.cpp

Output: wdata.cpp WeatherApi.cpp wdata.h
	$(CXX) wdata.cpp WeatherApi.cpp SQLhandler.cpp $(CXXFLAGS)
