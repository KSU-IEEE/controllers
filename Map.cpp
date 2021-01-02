
using namespace std;
#include <iostream>
#include "Map.h"


//Each boolean covers a 1/2 inch by 1/2 inch area
//8' * 12 * 2 by 4 * 12 * 2
Map::Map()
{
    map = new bool[192][96];
    rows = 192;
    cols = 96;
}

//Sets every bool in described area to true, for wall
void Map::addWall(int x, int y, int width, int height)
{
    for (int i = x; i-x < width; i++)
        for (int j = y; j-y < height; j++)
            {
                // if (i >= sizeof(map) || j >= sizeof(map[]))
                //     cout << "Array out of bounds"; << endl;

                map[&i][&j] = true;
            }
}

void Map::print()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            {
                cout << map[&i][&j];
            }
}