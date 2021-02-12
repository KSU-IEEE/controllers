/////////////////////////////////////////////////////////////////////////
///---------- Controller for KSU IEEE 2021 Pacman Robot---------------///
/////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <iostream>
#include <vector>
#include <queue>
#include "node/a_star_node.h"

namespace a_star{

	//std::priority_queue<a_star::a_star_node, std::vector<a_star::a_star_node>, a_star::a_star_node_compare> paths;

	bool goal_check(int currLocROW, int currLocCOL, int goalROW, int goalCOL){
		if((currLocROW == goalROW) && (currLocCOL == goalCOL))
			return true;
		else
			return false;
	}

	//TODO_IMPLEMENT CHECKING IF ADDED LOCATION IS ALREADY IN THE PRIORITY QUEUE
	bool repeat_loc_check(){
		return false;
	}

	//TODO ADD IN THE MAP TO CHECK IF SPOT IS FREE
	bool empty_loc_check(coord Position)
	{
		return true;
	}

	//Adds one new node for each of the directions that can be moved in
	void add_nearby_nodes(a_star_node node, std::priority_queue<a_star_node> paths)
	{
		for (int i = 0; i < 4; i++)
		{
			direction dir = static_cast<direction>(i);
			a_star_node new_node(&node, dir);
			paths.push(new_node);
		}
	}

	//Main function to be called externally
	//WILL ADD SOMETHING TO DECIDE WHAT MAP TO USE LATER
	void a_star(int initialROW, int initialCOL, direction initialDirection, int goalROW, int goalCOL)
	{
		std::priority_queue<a_star::a_star_node, std::vector<a_star::a_star_node>, a_star::a_star_node_compare> paths;

		//Empty priority queue
		while(!paths.empty())
			paths.pop();

		//Create first node and add it to the queue
		coord startLocation = {initialROW, initialCOL};
		coord goal = {goalROW, goalCOL};
		a_star_node init_node(startLocation, initialDirection, goal);



	}
}

namespace Controller{
	class A_Star{
		//controller thing
		void path_plan(float Parameter, bool LocROW, bool LocCOL){
		}
	};
}

	int main()
	{
		a_star::coord startLocation = {96,84};
		a_star::direction startDirection = a_star::north;
		a_star::coord destination = {190, 22};

		a_star::a_star_node init_node(startLocation, startDirection, destination);
		
		std::cout << init_node.getX() << std::endl;
		std::cout << init_node.getH() << std::endl;

		a_star::a_star_node next_node(&init_node, a_star::west);
		std::cout << next_node.getX() << std::endl;
		std::cout << next_node.getH() << std::endl;

		a_star::coord fetchedPosition = next_node.getParent() -> getPosition();
		std:: cout << fetchedPosition.x << " , " << fetchedPosition.y << std::endl;
	}