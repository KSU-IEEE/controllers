using namespace std;

#include "mapping/map.h"
int main ()
{
    controllers::Map m = controllers::Map();

    m.addWall(0, 0, 40, 3);

    m.print();

    return 0;
}