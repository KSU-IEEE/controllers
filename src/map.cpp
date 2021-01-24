using namespace std;
#include <iostream>
#include <cmath>
#include "mapping/map.h"
// #include "../include/mapping/map.h"

namespace controllers {
//Each boolean covers a 1/2 inch by 1/2 inch area
//8' * 12 * 2 by 4 * 12 * 2
Map::Map()
{
    // map =new bool[96][192];
    rows = 96;
    cols = 192;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            map[i][j] = false;
}

//Sets every bool in described area to true, for wall
void Map::addWall(int x, int y, int width, int height)
{
    for (int i = x; i-x < height; i++)
    {
        for (int j = y; j-y < width; j++)
            {
                // if (i >= sizeof(map) || j >= sizeof(map[]))
                //     cout << "Array out of bounds"; << endl;
                

                map[j][i] = true;
                cout << "i: " << i << " j: " << j << endl;
            }
    }
}

void Map::print()
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // cout << "i" << i << "j" << j << "-";
            cout << map[i][j];
            // cout << " ";

        }
        cout << " row" << i << endl;
    }
}
} // namespace controllers