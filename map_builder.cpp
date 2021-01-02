using namespace std;

#include "Map.h"
#include "Map.cpp"

int main ()
{
    Map m = Map();

    m.addWall(0, 0, 40, 3);

    m.print();

    return 0;
}