#include "person.hpp"
#include <iterator>
std::vector<std::pair<int,int>> Person::personsLocationArray;

const std::vector<std::pair<int, int>> Person::determineRoute_(Building *origin, Building *arrive) {
    const std::pair<int, int>& startPoint = origin->getEntrance();
    std::pair<int, int> endPoint = arrive->getEntrance();

    std::vector<std::pair<int, int>> bestRoute;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> predecessor;
    std::vector<std::pair<int, int>> visited;
    std::vector<std::pair<int, int>> queue;
    std::vector<std::pair<int, int>> backlog_intersection;
    bestRoute.push_back(endPoint);
    queue.push_back(startPoint);
    predecessor.push_back(std::make_pair(startPoint, std::make_pair(-1, -1)));

    std::pair<int, int> goal_intersection;
    while (sizeof(queue) != 0) {
        std::pair<int, int> locationNow = queue[0];
        queue.erase(queue.begin());
        for (std::pair<std::pair<int, int>, std::pair<std::string, std::string>> x : getIntersectionsList()) {
            if ((x.first.first == locationNow.first) || (x.first.second == locationNow.second)) {
                if (!nodeInList(x.first, visited)) {
                    queue.push_back(x.first);
                    predecessor.push_back(std::make_pair(x.first, locationNow));
                }
            }
        }
        if ((locationNow.first == endPoint.first) || (locationNow.second == endPoint.second)) {
            if (locationNow.first == endPoint.first){
                for (std::pair<std::pair<int, int>, std::pair<std::string, std::string>> x : getIntersectionsList()){
                    if (x.first.first == endPoint.first){
                        if ((x.first.second - endPoint.second)*(x.first.second - locationNow.second) < 0 ){
                            backlog_intersection.insert(backlog_intersection.begin(),x.first);
                        }
                    }
            }
            }
            else if (locationNow.second == endPoint.second){
                for (std::pair<std::pair<int, int>, std::pair<std::string, std::string>> x : getIntersectionsList()){
                    if (x.first.second == endPoint.second){
                        if ((x.first.first - endPoint.first)*(x.first.first - locationNow.first) < 0 ){
                            backlog_intersection.insert(backlog_intersection.begin(),x.first);
                        }
                    }
            }
            }
            
            goal_intersection = locationNow;

            break;
        }
        visited.push_back(locationNow);
    }
    for (std::pair<int,int> x : backlog_intersection){
        bestRoute.push_back(x);
    }
    std::pair<int, int> node = goal_intersection;
    bestRoute.push_back(goal_intersection);
    
    while (node != startPoint) {
        for (std::pair<std::pair<int, int>, std::pair<int, int>> x : predecessor) {
            if (x.first == node) {
                node = x.second;
                bestRoute.push_back(x.second);
            }
        }
    }
    std::reverse(bestRoute.begin(), bestRoute.end());
    return bestRoute;
}

bool Person::isIntersection_(std::pair<int, int> crds) {
    for (std::pair<std::pair<int, int>, std::pair<std::string, std::string>> i : getIntersectionsList()) {
        std::pair<int, int> intersection = i.first;
        if( (intersection.first == crds.first) && (intersection.second == crds.second) )
            return true;
    }
    return false;
}

bool Person::isOccupied_(std::pair<int, int> crds) {
    for (auto v : personsLocationArray) {
        if( (v.first == crds.first) && (v.second == crds.second) )
            return true;
    }
    return false;
}

bool Person::nodeInList(std::pair<int, int> node, std::vector<std::pair<int, int>> list)
{
    int count = 0;
    for (std::pair<int, int> x : list) {
        if ((node.first == x.first) && (node.second == x.second)) {
            count = count + 1;
        }
    }

    if (count > 0) {
        return true;
    }
    else {
        return false;
    }
}

//car = NULL if dont have one
Person::Person(std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> intersectionsList, const std::string& name, Building* building, Car* owned_vehicle, std::vector<std::pair<double, std::pair<std::string, Building*>>> schedule)
    : intersectionsList_(intersectionsList), name_(name), currentOrigin_(building), ownedCar_(owned_vehicle), schedule_(schedule) {
        
        idxPersonArray_ = personsLocationArray.size();
        personsLocationArray.push_back(location_);
        location_ = currentOrigin_->getEntrance();
        scheduleIndex_= 0;
     }

Person::~Person() {}

const std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> Person::getIntersectionsList() const {return intersectionsList_; }
const std::string &Person::getName() const {return name_;}

//Setter
void Person::updateLocation(std::pair<int,int> newLocation){
    location_ = newLocation;
    personsLocationArray[idxPersonArray_] = newLocation;
}

Person* Person::updateTime(double global_clock, std::vector <TrafficLight*> trafficlight_list){
    std::cout <<"global time: " << global_clock <<std::endl;

    if (schedule_.at(scheduleIndex_).first == global_clock){
        if (getCurrentDestination() == nullptr) {
        // std::cout<<"currentDestination is nullptr, we don't want to change the origin to NULL value"<<std::endl;
        } 
        else {
            //currentDestination is not nullptr
            setNewOrigin(currentDestination_);
            // std::cout<<"set Origin with the past destination"<<std::endl;
        }
        setNewDestination(schedule_.at(scheduleIndex_).second.second);
        // std::cout << "next building's name " << schedule_.at(scheduleIndex_).second.second->getName() << std::endl;
        // std::cout << "schedule Index : "<< scheduleIndex_ <<std::endl;
        // std::cout <<"index increased by 1, get New Destination" << schedule_.at(scheduleIndex_).second.second->getName() <<std::endl;
        // std::cout << "current Origin" << getCurrentOrigin()->getName()<< std::endl;
        // std::cout << "current Destination" << getCurrentDestination()->getName()<< std::endl;
        if (scheduleIndex_ + 1 != schedule_.size()){
            scheduleIndex_++;
        }
    }

    if (getCurrentDestination() != nullptr) {
        // std::cout<<"Walking to destination" <<std::endl;
        this->walk(getCurrentOrigin(), getCurrentDestination(), trafficlight_list);
        // std::cout<< "current location" << getLocation().first << "&" <<getLocation().second <<std::endl;
        // std::cout << "current Destination" << getCurrentDestination()->getName()<< std::endl;    
        return this;
    }
    else{
        // std::cout<<" currentDestination is nullptr so, person doesn't work "<<std::endl;
        return this;
    } 
}   

void Person::setRoute(std::vector<std::pair<int, int> > route) {
        route_.clear();
        for (auto r : route)
            route_.push_back(r);
    }

void Person::setNewOrigin(Building* source){
    currentOrigin_ = source;
}

void Person::setNewDestination(Building* destination){
    currentDestination_ = destination;
}

void Person::update_determine_route(std::vector<std::pair<int,int>> original_route)
{
    std::pair<int, int> origin_building = original_route.front();
    std::pair<int, int> destination = original_route.back();

    // In Walk: after a person Walk, current_node is first updated so this -> getLocation() will get the latest position
    std::pair<int, int> current_node = this->getLocation();

    // this if starts: update_determine_route(current_node, next_intersection(S), destination)
    if (current_node == origin_building)
    {
        updated_determine_route_ = original_route;
    }
    
    else if (current_node == destination){
        if (!updated_determine_route_.empty())
            updated_determine_route_.clear();
    }
    else
    {
        for (unsigned int i = 0; i < this->get_updated_determine_route().size(); i++)
        {
            updated_determine_route_.at(0) = current_node;
            
            // Ask if the current_node is equal to an destination
            if (updated_determine_route_.at(0) == destination) 
            {
                std::cout << "Person arrives at destination" << std::endl;
                updated_determine_route_.clear(); // empty the updated_determine_route once reach destination
            }

            // Ask if the current_node is equal to an intersection
            if (updated_determine_route_.at(0) == updated_determine_route_.at(1))
            {
                updated_determine_route_.erase(updated_determine_route_.begin()); // erase the first element of update_determine_route so the intersection will be the current_node
            }
        }
    }
}

//Getter
const int& Person::getIndexPersonArray() const {return idxPersonArray_;}
const std::vector<std::pair<int,int>>& Person::getRoute() const {return route_;}
const std::string Person::getDirection() const {
    std::string direction = "No";
    std::vector<std::pair<int,int>> route = getRoute();
    for (auto x : route){
    }
    for (std::vector<std::pair<int,int>>::iterator it = route.begin() ; next(it) != route.end(); ++it){
        std::cout << (*it).first << " " << (*it).second << std::endl;
        if (((*it).first == getLocation().first) && ((*next(it)).first == getLocation().first)){
            if (((*it).second-(*next(it)).second) < 0){
                direction = "south";
            }
            else{
                direction =  "north";
            }
        }
        else if (((*it).second == getLocation().second) && ((*next(it)).second == getLocation().second)){
            if (((*it).first-(*next(it)).first) < 0){
                direction =  "east";
            }
            else{
                direction =  "west";
            }
        }
    }
    return direction;
}

const std::vector<std::pair<double, std::pair<std::string, Building*>>>& Person::getSchedule() const{return schedule_;}
const std::pair<int, int>& Person::getLocation() const{return location_;}
Building* const& Person::getCurrentOrigin() const{return currentOrigin_;}
Building* const& Person::getCurrentDestination() const{return currentDestination_;}
const std::vector<std::pair<int,int>> Person::get_updated_determine_route() const
{
    return updated_determine_route_;
}

void Person::walk(Building* origin, Building* destination, std::vector<TrafficLight*> trafficLight_list){

    std::vector<std::pair<int,int>> route = updated_determine_route_;
    setRoute(route);
    std::vector< std::pair<int, int> > origin_route = determineRoute_(origin, destination); 
    
    update_determine_route(origin_route); 


    while (!route.empty()) 
    {   
        /* Used terms:
        - current node: this the current node where person is
        - next_node: the node that is right next to person is (in any direction)  
        - next_significant_node: either intersection or destination 
        */
        std::pair<int, int> current_node = route.at(0);
        std::pair<int, int> next_significant_node = route.at(1); // This will never be out of index because when current_node == destination: check line 32;
        
        
        if ( current_node.first == next_significant_node.first ) // Move on the y axis
        {
            // person walk vertically, moving North
            if ( current_node.second < next_significant_node.second ) 
            {
                std::pair<int, int> next_node = std::make_pair(current_node.first ,current_node.second+1); // first_coor is locked

                // check if next node is occupied or if it's intersection
                if (isOccupied_(next_node) == false && next_node.second != next_significant_node.second)
                {
                    // while not occupied, not intersection ahead: 
                    current_node.second++;
                    updateLocation(current_node);

                    //Debug: 
                    update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                    route = this -> get_updated_determine_route();
                    
                    break;
                    // next_node.second++; // might not need because if the time is control from outside drive, then this call won't valid 
                }

                else if (isOccupied_(next_node))
                {
                    break;
                }

                // the next node from current will be either intersection or end address
                else if (next_node.second == next_significant_node.second) 
                {

                    if (isIntersection_(next_node)){
                        TrafficLight* trafficLight = findTrafficLight(trafficLight_list, next_node);
                        if (!trafficLight -> isGreen(current_node))
                        {
                            break;
                        }
                        else if (trafficLight->isGreen(current_node) && isOccupied_(next_node) == false)
                        {
                            current_node.second++; // -> current_node.second++ == next_significant_node.second
                            updateLocation(current_node);

                            //Debug: 
                            update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                            route = this -> get_updated_determine_route();
                            break;
                        }
                    }

                    else 
                    {
                        // if not intersection then it will be destination: 
                        current_node.second++; // -> current_node.second++ == next_significant_node.second
                        updateLocation(current_node);



                        //Debug: 
                        update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                        route = this -> get_updated_determine_route();
                        this -> getIntoBuilding(*destination);
                        std::cout << "Size: ----- " << route.size() << std::endl;
                        break;
                    }
                }                   
            }

            // person walk vertically, moving South
            else if ( current_node.second > next_significant_node.second ) // --> will change to else 
            {
                std::pair<int, int> next_node = std::make_pair(current_node.first ,current_node.second - 1); // first_coor is locked

                // check available of next node or if it's intersection
                if (isOccupied_(next_node) == false && next_node.second != next_significant_node.second)
                {
                    // while not occupied, not intersection ahead: 
                    current_node.second--;
                    updateLocation(current_node);
                    
                    //Debug: 
                    update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                    route = this -> get_updated_determine_route();

                    break;

                    // next_node.second++; // might not need because if the time is control from outside drive, then this call won't valid 
                }

                else if (isOccupied_(next_node))
                {
                    break;
                }

                // the next node from current will be either intersection or end address
                else if (next_node.second == next_significant_node.second) 
                {

                    if (isIntersection_(next_node)){
                        TrafficLight* trafficLight = findTrafficLight(trafficLight_list, next_node);
                        if (!trafficLight -> isGreen(current_node))
                        {
                            break;
                        }
                        else if (trafficLight -> isGreen(current_node) && isOccupied_(next_node) == false)
                        {
                            current_node.second--; // -> current_node.second-- == next_significant_node.second
                            updateLocation(current_node);

                            //Debug: 
                            update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                            route = this -> get_updated_determine_route();
                            break;
                        }
                    }
                    else
                    {
                        // if not intersection then it will be destination: 
                        current_node.second--; // -> current_node.second++ == next_significant_node.second
                        updateLocation(current_node);


                        //Debug: 
                        update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                        route = this -> get_updated_determine_route();
                        this -> getIntoBuilding(*destination);

                        break;
                    }
                    
                }               
            }
        }

        // if starting_point_y == next_point_y --> person walk horizontally
        else if ( current_node.second == next_significant_node.second )
        {
            // person walk horizontally, moving East
            if ( current_node.first < next_significant_node.first ) 
            {
                std::pair<int, int> next_node = std::make_pair(current_node.first + 1 ,current_node.second); // second_coor is locked

                // check available of next node or if it's intersection
                if (isOccupied_(next_node) == false && next_node.first != next_significant_node.first)
                {
                    // while not occupied, not intersection ahead: 
                    current_node.first++;
                    updateLocation(current_node);
                    
                    //Debug: 
                    update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                    route = this -> get_updated_determine_route();
                    break;

                    // next_node.first++; // might not need because if the time is control from outside drive, then this call won't valid 
                }

                else if (isOccupied_(next_node))
                {
                    break;
                }

                // the next node from current will be either intersection or end address
                else if (next_node.first == next_significant_node.first) 
                {

                    if (isIntersection_(next_node)){
                        TrafficLight* trafficLight = findTrafficLight(trafficLight_list, next_node);
                        if (!trafficLight -> isGreen(current_node))
                        {
                            break;
                        }
                        else if (trafficLight -> isGreen(current_node) && isOccupied_(next_node) == false)
                        {
                            current_node.first++; // -> current_node.second++ == next_significant_node.second
                            updateLocation(current_node);

                            //Debug: 
                            update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                            route = this -> get_updated_determine_route();
                            break;
                        }
                    }
                    else 
                    {
                        // if not intersection then it will be destination: 
                        current_node.first++; // -> current_node.second++ == next_significant_node.second
                        updateLocation(current_node);
                        //Debug: 
                        update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                        route = this -> get_updated_determine_route();
                        this -> getIntoBuilding(*destination);
                        break;
                    }
                }   
            }

            // person walk horizontally, moving West
            else if ( current_node.first > next_significant_node.first ) // --> will change to else 
            {
                std::pair<int, int> next_node = std::make_pair(current_node.first + 1 ,current_node.second); // second_coor is locked

                // check available of next node or if it's intersection
                if (isOccupied_(next_node) == false && next_node.first != next_significant_node.first)
                {
                    // while not occupied, not intersection ahead: 
                    current_node.first--;
                    updateLocation(current_node);
                    
                    //Debug: 
                    update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                    route = this -> get_updated_determine_route();
                    break;

                    // next_node.first++; // might not need because if the time is control from outside drive, then this call won't valid 
                }

                else if (isOccupied_(next_node))
                {
                    break;
                }

                // the next node from current will be either intersection or end address
                else if (next_node.first == next_significant_node.first) 
                {

                    if (isIntersection_(next_node)){
                        TrafficLight* trafficLight = findTrafficLight(trafficLight_list, next_node);
                        if (!trafficLight -> isGreen(current_node))
                        {
                            break;
                        }
                        else if (trafficLight -> isGreen(current_node) && isOccupied_(next_node) == false)
                        {
                            current_node.first--; // -> current_node.second++ == next_significant_node.second
                            updateLocation(current_node);

                            
                            //Debug: 
                            update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                            route = this -> get_updated_determine_route();
                            break;
                        }
                    }
                    else 
                    {
                        // if not intersection then it will be destination: 
                        current_node.first++; // -> current_node.second++ == next_significant_node.second
                        updateLocation(current_node);
                        //Debug: 
                        update_determine_route(origin_route); // will not needed in final version because the update will be done before while loop
                        route = this -> get_updated_determine_route();
                        this -> getIntoBuilding(*destination);
                        
                        break;
                    }
                }   
            }
        }
        break;
    }
}

//Member Functions
void Person::getIntoBuilding(Building& b){
    b.accommodate(this);
    // this->location_ = b.getCoordinateArray().at(0);
    updateLocation (b.getCoordinateArray().at(0));
}
void Person::getIntoCar(Car& v){
    if (v.getPassengers().size() < v.getMaxCapacity()){
        v.accommodate(this);
    }
}

TrafficLight* Person::findTrafficLight (std::vector<TrafficLight*> trafficLight_list, std::pair<int, int> coordinates)
{
    for (unsigned int i = 0; i < trafficLight_list.size(); i++)
    {
        if (trafficLight_list.at(i) ->getLocation() == coordinates);
            return trafficLight_list.at(i);
    }
    return nullptr;
}

