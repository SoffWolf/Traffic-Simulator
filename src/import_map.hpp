#pragma once

#include "pugixml-1.10/src/pugixml.hpp"
//#include "pugixml-1.10/src/pugixml.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

class xml_parser {
    public:
        xml_parser(const char* file_name);
        std::vector<std::pair<std::string, std::vector<std::pair<int, int> > > > waysList;
        std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string> > > intersectionsList;
        std::vector<std::pair<std::pair<std::string,std::string>, std::pair<std::pair<int,int>,std::vector<std::pair<int,int>>>>> buildingsList;
        std::vector<int> staticMap;
    private:
        const char* file_name_;

        std::vector<std::pair<std::string, std::vector<std::pair<int, int> > > > get_ways_list_();
        std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string> > > get_intersections_list_();
        std::vector<std::pair<std::pair<std::string,std::string>, std::pair<std::pair<int,int>,std::vector<std::pair<int,int>>>>> get_buildings_list_();
        std::vector<int> get_static_map_();

};

