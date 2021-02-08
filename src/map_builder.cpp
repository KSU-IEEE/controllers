//using namespace std;

#include "mapping/map.h"

namespace map_builder{
//function that builds the map for A*
//hardcoded rn are the values for Southeastcon 2021 pacman
void build_real_space_map(int wallThickness, int mapHeight, int mapWidth, int foot, int inch){
    // int wallThickness = 3;
    // int mapHeight = 96;
    // int mapWidth = 192;
    // int foot = 24;
    // int inch = 2;

    controllers::map m(mapHeight,mapWidth);

    //4 Outer Walls
    m.addWall(0,0, wallThickness, mapHeight);
    m.addWall(0,0,mapWidth,  wallThickness);
    m.addWall(mapWidth-wallThickness, 0, wallThickness, mapHeight);
    m.addWall(0, mapHeight-wallThickness, mapWidth, wallThickness);

    //Rect A
    m.addWall(0,0, foot + 6*inch + wallThickness, 8*inch + wallThickness);
    //Rect B
    m.addWall(3*foot + 5*inch, 0, foot + 2*inch, 8*inch+wallThickness);
    //Rect D
    m.addWall(0, wallThickness + 8*inch + 10*inch, foot+10*inch+1 + 2*wallThickness, 5*inch+1);

    //Awkward wall between A and B
    m.addWall(foot + 6*inch + wallThickness + 10*inch, 0, wallThickness, 8*inch + wallThickness);
    //Vertcal wall to the right of F
    m.addWall(2 * foot, mapHeight - (11*inch + 1), wallThickness, 11*inch+1);
    //Horizontal wall above that wall
    m.addWall(2*foot - (foot - wallThickness), mapHeight-(11*inch + 1 + wallThickness), foot, wallThickness);
    //Short wall up and left from start
    m.addWall(2*foot + wallThickness + 10*inch, mapHeight-(11*inch + 1 + wallThickness), 7*inch + 1, wallThickness);
    //Long horizontal wall of T above start
    m.addWall(foot + 10*inch + 1 + wallThickness + 10*inch, wallThickness+8*inch + 10*inch, 2*foot + 1*inch, wallThickness);
    //Short vertical wall of T above start
    m.addWall(foot + 10*inch + 1 + wallThickness + 10*inch + foot + wallThickness, wallThickness+8*inch + 10*inch + wallThickness, wallThickness, 5*inch);

    m.reflectOnYAxis();

    //print for debugging map
    //m.print();
}
}
