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
     //int wallThickness = 3;
     //int mapHeight = 96;
     //int mapWidth = 192;
     int foot = 24;
     int inch = 2;

    controllers::map realMap(192, 96);

    //setters called
    realMap.setWallThickness(3);
    realMap.setRobotSize(14);
    realMap.setVmapCols(192);
    realMap.setVmapRow(96);
    // controllers::map meep(mapHeight,mapWidth);
    //4 Outer Walls
    realMap.addWall(0,0, realMap.getWallThickness(), realMap.getVmapRow());
    realMap.addWall(0,0,realMap.getVmapCols(),  realMap.getWallThickness());
    realMap.addWall(realMap.getVmapCols()-realMap.getWallThickness(), 0, realMap.getWallThickness(), realMap.getVmapRow());
    realMap.addWall(0, realMap.getVmapRow()-realMap.getWallThickness(), realMap.getVmapCols(), realMap.getWallThickness());
    std::cout << "Adding outer walls" << std::endl;
    //Rect A
    realMap.addWall(0,0, foot + 6*inch + realMap.getWallThickness(), 8*inch + realMap.getWallThickness());
    //Rect B
    realMap.addWall(3*foot + 5*inch, 0, foot + 2*inch, 8*inch+realMap.getWallThickness());
    //Rect D
    realMap.addWall(0, realMap.getWallThickness() + 8*inch + 10*inch, foot+10*inch+1 + 2*realMap.getWallThickness(), 5*inch+1);
    std::cout << "Added rectangles" << std::endl;
    //Awkward wall between A and B
    realMap.addWall(foot + 6*inch + realMap.getWallThickness() + 10*inch, 0, realMap.getWallThickness(), 8*inch + realMap.getWallThickness());
    //Vertcal wall to the right of F
    realMap.addWall(2 * foot, realMap.getVmapRow() - (11*inch + 1), realMap.getWallThickness(), 11*inch+1);
    //Horizontal wall above that wall
    realMap.addWall(2*foot - (foot - realMap.getWallThickness()), realMap.getVmapRow()-(11*inch + 1 + realMap.getWallThickness()), foot, realMap.getWallThickness());
    //Short wall up and left from start
    realMap.addWall(2*foot + realMap.getWallThickness() + 10*inch, realMap.getVmapRow()-(11*inch + 1 + realMap.getWallThickness()), 7*inch + 1, realMap.getWallThickness());
    //Long horizontal wall of T above start
    realMap.addWall(foot + 10*inch + 1 + realMap.getWallThickness() + 10*inch, realMap.getWallThickness()+8*inch + 10*inch, 2*foot + 1*inch, realMap.getWallThickness());
    //Short vertical wall of T above start
    realMap.addWall(foot + 10*inch + 1 + realMap.getWallThickness() + 10*inch + foot + realMap.getWallThickness(), realMap.getWallThickness()+8*inch + 10*inch + realMap.getWallThickness(), realMap.getWallThickness(), 5*inch);

    realMap.reflectOnYAxis();

    return realMap;
    //print for debugging map
    //m.print();
}

controllers::map build_config_space_map(controllers::map realMap){
   
    std::cout<<"creating base map"<<std::endl;

   controllers::map configMap(192,96);
   
    // int wallThickness = 3;
    // int mapHeight = 96;
    // int mapWidth = 192;
     int foot = 24;
     int inch = 2;
    //robotSize = 14 //10 inches nomrally, but we are using 1/2 inch to 7*2 =14

    //controllers::map configMap(mapHeight,mapWidth);
    
    //computations for config space
    //use bottom left of robot for origin reference
    configMap.setWallThickness(3 + 14);

    std::cout<<"adding outer walls" <<std::endl;
    //4 Outer Walls
    configMap.addWall(0,0, realMap.getWallThickness(), realMap.getVmapRow() + realMap.getRobotSize());
    std::cout<<"added 1"<<std::endl;
    configMap.addWall(0,0,realMap.getVmapCols(),  realMap.getWallThickness() + realMap.getRobotSize());
    std::cout<<"added 2"<<std::endl;
    configMap.addWall(realMap.getVmapCols()-realMap.getWallThickness(), 0, realMap.getWallThickness(), realMap.getVmapRow());
    std::cout<<"added 3"<<std::endl;
    configMap.addWall(0, realMap.getVmapRow()-realMap.getWallThickness(), realMap.getVmapCols(), realMap.getWallThickness());
    std::cout<<"added 4"<<std::endl;

    std::cout<<"Adding ABD"<<std::endl;
    //Rect A
    configMap.addWall(0,0, realMap.getRobotSize() + foot + 6*inch + realMap.getWallThickness(), 8*inch + realMap.getWallThickness());
    //Rect B
    configMap.addWall(3*foot + 5*inch, 0, foot + 2*inch, realMap.getRobotSize() + 8*inch+realMap.getWallThickness());
    //Rect D
    configMap.addWall(0, realMap.getWallThickness() + 8*inch + 10*inch, foot+10*inch+1 + 2*realMap.getWallThickness(), 5*inch+1+realMap.getRobotSize());

    std::cout<<"Adding awkard stuff"<<std::endl;
    //Awkward wall between A and B
    configMap.addWall(foot + 6*inch + realMap.getWallThickness() + 10*inch + realMap.getRobotSize(), 0, realMap.getWallThickness(), 8*inch + realMap.getWallThickness() + realMap.getRobotSize());
    //Vertcal wall to the right of F
    configMap.addWall(2 * foot, realMap.getVmapRow() - (11*inch + 1), realMap.getWallThickness() + realMap.getRobotSize(), 11*inch+1);
    //Horizontal wall above that wall
    configMap.addWall(2*foot - (foot - realMap.getWallThickness()), realMap.getVmapRow()-(11*inch + 1 + realMap.getWallThickness()), foot, realMap.getWallThickness());
    //Short wall up and left from start
    configMap.addWall(2*foot + realMap.getWallThickness() + 10*inch, realMap.getVmapRow()-(11*inch + 1 + realMap.getWallThickness()), 7*inch + 1, realMap.getWallThickness());
    //Long horizontal wall of T above start
    configMap.addWall(foot + 10*inch + 1 + realMap.getWallThickness() + 10*inch, realMap.getWallThickness()+8*inch + 10*inch, 2*foot + 1*inch, realMap.getWallThickness());
    //Short vertical wall of T above start
    configMap.addWall(foot + 10*inch + 1 + realMap.getWallThickness() + 10*inch + foot + realMap.getWallThickness(), realMap.getWallThickness()+8*inch + 10*inch + realMap.getWallThickness(), realMap.getWallThickness(), 5*inch);

    configMap.reflectOnYAxis();

    return configMap;
//     //print for debugging map
//     //m.print();

}
}