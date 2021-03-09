//using namespace std;

#include <iostream>
#include "mapping/map.h"

namespace map_builder{

/*
"elsehere":
    controllers::map real_space = build_pm_real();

"also elsewhere":
    build_real_space_map(34, 32, 8, 12, 2, my_map());
    
---------------------------------------
controllers::map build_pm_real() {
    controllers::map output;

    //... code 

    return output;
}
*/


//function that builds the map for A*
//hardcoded rn are the values for Southeastcon 2021 pacman
controllers::map build_real_pman_map(){
     int wallThickness = 3;
     int mapHeight = 96;
     int mapWidth = 192;
     int foot = 24;
     int inch = 2;

    controllers::map realMap = controllers::map(mapHeight, mapWidth);
    //setters calle
    realMap.setWallThickness(3);
    realMap.setRobotSize(14);

    // controllers::map meep(mapHeight,mapWidth);
    //4 Outer Walls
    realMap.addWall(0,0, wallThickness, mapHeight);
    realMap.addWall(0,0,mapWidth,  wallThickness);
    realMap.addWall(mapWidth-wallThickness, 0, wallThickness, mapHeight);
    realMap.addWall(0, mapHeight-wallThickness, mapWidth, wallThickness);

    //Rect A
    realMap.addWall(0,0, foot + 6*inch + wallThickness, 8*inch + wallThickness);
    //Rect B
    realMap.addWall(3*foot + 5*inch, 0, foot + 2*inch, 8*inch+wallThickness);
    //Rect D
    realMap.addWall(0, wallThickness + 8*inch + 10*inch, foot+10*inch+1 + 2*wallThickness, 5*inch+1);

    //Awkward wall between A and B
    realMap.addWall(foot + 6*inch + wallThickness + 10*inch, 0, wallThickness, 8*inch + wallThickness);
    //Vertcal wall to the right of F
    realMap.addWall(2 * foot, mapHeight - (11*inch + 1), wallThickness, 11*inch+1);
    //Horizontal wall above that wall
    realMap.addWall(2*foot - (foot - wallThickness), mapHeight-(11*inch + 1 + wallThickness), foot, wallThickness);
    //Short wall up and left from start
    realMap.addWall(2*foot + wallThickness + 10*inch, mapHeight-(11*inch + 1 + wallThickness), 7*inch + 1, wallThickness);
    //Long horizontal wall of T above start
    realMap.addWall(foot + 10*inch + 1 + wallThickness + 10*inch, wallThickness+8*inch + 10*inch, 2*foot + 1*inch, wallThickness);
    //Short vertical wall of T above start
    realMap.addWall(foot + 10*inch + 1 + wallThickness + 10*inch + foot + wallThickness, wallThickness+8*inch + 10*inch + wallThickness, wallThickness, 5*inch);

    realMap.reflectOnYAxis();

    return realMap;
    //print for debugging map
    //m.print();
}

controllers::map build_config_space_map(controllers::map realMap)//int wallThickness, int mapHeight, int mapWidth, int robotSize){
   
   controllers::map configMap;
   configMap.map();
   
    // int wallThickness = 3;
    // int mapHeight = 96;
    // int mapWidth = 192;
    // int foot = 24;
    //int inch = 2;
    //robotSize = 14 //10 inches nomrally, but we are using 1/2 inch to 7*2 =14

    //controllers::map configMap(mapHeight,mapWidth);
    
    //computations for config space
    //use bottom left of robot for origin reference
    wallThickness += robotSize;


    //4 Outer Walls
    configMap.addWall(0,0, wallThickness, mapHeight + robotSize);
    configMap.addWall(0,0,mapWidth,  wallThickness + robotSize);
    configMap.addWall(mapWidth-wallThickness, 0, wallThickness, mapHeight);
    configMap.addWall(0, mapHeight-wallThickness, mapWidth, wallThickness);

    //Rect A
    configMap.addWall(0,0, robotSize + foot + 6*inch + wallThickness, 8*inch + wallThickness);
    //Rect B
    configMap.addWall(3*foot + 5*inch, 0, foot + 2*inch, robotSize + 8*inch+wallThickness);
    //Rect D
    configMap.addWall(0, wallThickness + 8*inch + 10*inch, foot+10*inch+1 + 2*wallThickness, 5*inch+1+robotSize);

    //Awkward wall between A and B
    configMap.addWall(foot + 6*inch + wallThickness + 10*inch + robotSize, 0, wallThickness, 8*inch + wallThickness + robotSize);
    //Vertcal wall to the right of F
    configMap.addWall(2 * foot, mapHeight - (11*inch + 1), wallThickness + robotSize, 11*inch+1);
    //Horizontal wall above that wall
    configMap.addWall(2*foot - (foot - wallThickness), mapHeight-(11*inch + 1 + wallThickness), foot, wallThickness);
    //Short wall up and left from start
    configMap.addWall(2*foot + wallThickness + 10*inch, mapHeight-(11*inch + 1 + wallThickness), 7*inch + 1, wallThickness);
    //Long horizontal wall of T above start
    configMap.addWall(foot + 10*inch + 1 + wallThickness + 10*inch, wallThickness+8*inch + 10*inch, 2*foot + 1*inch, wallThickness);
    //Short vertical wall of T above start
    configMap.addWall(foot + 10*inch + 1 + wallThickness + 10*inch + foot + wallThickness, wallThickness+8*inch + 10*inch + wallThickness, wallThickness, 5*inch);

    configMap.reflectOnYAxis();

    return configMap;
    //print for debugging map
    //m.print();

}
}