#include "building.hpp"
#include "person.hpp"

Building::Building(std::pair<std::pair<std::string, std::string> , std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>>> building)
{
    building_ = building ; // Init here but why? candidate expects 1 argument, 0 provided
    name_ = (building.first).first ;
    coordinateArray_ = (building.second).second;
    nPerson_ = 0;
    nCar_ = 0;

    std::string typeStr = (building_.first).second;
    auto it = table.find(typeStr);
    if (it != table.end()) {
        type_ = it->second;
    }
    else {
        std::cout << "Wrong building type in the map. Possible values are: 'Residential', 'Commercial', 'Industrial', 'Misc' " << std::endl;
    }
    entranceCoordinate_ = std::make_pair(building.second.first.first, building.second.first.second);
}

// Getters
const std::string& Building::getName() const { return name_; }
const buildingType& Building::getType() const { return type_; }
const std::pair<int, int> &Building::getEntrance() const { return entranceCoordinate_; }
const std::vector<std::pair<int, int>> &Building::getCoordinateArray() const { return coordinateArray_; }
// const int& Building::getNlevel() const { return nLevel_; }
const int& Building::getNperson() const { return nPerson_; }
const int& Building::getNcar() const { return nCar_; }
const int& Building::getmaxCapacity() const { return maxCapcity_;}
const std::vector<Person*>& Building::getPeople() const { return people_; }
const std::vector<Car*>& Building::getCars() const { return garage_; }

// Member Functions
void Building::accommodate(Person* p) {
    people_.push_back(p);
    nPerson_ ++;
}

void Building::evict(std::string name) {

    auto it = people_.begin(); 
    int count = 0;
    for (auto person : people_)
    {
        if (person->getName() == name) 
        {
            people_.erase(it+count);
            delete person;
            nPerson_ --;
            break;
        }
        count++;
    }
}

void Building::evictAll() {
    people_.clear();
    nPerson_ = 0;
}

void Building::addCarToGarage(Car* v) {
    garage_.push_back(v);
    nCar_++;
}

void Building::removeCarFromGarage(Car* c) {
    auto it = garage_.begin(); 
    int count = 0;
    for (auto car : garage_)
    {
        if (car == c) 
        {
            garage_.erase(it+count);
            delete car;
            nCar_--;
            break;
        }
        count++;
        
    }
}

void Building::removeAllCarsFromGarage() {
    garage_.clear();
    nCar_ = 0;
}

Building::~Building() {
    for (auto it : people_)
        delete it;
    for (auto it : garage_)
        delete it;
}