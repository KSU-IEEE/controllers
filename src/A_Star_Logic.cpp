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

	bool goal_check(a_star_node node){
		coord goal = node.getGoal();
		coord position = node.getPosition();

		return (goal.x == position.x && goal.y == position.y);
	}

	//TODO_IMPLEMENT CHECKING IF ADDED LOCATION IS ALREADY IN THE PRIORITY QUEUE
	//Returns true if unique, false if repeated
	//Aw fucc, priority_queue doesn't let you iterate through its members.
	//Instead, we're keeping track of things already visited in another way
	//Thinking about it though, the priority queue nature itself should limit the creation of redundant nodes;
	//Moving to a previously visited space elongates the path, and therefore increases h(x) for which a better node must exist
	bool unique_loc_check(coord newLocation, std::vector<coord> *traversed_locations){

		for (std::vector<coord>::iterator it = traversed_locations -> begin(); it < traversed_locations -> end(); it++)
		{
			if (it -> x == newLocation.x && it -> y == newLocation.y)
				return false;
		}
		return true;
	}

	//TODO ADD IN THE MAP TO CHECK IF SPOT IS FREE
	bool empty_loc_check(coord location)
	{
		//Still commented out while map still in flux
		//coord newLocation = node.getPosition();
		//return !map[newLocation.x][newLocation.y];
		return true;
	}

	//Adds one new node for each of the directions that can be moved in
	void add_nearby_nodes(a_star_node node, std::priority_queue<a_star::a_star_node, std::vector<a_star::a_star_node>, a_star::a_star_node_compare> *paths, std::vector<coord> traversed_locations)
	{
		std::cout << "Adding moves from " << node.getPosition().x << "," << node.getPosition().y << std::endl;

		std::vector<a_star_node> nodes_to_push;

		for (int i = 0; i < 4; i++)
		{
			//Turns i into one of the 4 cardinal directions.
			direction dir = static_cast<direction>(i);
			coord newLocation = a_star_node::getMove(node.getPosition(), dir);

			//Make sure place we're attempting to add new node is empty
			if (empty_loc_check(newLocation))
			{
				//Make sure location of new node isn't already in tree. If it is, eliminate one with longer path to current square
			
				a_star_node new_node(&node, dir);
				if (!unique_loc_check(newLocation, &traversed_locations))
					continue;
				traversed_locations.push_back(newLocation);
				nodes_to_push.push_back(new_node);
				std::cout << "Added " << newLocation.x << "," << newLocation.y << std::endl;
				std::cout << "getX() " << (new_node.getX()) << std::endl;
				std::cout << "getH() " << (new_node.getH()) << std::endl;
				std::cout << "getAStar() " << (new_node.getAStar()) << std::endl;
				
			}
		}

		paths -> pop();
		for (std::vector<a_star_node>::iterator it = nodes_to_push.begin(); it < nodes_to_push.end(); it++)
			paths -> push(*it);
	}

	//Main function to be called externally
	//Can either use an a_star_node or initial positions, direction, and goal for flashiness.
	void a_star(a_star_node init_node)
	{
		std::priority_queue<a_star::a_star_node, std::vector<a_star::a_star_node>, a_star::a_star_node_compare> paths;

		//Empty priority queue
		while(!paths.empty())
			paths.pop();

		paths.push(init_node);

		std::vector<coord> traversed_locations;

		const a_star_node *next_node = &(paths.top());
		traversed_locations.push_back(next_node -> getPosition());
		

		std::cout << "Goal check is " << goal_check(*next_node) << std::endl;
		std::cout << "Paths size : " << paths.size() << std::endl;
		int iterations = 0;
		int maxIterations = 500;
		while (iterations < maxIterations)
		{	
			next_node = &(paths.top());
		
			if (goal_check(*next_node))
			{
				std::cout <<"Weeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee" << std::endl;
				break;
			}
				
			
			add_nearby_nodes(*next_node, &paths, traversed_locations);


			std::cout << next_node -> getPosition().x << "," << next_node -> getPosition().y << std::endl;
			std::cout << "Paths size : " << paths.size() << std::endl <<std::endl;
			iterations++;
		}
		if (iterations >= maxIterations)
			std::cout << "Pathfinding failed" << std::endl;
	}

	//Main function to be called externally
	//WILL ADD SOMETHING TO DECIDE WHAT MAP TO USE LATER
	void a_star(int initialROW, int initialCOL, direction initialDirection, int goalROW, int goalCOL)
	{
		//Creates first node, and add it to the queue
		coord startLocation = {initialROW, initialCOL};
		coord goal = {goalROW, goalCOL};
		a_star_node init_node(startLocation, initialDirection, goal);

		a_star(init_node);
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

		a_star::a_star(init_node);
	}