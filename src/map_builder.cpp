using namespace std;

#include "map/map.h"

int main ()
{
    Map m = Map();

    m.addWall(0, 0, 40, 3);

    m.print();

    return 0;
}