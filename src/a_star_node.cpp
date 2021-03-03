#include "node/a_star_node.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace a_star;

//Not copy constructor: asssume starting process: distance_to_here is  0
a_star_node::a_star_node(coord initial_position, direction direction, coord destination)
{
    distance_to_here = 0;
    parent_ = NULL;
    position = initial_position;
    dir = direction;
    goal = destination;
    dist_to_goal = getEuclidDist();
    moves = "";
}

a_star_node::a_star_node(a_star_node parent, direction direction)
{
    parent_ = &parent;

    //Fetches parent's position & distance traveled, modifies them based on direction moved
    //Distance increases by 1  if going cardinally or root2 if going diagonally.
    position = parent.getPosition();
    distance_to_here = parent.getX();
    goal = parent.getGoal();
    dir = direction;

    position = getMove(position, direction);
    distance_to_here++;

    char thisMove = 'F';
    
    switch (direction)
    {
        case north: 
            thisMove = 'N'; break;
        case east: thisMove = 'E'; break;
        case south: thisMove = 'S'; break;
        case west: thisMove = 'W'; break;
    }
    moves = (parent.getMoves()) + thisMove;

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

}

int a_star_node::getManhattanDist()
{
    return abs(position.x - goal.x) + abs(position.y - goal.y);
}

double a_star_node::getEuclidDist()
{
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

 const a_star_node* const a_star_node::getParent() const
{
    return parent_;
}

direction a_star_node::getDirection() const
{
    return dir;
}

std::string a_star_node::getMoves() const{

    return moves.substr(0, moves.size());
}


//Returns a set of coordinates that have moved 1-2 squares in the indicated direction from the first set of coordinates
coord a_star_node::getMove(coord startLocation, direction dir)
{

    coord position = startLocation;
    switch(dir)
    {
        case north: position.y--; break;
        case west: position.x++;  break;
        case south: position.y++;  break;
        case east: position.x--;  break;
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
        moves = other.moves;

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

