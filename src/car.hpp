/* ************************************************** *
 * Author: Mahmoud Gadalla                            *
 *                                                    *
 * This class is part of the TrafficSim C++ software  *
 * ************************************************** */

#pragma once

#include <chrono>
#include <thread>
#include <algorithm>
#include <vector>

#include "building.hpp" 
#include "trafficLight.hpp"
#include "person.hpp"

class Building;
class TrafficLight;

class Car
{
    public:
        Car(Building& inBuilding, std::pair<int, int> location,  std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> intersectionsList, int speed);
        ~Car();

        static std::vector<std::pair<std::pair<int, int>, std::string>> vehiclesLocationArray;

        // Getters: 
        const std::pair<int, int> &getLocation() const;
        const int& getCurrentSpeed() const;

        const int& getIndexVehicleArray() const; 
        const int& getMaxCapacity() const;

        const std::vector<Person*>& getPassengers() const;
        Building* const getDestination() const;
        const std::vector<std::pair<int, int> > getRoute();
        const std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> getIntersectionsList();

        Building& getBuilding(); //return building name or "" if on the road

        // Setters:
        void updateLocation(std::pair<int, int>);
        void setDestination(Building*);
        void setRoute(std::vector<std::pair<int, int> > route);

        const std::vector<std::pair<int,int>> get_updated_determine_route() const;

        void update_determine_route(std::vector<std::pair<int,int>> original_route);
        void drive(Building *origin, Building *destination, std::vector<TrafficLight*> trafficLight_list);

        bool nodeInList(std::pair<int, int> node, std::vector<std::pair<int, int>> list);
        
        TrafficLight* findTrafficLight (std::vector<TrafficLight*> trafficLight_list, std::pair<int, int> coordinates);
        const std::string getDirection() const;
        const std::vector<std::pair<int,int>>& getRoute() const;

        //memeber fucntions:
        void getInto(Building& the_garage_of);
        void accommodate(Person* p);
        void evict(const std::string passengerName);
        void evictAll();
    private:

        std::pair<int, int> location_;
        int currentSpeed_;
        Building& inBuilding_;

        int idxVehicleArray_;    // Index of current class instance in vehiclesLocation array
        
        int maxCapacity_;
        
        std::vector<Person*> passengers_;
        Building* destination_;
        std::vector<std::pair<int, int> > route_;
        std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> intersectionsList_;

        // Variables: 
        std::vector<std::pair<int,int>> updated_determine_route_;
        double occupiedWait = 0;
        double redLightWait = 0;
        std::pair<std::pair<int, int>, std::pair<std::string, std::string>> intersectionsList;
        const std::vector<std::pair<int, int>> determineRoute_(Building *origin, Building *destination);
        std::pair<int,int> currentOrigin_;
        std::pair<int,int> currentDestination_;
        bool isIntersection_(std::pair<int, int> crds);
        bool isOccupied_(std::pair<int, int> crds);
        
};


        // xml_parser xml_doc(getMapFileName());
