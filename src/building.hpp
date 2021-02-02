/* ************************************************** *
 * Author: Mahmoud Gadalla                            *
 *                                                    *
 * This class is part of the TrafficSim C++ software  *
 * ************************************************** */

#pragma once

#include<vector>
#include<string>
#include <iostream>
#include <unordered_map>

class Person;
class Car;

enum class buildingType {
    NO_OBJECT,
    RESIDENTIAL,
    COMMERCIAL,
    INDUSTRIAL,
    EDUCATION,
    MISC
};

static std::unordered_map<std::string, buildingType> const table = {{"Residential", buildingType::RESIDENTIAL}, {"Commercial", buildingType::COMMERCIAL}, {"Industrial", buildingType::INDUSTRIAL}, {"Education", buildingType::EDUCATION}, {"Misc", buildingType::MISC}};

class Building {
public:
    // Constructor
    Building(){}

    //buildings_list(std::make_pair(std::pair(name, type) std::make_pair(entrance, Coor_list)));
    Building(std::pair<std::pair<std::string, std::string>, std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>>> building);

    // Getters
    const std::string& getName() const;
    const buildingType& getType() const;
    const std::pair<int, int> &getEntrance() const;
    const std::vector<std::pair<int, int>>& getCoordinateArray() const;
    // const int& getNlevel() const;
    const int& getNperson() const;
    const int& getNcar() const;
    const int& getmaxCapacity() const;
    const std::vector<Person*>& getPeople() const;
    const std::vector<Car*>& getCars() const;

    // Setters
    //void setType(buildingType type);
    //void setNlevel(int nLevel);

    // Member Functions
    void accommodate(Person* p);
    void evict(std::string name);
    void evictAll();

    void addCarToGarage(Car* v);
    void removeCarFromGarage(Car* c);
    void removeAllCarsFromGarage();

    ~Building();

private:
    std::pair<std::pair<std::string, std::string> , std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>>> building_;
    std::string name_;
    buildingType type_;
    std::pair<int, int> entranceCoordinate_;
    std::vector<std::pair<int, int>> coordinateArray_;
    int maxCapcity_ = coordinateArray_.size();

    // int nLevel_;
    int nPerson_;
    int nCar_;

    std::vector<Person*> people_;
    std::vector<Car*> garage_;

};
