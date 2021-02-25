/////////////////////////////////////////////////////////////////////////
///---------- Controller for KSU IEEE 2021 Pacman Robot---------------///
/////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
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

		//Put first node into the priority queue
		paths.push(init_node);

		std::vector<coord> traversed_locations;

		//Constant pointer to current best node in the priority queue.
		//Best node will change as more are added
		const a_star_node *next_node = &(paths.top());
		traversed_locations.push_back(next_node -> getPosition());
	
		//Keep track of number of iterations to avoid being stuck in infinite loop
		int iterations = 0;
		int maxIterations = 500;
		while (iterations < maxIterations)
		{	
			next_node = &(paths.top());
		
			//Check if we have found the goal
			if (goal_check(*next_node))
			{
				std::cout <<"Weeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee" << std::endl;
				break;
			}
			
			add_nearby_nodes(*next_node, &paths, traversed_locations);
			iterations++;
		}
		if (iterations >= maxIterations)
			std::cout << "Pathfinding failed" << std::endl;
		else
		{
			std::cout << "Goal found at " << next_node -> getPosition().x << "," << next_node -> getPosition().y << std::endl;
			// int string_index = 0;
			// for (const a_star_node *ptr = next_node; ptr != NULL; ptr = ptr -> getParent())
			// {
			// 	direction dir = ptr -> getDirection();
			// 	char stepChar;
			// 	switch (dir)
			// 	{
			// 		case north: stepChar = 'N'; break;
			// 		case west: stepChar = 'W'; break;
			// 		case south: stepChar = 'S'; break;
			// 		case east: stepChar = 'E'; break;
			// 		default: stepChar = 'X'; break;
			// 	}

			// 	steps[string_index] = stepChar;
			// 	string_index++;
			// }
			// steps[string_index] = '\0';

			std::cout << next_node -> getParent() -> getPosition().x <<"," << std::endl;
			std::cout << next_node -> getMoves() << std::endl;
		}
	}

	//Overload of main external method with different inputs
	//Prepares a node to be used by the main method
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
		
		std::cout << "Initial Position : " << init_node.getPosition().x << "," << init_node.getPosition().y << std::endl;
		std::cout << "Destination : " << init_node.getGoal().x << "," << init_node.getGoal().y << std::endl;

		a_star::a_star(init_node);
	}