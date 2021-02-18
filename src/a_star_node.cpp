#include "node/a_star_node.h"
#include <iostream>

using namespace a_star;

//Not copy constructor: asssume starting process: distance_to_here is  0
a_star_node::a_star_node(coord initial_position, direction direction, coord destination)
{
    distance_to_here = 0;
    parent = NULL;
    position = initial_position;
    dir = direction;
    goal = destination;
    dist_to_goal = getEuclidDist();

}

a_star_node::a_star_node(a_star_node *parent, direction direction)
{
    this -> parent = parent;

    //Fetches parent's position & distance traveled, modifies them based on direction moved
    //Distance increases by 1  if going cardinally or root2 if going diagonally.
    position = parent -> getPosition();
    distance_to_here = parent -> getX();
    goal = parent -> getGoal();
    dir = direction;

    position = getMove(position, direction);
    // std::cout << "New Position " << position.x << "," <<position.y << std::endl;


    // if ((int)direction % 2 == 0)
    //     distance_to_here++;
    // else
    //     distance_to_here += root2;

    distance_to_here++;
    

    // //MAYBE WILL GET RID OF THIS
    // //Adds to distance traveled based on how much turning was done to face this direction
    // int direction_diff = abs((int)dir - (int)parent.getDirection());
    // //Absolute difference between half of all directions and size of difference
    // direction_diff = abs(4 - direction_diff);

    // distance_to_here += 0.25 * (direction_diff);
    dist_to_goal = getManhattanDist();

}

//Destructor?
a_star_node::~a_star_node()
{
    // std::cout << "Adios master" << std::endl;
    // if (parent != NULL)
    //     delete parent;
}

int a_star_node::getManhattanDist()
{
    return abs(position.x - goal.x) + abs(position.y - goal.y);
}

double a_star_node::getEuclidDist()
{
    // std::cout << "Current position: (" << position.x << "," << position.y << ")" << std::endl;
    // std::cout << "Destination: (" << goal.x << "," << goal.y << ")" << std::endl;

    return sqrt(pow(position.x-goal.x,2) + pow(position.y-goal.y,2));
}

coord a_star_node::getPosition() const
{
    // std::cout << "Current position: (" << position.x << "," << position.y << ")" << std::endl;
    return position;
}

coord a_star_node::getGoal() const
{
    // std::cout << "Destination: (" << goal.x << "," << goal.y << ")" << std::endl;
    return goal;
}

int a_star_node::getX() const
{
    return distance_to_here;
}

int a_star_node::getH() const
{
    return dist_to_goal;
}

int a_star_node::getAStar() const
{
    return getX() + getH();
}

a_star_node* a_star_node::getParent() const
{
    return parent;
}

direction a_star_node::getDirection() const
{
    return dir;
}


//Returns a set of coordinates that have moved 1-2 squares in the indicated direction from the first set of coordinates
coord a_star_node::getMove(coord startLocation, direction dir)
{

    coord position = startLocation;
    switch(dir)
    {
        case north: position.y--; break;
        //case northwest: position.y--; position.x++;  break;
        case west: position.x++;  break;
        //case southwest: position.x++; position.y++;  break;
        case south: position.y++;  break;
        //case southeast: position.y++; position.x--; break;
        case east: position.x--;  break;
        //case northeast: position.x--; break;
    }

    return position;
}

bool a_star_node::operator<(const a_star_node& other) const
{
    bool a_equals = getAStar() == other.getAStar();
    if (a_equals)
        return getH() < other.getH();
    else
        return getAStar() < other.getAStar();
}

a_star_node& a_star_node::operator=(const a_star_node& other)
{
    if (this != &other) // not a self-assignment
    {
        position = other.getPosition();
        goal = other.getGoal();
        dir = other.getDirection();
        distance_to_here = other.getX();
        dist_to_goal = getManhattanDist();

    }
    return *this;
}

int a_star_node_compare::operator()(const a_star_node &a, const a_star_node &b)
{
    //Sort first based on the AStar value, second based on H (how close they are to the goal)

    if (a.getAStar() == b.getAStar())
        return a.getH() > b.getH();
    else
        return a.getAStar() > b.getAStar();
};

