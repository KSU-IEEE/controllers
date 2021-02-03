#ifndef MAP_H
#define MAP_H

namespace controllers {
class Map
{
private:
    //Internal Boolean representation
    //Each boolean covers a 1/2 inch by 1/2 inch area
    //8' * 12 * 2 by 4 * 12 * 2
    //False means no wall, True means wall
    bool map[96][192];

    //Adding these because I can't be bothered to understand sizeof
    //ints for width and height of the map array
    int rows;
    int cols;

public:
    Map();

    //Copy Constructor for making another from the same boolean array
    Map(Map &m);    

    void addWall(int x, int y, int width, int height);
    void print();
    void reflectOnYAxis();

    //Returns pointer to an array of length 4 of booleans.
    //Up, Right, Down, Left
    bool * getAdjacentSquares(int x, int y);

};
} // namespace controllers
#endif