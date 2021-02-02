#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <time.h>
#include <stdlib.h> /* srand, rand */


#include "pugixml-1.10/src/pugixml.hpp"
#include "import_map.hpp"
#include "car.hpp"
#include "trafficLight.hpp"
#include "person.hpp"
#include "building.hpp"
#include "tileMap.hpp"





int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Tilemap");

    xml_parser xml_doc("the_3x3_map.xml");
    std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>>>> buildingsList = xml_doc.buildingsList;
    std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> intersectionsList = xml_doc.intersectionsList;    

    //init building and put in a list-buildings
    std::vector<Building*> buildings;
    for (unsigned int i = 0; i < buildingsList.size(); i++){
        Building* building = new Building(buildingsList[i]); 
        buildings.push_back(building);
    }

    //init trafficlight and put them in a list-trafficlights
    std::vector <TrafficLight*> trafficlights;
    for (unsigned int i =0 ; i< intersectionsList.size(); i++)
    {
        TrafficLight* light = new TrafficLight(intersectionsList.at(i).first);
        trafficlights.push_back(light);
    }


    
    //init car here
    int cars_number;
    std::cout << "Please enter number of car in the map: " << std::endl;
    std::cin >> cars_number;
    std::vector<Car*> cars;
    for (int i =0; i < cars_number; i++){
        Building* initial_building = buildings[rand() % buildings.size()];
        Car* car = new Car(*initial_building, initial_building->getEntrance(), intersectionsList, 10);
        car->setDestination(buildings[rand() % buildings.size()]);
        cars.push_back(car);
    }

    // Car test_car("CAR", *buildings[4], buildings[4]->getEntrance(), intersectionsList);

    
    //init person here
    int people_number;
    std::cout << "Please enter number of people in the map: " << std::endl;
    std::cin >> people_number;
    std::vector<Person*> people;
    std::vector<std::string> tasks_list{"Debug", "Eat", "Study", "Work", "Sleep", "Play"};
    for (int i =0; i < people_number; i++){
        Building* initial_building = buildings[rand() % buildings.size()];
        //we need more tasks than this
        std::vector<std::pair<double, std::pair<std::string, Building*>>> schedule ;
        schedule.push_back(std::make_pair(rand() % 24 + 0, std::make_pair(tasks_list[rand() % (tasks_list.size()-1)], buildings[rand() % buildings.size()])));
        Person* person = new Person(intersectionsList, "Tung", initial_building, NULL, schedule);
        people.push_back(person);
    }
    // std::map<double, std::pair<std::string, Building*>> schedule;
    // std::map<double, std::pair<std::string, Building*>> schedule_2;
    // schedule[7.00] = std::make_pair("Debug", buildings[3]); 
    // schedule_2[7.50] = std::make_pair("Debug_2", buildings[1]);

    // Person test_person(intersectionsList, "Tung", buildings[3]->getEntrance(), NULL, schedule);
    // Person test_person_2(intersectionsList, "Sophie", buildings[1]->getEntrance(), NULL, schedule_2);

    ////////////////////////////start to handle time, run the simulation
    double time_counter = 0;
    const int NUM_SECONDS = 1;
    clock_t this_time = clock();
    clock_t last_time = this_time;

    double global_clock = 0;


    // for (int it : staticMap){
    //         std::cout << it;
    //     }
    // std::cout << std::endl;

    while (window.isOpen()) {

        

        this_time = clock();
        time_counter += (double)(this_time - last_time);
        last_time = this_time;

        if (time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC)){ 
            time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
            global_clock++;
            for ( TrafficLight* it : trafficlights){
                
                for (auto i : people){
                    i = i->updateTime(global_clock, trafficlights);
                }
                for (Car* x: cars){
                    x->drive(&x->getBuilding(), x->getDestination(), trafficlights);
                }
                
                // test_person.updateTime(global_clock); // seems to not update anything
                it -> update(NUM_SECONDS);
                std::vector<int> staticMap = xml_doc.staticMap;
                
///////////////////////////////////////////////////////////////////////////////////Handle the matrix changes
                ////////////TRAFFIC LIGHT
                for (TrafficLight* x : trafficlights){
                    int tile_south;
                    int tile_north;
                    int tile_west;
                    int tile_east;
                    //south traffic light
                    if (x->isGreen(std::make_pair(x->getLocation().first+1, x->getLocation().second))){
                        tile_south = 6;
                    }
                    else {tile_south = 5;}
                    //north
                    if (x->isGreen(std::make_pair(x->getLocation().first-1, x->getLocation().second))){
                        tile_north = 6;
                    }
                    else {tile_north = 5;}
                    //west
                    if (x->isGreen(std::make_pair(x->getLocation().first, x->getLocation().second - 1))){
                        tile_west = 6;
                    }
                    else {tile_west = 5;}
                    //east
                    if (x->isGreen(std::make_pair(x->getLocation().first, x->getLocation().second + 1))){
                        tile_east = 6;
                    }
                    else {tile_east = 5;}
                    
                    staticMap[(x->getLocation().first+1)*100 + x->getLocation().second+2] = tile_south;
                    staticMap[(x->getLocation().first-3)*100 + x->getLocation().second-2] = tile_north;
                    staticMap[(x->getLocation().first+1)*100 + x->getLocation().second-2] = tile_west;
                    staticMap[(x->getLocation().first-3)*100 + x->getLocation().second+2] = tile_east;
                }
                /////PERSON
                for (Person* person : people){
                    if (person->getRoute().size() != 0){
                        std::string direction = person->getDirection();
                        if (direction == "south"){
                            staticMap[(person->getLocation().first -1 + 2)*100 + person->getLocation().second] = 9;
                        }
                        else if (direction == "north"){
                            staticMap[(person->getLocation().first -1 -2)*100 + person->getLocation().second] = 9;
                        }
                        else if (direction == "west"){
                            staticMap[(person->getLocation().first-1)*100 + person->getLocation().second + 2] = 9;
                        }
                        else if (direction == "east"){
                            staticMap[(person->getLocation().first-1)*100 + person->getLocation().second - 2] = 9;
                        }
                    }
                }
                ///////////////////////////CAR
                for (Car* car : cars){
                    if (car->getRoute().size() != 0){
                        std::string direction = car->getDirection();
                        if (direction == "south"){
                            staticMap[(car->getLocation().first -1 +1)*100 + car->getLocation().second] = 10;
                        }
                        else if (direction == "north"){
                            staticMap[(car->getLocation().first -1 -1)*100 + car->getLocation().second] = 10;
                        }
                        else if (direction == "west"){
                            staticMap[(car->getLocation().first - 1)*100 + car->getLocation().second + 1] = 10;
                        }
                        else if (direction == "east"){
                            staticMap[(car->getLocation().first - 1)*100 + car->getLocation().second -1] = 10;
                        }
                    }
                }
                // for (int it : staticMap){
                //     std::cout << it;
                // }
                // std::cout << std::endl;
                
                

                //GUI
                    int* next_level_shit = &staticMap[0];//////////////////////////////////
                    TileMap map;
                    if (!map.Load("tinytile.png", sf::Vector2u(10, 10), next_level_shit, 100, 100));
                    // handle events
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if(event.type == sf::Event::Closed)
                            window.close();
                    }

                    // draw the map
                    window.clear();
                    window.draw(map);
                    window.display();
                
            }
        }
        
    }
    std::vector<std::pair<std::string, int>> load_on_da_road;
    for (std::pair<std::string, std::vector<std::pair<int, int> > > way : xml_doc.waysList){
        int traffic_count = 0;
        if (way.second[0].first == way.second[1].first){
            for (Car* x : cars){
                if (x->getLocation().first == way.second[0].first){traffic_count ++;}
            }
        }
        else if (way.second[0].second == way.second[1].second){
            for (Car* x : cars){
                if (x->getLocation().second == way.second[0].second){traffic_count ++;}
            }
        }
        load_on_da_road.push_back(std::make_pair(way.first, traffic_count));
    }
    //print the result
    for (std::pair<std::string, int> result : load_on_da_road){
        std::cout << result.first << " : " << result.second << std::endl;
    }
    
    return 0;
}

