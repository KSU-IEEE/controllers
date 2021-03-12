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
    VRowMap.resize(0);

    for (int col = 0; col < cols; col++)
        VRowMap.push_back(false);

    for (int row = 0; row < rows; row++)
        Vmap.push_back(VRowMap);

    std::cout << Vmap.size() << std::endl;
    std::cout << VRowMap.size() << std::endl;
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
    std::cout << "x, y, width, height: " << x << "," << y<< "," << width << "," <<height << std::endl;
    std::cout << "rows, cols: " << rows << "," << cols << std::endl;
    std::cout << "VMap size, vMapRows size: " << Vmap.size() << "," << VRowMap.size() << std::endl;
    for (int i = x; i-x < width; i++)
    {

        //Prevent going over size of map
        if (i >= cols)
            break;

        for (int j = y; j-y < height; j++)
            {
                
                //Prevent going over size of map
                if (j >= rows)
                {
                    break;
                }
                Vmap[j][i] = true;
            }
    }
}
//Sets every bool in described area to false, for free space
void map::rmWall(int x, int y, int width, int height)
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
                
                Vmap[j][i] = false;
            }
    }
}
void map::print(std::vector<std::pair<int, int>> *path_points)
{
    //Print 2 rows showing the column numbers for my sanity
    //10's place
    for (int i = 0; i < cols; i++)
        std::cout << (i / 10) % 10;
    std::cout << std::endl;
    //1's place
    for (int i = 0; i < cols; i++)
        std::cout << i % 10;
    std::cout << std::endl;
    std::cout << std::endl;


    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            //Branching to print an X if in a path sent over.
            if (path_points == NULL)
                std::cout << Vmap[i][j];
            else
            {
                bool wasInPath = false;
                for (auto ptr : *path_points)
                {
                    if (ptr.first == i && ptr.second == j)
                    {
                        std::cout << "X";
                        wasInPath = true;
                    }
                }
                if (!wasInPath)
                    std::cout << Vmap[i][j];
            }

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