//using namespace std;
#include <iostream>
#include <cmath>
#include "mapping/map.h"
#include <vector>
// #include "../include/mapping/map.h"

namespace controllers {
//Each boolean covers a 1/2 inch by 1/2 inch area
//8' * 12 * 2 by 4 * 12 * 2
map::map(){
    // Map map = new bool[96][192];
    // rows = 96;
    // cols = 192;

    // for (int i = 0; i < rows; i++)
    //     for (int j = 0; j < cols; j++)
    //         map[i][j] = false;
    
}

map::map(int CONSTR_rows, int CONSTR_cols)
{

    //should generate the real space
    //ie the map in real life scale
    rows = CONSTR_rows;
    cols = CONSTR_cols;
    //set map vector for row to 1 so pushback will work
    VRowMap.resize(1);
    
    //load a row vector with false
    // Vmap.at(index).push_back(value);
        for (int i = 0; i < rows; i++){
            VRowMap.push_back(false);
            //load the row vector into columns
            // 1 2 3 4 5 -> load -> 1 2 3 4 5
            //                      0 0 0 0 0
            for (int j = 0; j < cols; j++)
                Vmap.push_back(VRowMap);
        }
}    

//setters -> implement later
// void setVmapRow(int rowSET)
// {
//         Map::rows = rowSET;
// }

// void setVmapCols(int colSET)
// {
//         cols = colSET;
// }

map::map(map &m)
{
    map();

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            Vmap[i][j] = m.Vmap[i][j];
}


//Sets every bool in described area to true, for wall
void map::addWall(int x, int y, int width, int height)
{
    for (int i = x; i-x < width; i++)
    {
        //Prevent going over size of map
        if (i >= cols)
            break;

        for (int j = y; j-y < height; j++)
            {
                //Prevent going over size of map
                if (j >= rows)
                    break;
                
                Vmap[j][i] = true;
            }
    }
}

void map::print()
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // cout << "i" << i << "j" << j << "-";
            std::cout << Vmap[i][j];
            // cout << " ";

        }
        std::cout << " row" << i << std::endl;
    }
}

void map::reflectOnYAxis()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            bool reflectedSpot = Vmap[i][cols-j];
            if (reflectedSpot)
                Vmap[i][j] = true;
        }
    }
}

bool map::isWall(int x, int y)
{
    return Vmap[x][y];
}
} // namespace controllers