// #include "pugixml-1.10/src/pugixml.hpp"
// #include "pugixml-1.10/src/pugixml.cpp"
#include "import_map.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>


xml_parser::xml_parser(const char* file_name)
  : file_name_(file_name){
    waysList = get_ways_list_();
    intersectionsList = get_intersections_list_();
    buildingsList = get_buildings_list_();
    staticMap = get_static_map_();
}

std::vector<std::pair<std::string, std::vector<std::pair<int, int> > > > xml_parser::get_ways_list_(){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_name_);
    pugi::xml_node root = doc.document_element();

    pugi::xml_node ways = root.child("ways");
    std::vector<std::pair<std::string, std::vector<std::pair<int, int> > > > ways_list;
    for (pugi::xml_node i = ways.first_child(); i; i = i.next_sibling()){
        std::vector<std::pair<int, int> > two_ends;
        std::pair<int, int> start_node = std::make_pair(i.first_child().attribute("lon").as_int(), i.first_child().attribute("lat").as_int());
        std::pair<int, int> end_node = std::make_pair(i.last_child().attribute("lon").as_int(), i.last_child().attribute("lat").as_int());
        //add the 2 node to the output list
        two_ends.push_back(start_node);
        two_ends.push_back(end_node);
        ways_list.push_back(std::make_pair(i.attribute("name").as_string(), two_ends));
    }
    return ways_list;
}


std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string> > > xml_parser::get_intersections_list_(){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_name_);
    pugi::xml_node root = doc.document_element();

    pugi::xml_node intersections = root.child("intersections");
    std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string> > > intersections_list;
    for (pugi::xml_node i = intersections.first_child(); i; i = i.next_sibling()){
        std::pair<int, int> coordinate = std::make_pair(i.attribute("lon").as_int(), i.attribute("lat").as_int());
        std::pair<std::string, std::string> two_roads = std::make_pair(i.first_child().attribute("name").as_string(), i.last_child().attribute("name").as_string());
        intersections_list.push_back(std::make_pair(coordinate, two_roads));
        int position = (coordinate.second-1)*100 + coordinate.first;
    }
    return intersections_list;
}
//buildings_list(std::make_pair(std::pair(name, type) std::make_pair(entrance, Coor_list)));
std::vector<std::pair<std::pair<std::string,std::string>, std::pair<std::pair<int,int>,std::vector<std::pair<int,int>>>>> xml_parser::get_buildings_list_(){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_name_);
    pugi::xml_node root = doc.document_element();
    //Get all the building
    //return a list of pair of < building_name, <all_the_nodes>>
    pugi::xml_node buildings = root.child("buildings");
    std::vector<std::pair<std::pair<std::string,std::string>, std::pair<std::pair<int,int>,std::vector<std::pair<int,int>>>>> buildings_list;
    for (pugi::xml_node i = buildings.first_child(); i; i = i.next_sibling()){
        std::string name = i.attribute("name").as_string();
        std::string type = i.attribute("type").as_string();
        int entrance_lon = i.attribute("entrance_lon").as_int();
        int entrance_lat = i.attribute("entrance_lat").as_int();
        std::vector<std::pair<int, int> > coor_list;
        for (pugi::xml_node node = i.first_child(); node; node = node.next_sibling()){
            std::pair<int, int> coordinate = std::make_pair(node.attribute("lon").as_int(), node.attribute("lat").as_int());
            coor_list.push_back(coordinate);
        }
        buildings_list.push_back(std::make_pair(std::make_pair(name, type), std::make_pair(std::make_pair(entrance_lon, entrance_lat), coor_list)));
    }
    return buildings_list;
}

std::vector<int> xml_parser::get_static_map_(){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_name_);
    pugi::xml_node root = doc.document_element();

    std::vector<int> static_map(10000, 7);

        // Get all the road, return list of start_node and end_node for each
    // a list of pairs of <road_name, <start_node, end_node>>
    pugi::xml_node ways = root.child("ways");
    for (pugi::xml_node i = ways.first_child(); i; i = i.next_sibling()){
        std::pair<int, int> start_node = std::make_pair(i.first_child().attribute("lon").as_int(), i.first_child().attribute("lat").as_int());
        std::pair<int, int> end_node = std::make_pair(i.last_child().attribute("lon").as_int(), i.last_child().attribute("lat").as_int());
        //add all the node to the static map vector for graphical use, road is 1
        //vertical
        if (start_node.first == end_node.first){
            int position = (start_node.second-1)*100 + start_node.first;
            while (position != (end_node.second-1)*100 + end_node.first){
                static_map[position] = 1;
                static_map[position-1] = 0;
                static_map[position+1] = 0;
                static_map[position-2] = 8;
                static_map[position+2] = 8;
                position = position + 100;
            }
        }
        else{
            int position = (start_node.second-1)*100 + start_node.first;
            while (position != (end_node.second-1)*100 + end_node.first){
                static_map[position] = 2;
                static_map[position-100] = 0;
                static_map[position+100] = 0;
                static_map[position-200] = 8;
                static_map[position+200] = 8;
                position = position + 1;
            }
        }
    }
    //Get all the intersection
    //return a list of pairs of < <lon,lat>, <road1, road2> >
    pugi::xml_node intersections = root.child("intersections");
    for (pugi::xml_node i = intersections.first_child(); i; i = i.next_sibling()){
        std::pair<int, int> coordinate = std::make_pair(i.attribute("lon").as_int(), i.attribute("lat").as_int());
        int position = (coordinate.second-1)*100 + coordinate.first;
        //intersection is 2
        static_map[position]= 3;
        static_map[position-198]= 6;
        static_map[position-202]= 6;
        static_map[position+198]= 6;
        static_map[position+202]= 6;

        static_map[position-98]= 0;
        static_map[position-99]= 0;
        static_map[position-101]= 0;
        static_map[position-102]= 0;
        static_map[position+98]= 0;
        static_map[position+99]= 0;
        static_map[position+101]= 0;
        static_map[position+102]= 0;
        static_map[position-199]= 0;
        static_map[position-201]= 0;
        static_map[position+199]= 0;
        static_map[position+201]= 0;

        static_map[position-1]= 2;
        static_map[position-2]= 2;
        static_map[position+1]= 2;
        static_map[position+2]= 2;
        static_map[position-100]= 1;
        static_map[position-200]= 1;
        static_map[position+100]= 1;
        static_map[position+200]= 1;
    }


    //Get all the building
    //return a list of pair of < building_name, <all_the_nodes>>
    pugi::xml_node buildings = root.child("buildings");
    for (pugi::xml_node i = buildings.first_child(); i; i = i.next_sibling()){
        //std::cout << i.attribute("name").value();
        std::string name = i.attribute("name").as_string();
        std::vector<std::pair<int, int> > coor_list;
        for (pugi::xml_node node = i.first_child(); node; node = node.next_sibling()){
            std::pair<int, int> coordinate = std::make_pair(node.attribute("lon").as_int(), node.attribute("lat").as_int());
            coor_list.push_back(coordinate);
        }

        //building is 11
        for (std::pair<int, int> node : coor_list){
            int position = (node.second-1)*100 + node.first;
            static_map[position] = 4;
        }
    }
    return static_map;
}




// int main(){
//     xml_parser xml_doc("the_map.xml");
//     for (int x: xml_doc.staticMap){
//         std::cout << x;
//     }
//     std::cout << std::endl;
// }
//     // xml_doc.get_ways_list_();
//     // xml_doc.get_buildings_list_();
//     // xml_doc.get_intersections_list_();
//     // for (std::pair<std::string, std::vector<std::pair<int, int>>> buildings : xml_doc.get_ways_list_()){
//     //     std::cout << buildings.first        ;
//     // }
//     // std::cout << std::endl;

// // }

