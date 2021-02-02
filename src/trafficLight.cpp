#include "trafficLight.hpp"

void TrafficLight::initIncomingLanes() {

    IncomingLane North;
    trafficLights["North"] = North;
    trafficLights["North"].color = GREEN;
    trafficLights["North"].isGreen = true;

    IncomingLane South;
    trafficLights["South"] = South;
    trafficLights["South"].color = GREEN;
    trafficLights["South"].isGreen = true;


    IncomingLane East;
    trafficLights["East"] = East;
    trafficLights["East"].color = RED;
    trafficLights["East"].isGreen = false;

    IncomingLane West;
    trafficLights["West"] = West;
    trafficLights["West"].color = RED;
    trafficLights["West"].isGreen = false;

}


TrafficLight::TrafficLight(std::pair<int, int> coordinate)
    : coordinate_(coordinate){ 
        initIncomingLanes();
    }

TrafficLight::~TrafficLight(){}

std::pair<int,int> TrafficLight::getLocation(){
    return coordinate_;
}

void TrafficLight::update(double delta_time)
{
    greenDuration += delta_time;
    if (greenDuration >= timeInterval){
        if (trafficLights["North"].isGreen == true){
            trafficLights["North"].color = RED;
            trafficLights["North"].isGreen = false;

            trafficLights["South"].color = RED;
            trafficLights["South"].isGreen = false;

            trafficLights["East"].color = GREEN;
            trafficLights["East"].isGreen = true;

            trafficLights["West"].color = GREEN;
            trafficLights["West"].isGreen = true;
        }
        else {
            trafficLights["North"].color = GREEN;
            trafficLights["North"].isGreen = true;

            trafficLights["South"].color = GREEN;
            trafficLights["South"].isGreen = true;

            trafficLights["East"].color = RED;
            trafficLights["East"].isGreen = false;

            trafficLights["West"].color = RED;
            trafficLights["West"].isGreen = false;
        }
        greenDuration = 0;
    }
    // std::cout<<"North:" << trafficLights["North"].color<<std::endl;
    // std::cout<<"East:"<< trafficLights["East"].color<<std::endl;
}

bool TrafficLight::isGreen(std::pair<int,int> incomingcarCoordinate){
    if (getLocation().first == incomingcarCoordinate.first && getLocation().second < incomingcarCoordinate.second){
        // std::cout<<"Car is coming down from North"<<std::endl;
        return trafficLights["North"].isGreen;
    } else if (coordinate_.first == incomingcarCoordinate.first && coordinate_.second > incomingcarCoordinate.second){
        // std::cout<<"Car is coming down from South"<<std::endl;
        return trafficLights["South"].isGreen;
    } else if (coordinate_.first > incomingcarCoordinate.first && coordinate_.second == incomingcarCoordinate.second){
        // std::cout<<"Car is coming down from West"<<std::endl;
        return trafficLights["West"].isGreen;
    } 
    // std::cout<<"Car is coming from East"<<std::endl;
    return trafficLights["East"].isGreen;
}


