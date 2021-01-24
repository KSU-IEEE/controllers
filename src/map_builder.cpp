using namespace std;

#include "mapping/map.h"
int main ()
{
    controllers::Map m = controllers::Map();

    m.addWall(0, 0, 6, 30);
    m.addWall(0,0,4*12*2, 3);

    m.print();

    return 0;
}