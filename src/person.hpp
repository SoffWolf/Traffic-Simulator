/* ************************************************** *
 * Author: Gyeha Lim                                  *
 * Updated: 2020-08-21, 1:48 AM in Korea lol                                                   *
 * This class is part of the TrafficSim C++ software  *
 * ************************************************** */

#ifndef PERSON_HPP
#define PERSON_HPP

#include "car.hpp"
#include <string>
#include <vector>
#include <iostream>

class Car;
class Building;
class TrafficLight;

class Person {
    private:

        //Variables:
        std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> intersectionsList_;
        std::string name_;
        Car* ownedCar_;
        std::vector<std::pair<double, std::pair<std::string, Building*>>> schedule_;  //<time, <task, building>

        int idxPersonArray_;
        // int currentSpeed_ = 5; 
        
        std::pair<int,int> location_;
        Building* currentOrigin_;
        Building* currentDestination_;
        int scheduleIndex_;
        
        std::vector<std::pair<int, int>> route_; // used for determine_route_()
        std::vector<std::pair<int,int>> updated_determine_route_;

        const std::vector<std::pair<int, int>> determineRoute_(Building *origin, Building *arrive);
        bool isIntersection_(std::pair<int, int> crds);
        bool isOccupied_(std::pair<int, int> crds);
        bool nodeInList(std::pair<int, int> node, std::vector<std::pair<int, int>> list);

    public:
        // Constructor & Destructor
        
        //pass the whole schedule when creating a new person generate randomy(in the main simulation function)
        Person(std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> intersectionsList, const std::string& name, Building* building, Car* owned_vehicle, std::vector<std::pair<double, std::pair<std::string, Building*>>> schedule);//car = NULL if dont have one
        ~Person();
        
        const std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> getIntersectionsList() const;
        const std::string &getName() const;

        //Setter 
        void updateLocation(std::pair<int,int>);
        void setRoute(std::vector<std::pair<int, int> > route);
        void setNewOrigin(Building* source);
        void setNewDestination(Building* destination);
        void update_determine_route(std::vector<std::pair<int,int>> original_route);
        
        //Getter
        const int& getIndexPersonArray() const;
        const std::string getDirection() const;
        const std::vector<std::pair<int,int>>& getRoute() const;
        const std::vector<std::pair<double, std::pair<std::string, Building*>>>& getSchedule() const;     
        const std::pair<int, int>& getLocation() const;
        Building* const& getCurrentOrigin() const;
        Building* const& getCurrentDestination() const;
        const std::vector<std::pair<int,int>> get_updated_determine_route() const;
        static std::vector<std::pair<int,int>> personsLocationArray;

        void walk(Building* origin, Building* destination, std::vector<TrafficLight*> trafficLight_list);
        Person* updateTime(double global_clock, std::vector <TrafficLight*> trafficlight_list);

        //Member Functions
        void getIntoBuilding(Building& b); //the coordinate of entrance == the coordinate of the garage
        void getIntoCar(Car& v);
        TrafficLight* findTrafficLight (std::vector<TrafficLight*> trafficLight_list, std::pair<int, int> coordinates);
};

#endif