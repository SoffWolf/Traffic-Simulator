#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <map>
#include <string>
#include <iostream>
#include <vector>


//LIGHT COLORS
#define RED 0
#define GREEN 1

struct IncomingLane{
    bool isGreen;
    int color;
};

class TrafficLight {
    private:
        // Variables: 
        std::map<std::string, IncomingLane> trafficLights;
        std::pair<int, int> coordinate_;

        double greenDuration = 0; //time in seconds from lights activation
        double timeInterval = 5;  // Time this light spends on green  = 5 seconds.

        // Functions: 
        void initIncomingLanes();

    public:
        // Constructor & destructor
        TrafficLight(std::pair<int,int> coodinate);
        ~TrafficLight();

        std::pair<int,int> getLocation();
        void update(double delta_time);
        bool isGreen(std::pair<int,int> incomingcarCoordinate);
    
};

#endif