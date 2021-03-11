///////////////////////////////////////////////////
//  VECTOR INCLUDED SO CMAKE WILL STOP YELLING AT ME
//  COMMENT OUT FOR FULL RUN    ///////////////////
#include <vector>
///////////////////////////////////////////////////
#ifndef MAP_H
#define MAP_H


namespace controllers {

class map
{
private:
    //Internal Boolean representation
    //Each boolean covers a 1/2 inch by 1/2 inch area
    //8' * 12 * 2 by 4 * 12 * 2
    //False means no wall, True means wall
    
    //variable size vectors to create a map
    //you load a row vector into another vector to creat columns
    std::vector<bool> VRowMap;
    std::vector<std::vector<bool>> Vmap;

    //Adding these because I can't be bothered to understand sizeof
    //ints for width and height of the map array
    int rows;
    int cols;
    int wallThickness;
    int robotSize;

public:
    //default constructor
    //uses array style for pac man style competition for Southeastcon 2021
    map();

    //contructor for vector based map
    //changebale rows and cols
    map(int rows, int cols);

    //Copy Constructor for making another from the same boolean array
    map(map &m); 

    //setters for vars
    void setWallThickness(int thicc){ wallThickness = thicc; };
    void setRobotSize(int SetRobotSize){ robotSize = SetRobotSize;};    
    void setVmapRow(int rowSET){ rows = rowSET; };   
    void setVmapCols(int colSET){ cols = colSET; };

    //getters for vars
    int getWallThickness(){ return wallThickness; };
    int getRobotSize(){ return robotSize; };    
    int getVmapRow(){ return rows; };   
    int getVmapCols(){ return cols; };

    //function to add walls to the boolean map
    void addWall(int x, int y, int width, int height);
    //print out map to terminal
    void print(std::vector<std::pair<int, int>> *path_points = NULL);

    //reflects the map across y axis
    //map is symentrical so this is faster for generating it
    void reflectOnYAxis();

    //Returns pointer to an array of length 4 of booleans.
    //Up, Right, Down, Left
    bool * PgetAdjacentSquares(int x, int y);

    //Returns presence of wall at coordinates x, y
    bool isWall(int x, int y);

};
} // namespace controllers
#endif