# Traffic-Simulator
A traffic simulator in C++, that can generate cars and pedestrians under the instructions of the users.

We construct maps by editing a XML file (inspired by Open Street Map), then we import that file into a graphical program written in C++ to visualize the map, and build traffic objects using C++ on top of the map.

The list of interactive objects in the map includes road, car, pedestrian, bus, building, traffic light, and many more.

The car and pedestrain navigate from the starting point to the destination using the A* algorithm.

For more detail please read the documentation: https://docs.google.com/document/d/1-DKgzNFHMP9c-G3yBtJF9jeh5upZ_mUxjd-pqg5ba1s/edit?usp=sharing

Demo video: https://youtu.be/aYBN_SPCFEc


# Dependency
* `SFML` 
* `pugixml-1.10`
# Folder Structure
 * `plan/` -- Project plan 
 * `doc/`  -- The documentation sources related to the project
 * `src/`  -- Source files. 

# Credits
Tung Nguyen, Mahmoud Gadalla, Lac Truong (Sophie Truong), Gyeha Lim


