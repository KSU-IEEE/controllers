// /////////////////////////////////////////////////////////////////////////
// ///---------- Controller for KSU IEEE 2021 Pacman Robot---------------///
// /////////////////////////////////////////////////////////////////////////
// #include <math.h>
// #include <iostream>
// #include <vector>
// #include <queue>
// #include <string>
// #include "node/a_star_node.h"
// #include "mapping/map.h"
// #include "map_builder.cpp"

// namespace a_star{

// 	bool is_test = true;


// 	//std::priority_queue<a_star::a_star_node, std::vector<a_star::a_star_node>, a_star::a_star_node_compare> paths;

// 	bool goal_check(a_star_node node){
// 		coord goal = node.getGoal();
// 		coord position = node.getPosition();

// 		return (goal.x == position.x && goal.y == position.y);
// 	}

// 	//TODO_IMPLEMENT CHECKING IF ADDED LOCATION IS ALREADY IN THE PRIORITY QUEUE
// 	//Returns true if unique, false if repeated
// 	//Aw fucc, priority_queue doesn't let you iterate through its members.
// 	//Instead, we're keeping track of things already visited in another way
// 	//Thinking about it though, the priority queue nature itself should limit the creation of redundant nodes;
// 	//Moving to a previously visited space elongates the path, and therefore increases h(x) for which a better node must exist
// 	bool unique_loc_check(coord newLocation, std::vector<coord> &traversed_locations){

// 		for (auto it: traversed_locations)
// 		{
// 			if (it.x == newLocation.x && it.y == newLocation.y)
// 				return false;
// 		}
// 		return true;
// 	}

// 	//TODO ADD IN THE MAP TO CHECK IF SPOT IS FREE
// 	bool empty_loc_check(coord location, controllers::map& config_map)
// 	{
// 		//Still commented out while map still in flux
// 		//coord newLocation = node.getPosition();
// 		//return !map[newLocation.x][newLocation.y];
// 		return !config_map.isWall(location.x, location.y);
// 	}

// 	char directionToChar(direction dir)
// 	{
// 		switch (dir)
// 		{
// 			case north: return 'N';
// 			case east: return 'E';
// 			case south: return 'S';
// 			case west: return 'W';
// 			default: return 'F';
// 		}
// 	}

// 	direction charToDirection(char char_dir)
// 	{
// 		switch (char_dir)
// 		{
// 			case 'N' : return north;
// 			case 'E' : return east;
// 			case 'S' : return south;
// 			case 'W' : return west;
// 			default: return north;
// 		}
// 	}

// 	direction charToOppositeDirection(char char_dir)
// 	{
// 		direction opposite_dir = north;
// 		switch (char_dir)
// 		{
// 			case 'N': opposite_dir = south; break;
// 			case 'E': opposite_dir = west; break;
// 			case 'S': opposite_dir = north; break;
// 			case 'W': opposite_dir = east; break;
// 		}

// 		return opposite_dir;
// 	}

// 	//Helper method returns a vector of all the coordinates used in a path, given the end and the steps
// 	std::vector<std::pair<int, int>> getSpacesInPath(a_star_node end_node, std::string steps)
// 	{
// 		//Add last space
// 		std::vector<std::pair<int, int>> spaces;
// 		coord current_space = end_node.getPosition();
// 		std::pair<int, int> startingSpace(current_space.x, current_space.y);
// 		spaces.push_back(startingSpace);

// 		//Do opposite step for every step in steps string, in reverse order
// 		for (int i = steps.size() - 1; i >= 0; i--)
// 		{
// 			char step = steps[i];
// 			direction opposite_dir = charToOppositeDirection(step);
// 			current_space = a_star_node::getMove(current_space, opposite_dir);
// 			std::pair<int, int> new_pair(current_space.x, current_space.y);
// 			spaces.push_back(new_pair);

// 		}

// 		return spaces;
// 	}

// 	std::vector<float> encodeRobotMovements(std::string cardinalSteps, direction initialDir)
// 	{
// 		//Positive floats indicate number of half-inches to go
// 		//Negative floats should be whole numbers -- indicate number of 90 degree clockwise turns needed to face a new direction
// 		std:: vector<float> instructions;
// 		const float stepDistance = 0.5;

// 		char currentDir = directionToChar(initialDir);
// 		float distanceInDirection = 0.0;
// 		for (int i = 0; i < cardinalSteps.length(); i++)
// 		{

// 			//If it is another step in the same direction
// 			if (cardinalSteps[i] == currentDir)
// 			{
// 				distanceInDirection += stepDistance;
// 			}
// 			else
// 			{
// 				//Don't push empty forward move in beginning to confuse motor people
// 				if (distanceInDirection != 0.0)
// 					instructions.push_back(distanceInDirection);
// 				distanceInDirection = 0.0;

// 				//Add turn to face new direction
// 				//CODE REQUIRES DIRECTION ENUM BE IN CLOCKWISE ORDER TO WORK
// 				int current_dir_int = (int)charToDirection(currentDir);
// 				int new_dir_int = (int)charToDirection(cardinalSteps[i]);
// 				int turn = current_dir_int - new_dir_int;
// 				if (turn > 0)
// 					turn -= 4;
// 				instructions.push_back((float)turn);
// 				currentDir = cardinalSteps[i];
				
// 				distanceInDirection += stepDistance;
// 			}
// 		}
// 		instructions.push_back(distanceInDirection);

// 		return instructions;
// 	}

// 	//Adds one new node for each of the directions that can be moved in
// 	void add_nearby_nodes(a_star_node node, std::priority_queue<a_star::a_star_node, std::vector<a_star::a_star_node>, a_star::a_star_node_compare> *paths, std::vector<coord> &traversed_locations, controllers::map &config_map)
// 	{

// 		// std::cout << "Adding moves from " << node.getPosition().x << "," << node.getPosition().y << std::endl;

// 		std::vector<a_star_node> nodes_to_push;

// 		for (int i = 0; i < 4; i++)
// 		{
// 			//Turns i into one of the 4 cardinal directions.
// 			direction dir = static_cast<direction>(i);
// 			coord newLocation = a_star_node::getMove(node.getPosition(), dir);

// 			//Make sure new direction doesn't go back to where old node came from;
// 			//Does this by not going in the opposite direction as the old node
// 			//Is allowed to go backwards on the first node, i.e. when the number of steps so far is 0
// 			int oldDirInt = (int)(node.getDirection());
// 			if (abs(i - oldDirInt) % 4 == 2 && node.getMoves().length() != 0)
// 				continue;

// 			//Make sure place we're attempting to add new node is empty
// 			if (empty_loc_check(newLocation, config_map))
// 			{
// 				a_star_node new_node(node, dir);

// 				//Make sure place we're going to has not been gone to before
// 				if (!unique_loc_check(newLocation, traversed_locations))
// 					continue;
// 				traversed_locations.push_back(newLocation);
// 				nodes_to_push.push_back(new_node);
// 			}
// 			else{
// 				//std::cout << "You bad lad!";
// 				;
// 			}
// 		}

// 		paths -> pop();
// 		for (a_star_node i : nodes_to_push)
// 			paths -> push(i);
// 	}

// 	//Main function to be called externally
// 	//Can either use an a_star_node or initial positions, direction, and goal for flashiness.
// 	void a_star(a_star_node init_node, controllers::map &config_map)
// 	{
// 		std::priority_queue<a_star::a_star_node, std::vector<a_star::a_star_node>, a_star::a_star_node_compare> paths;

// 		//Empty priority queue
// 		while(!paths.empty())
// 			paths.pop();

// 		//Ensure neither initial node nor destination are a wall
// 		if (!empty_loc_check(init_node.getPosition(), config_map))
// 		{
// 			std::cout << "Invalid! Initial position is a wall" << std:: endl;
// 			return;
// 		}
// 		else if (!empty_loc_check(init_node.getGoal(), config_map))
// 		{
// 			std::cout << "Invalid! Destination is a wall" << std:: endl;
// 			return;
// 		}

// 		direction initialDirection = init_node.getDirection();
// 		//Put first node into the priority queue
// 		paths.push(init_node);
// 		std::vector<coord> traversed_locations;

// 		//Constant pointer to current best node in the priority queue.
// 		//Best node will change as more are added
// 		const a_star_node *next_node = &(paths.top());
// 		traversed_locations.push_back(next_node -> getPosition());
	
// 		//Keep track of number of iterations to avoid being stuck in infinite loop
// 		int iterations = 0;
// 		int maxIterations = 5000;
// 		while (iterations < maxIterations)
// 		{
// 			if (paths.size() == 0)
// 			{
// 				std::cout << "Pathfinding failed due to running out of frontier nodes" << std::endl;
// 				return;
// 			}

// 			next_node = &(paths.top());
// 			a_star_node current_node = paths.top();
		
// 			//Check if we have found the goal
// 			if (goal_check(*next_node))
// 			{
// 				break;
// 			}
			
// 			add_nearby_nodes(current_node, &paths, traversed_locations, config_map);

// 			//std::cout << "Checking at: (" << current_node.getPosition().x << "," << current_node.getPosition().y << ")" << std::endl;

// 			iterations++;
// 		}
// 		if (iterations >= maxIterations)
// 			std::cout << "Pathfinding failed due to too many iterations" << std::endl;
// 		else
// 		{
// 			if (is_test)
// 			{
// 				std::cout << "Goal found at " << next_node -> getPosition().x << "," << next_node -> getPosition().y << std::endl;
// 				std::vector<std::pair<int,int>> path_points = getSpacesInPath(*next_node, next_node -> getMoves());	
// 				config_map.print(&path_points);
// 				std::cout << next_node -> getMoves() << std::endl;
				
// 			}

// 			std::vector<float> instructions = encodeRobotMovements(next_node -> getMoves(), initialDirection);
// 			for (auto it: instructions)
// 				std::cout << it << ",";
// 			std::cout << std::endl;
// 		}
// 	}

// 	//Overload of main external method with different inputs
// 	//Prepares a node to be used by the main method
// 	void a_star(int initialROW, int initialCOL, direction initialDirection, int goalROW, int goalCOL, controllers::map& config_map)
// 	{
// 		//Creates first node, and add it to the queue
// 		coord startLocation = {initialROW, initialCOL};
// 		coord goal = {goalROW, goalCOL};
// 		a_star_node init_node(startLocation, initialDirection, goal);

// 		//Calls real main method using arguments put together
// 		a_star(init_node, config_map);
// 	}

	
// }
 // the real start
 #include <node/a_star_node.h>
//  #include <iostream>
//  #include <mapping/map.h>
//  #include <mapping/map_builder.h>
 #include <node/a_star_logic.h>

int main()
{
	// a_star::coord startLocation = {50, 23};
	// a_star::direction startDirection = a_star::north;
	// a_star::coord destination = {100, 23};

	// a_star::a_star_node init_node(startLocation, startDirection, destination);
	
	// std::cout << "Initial Position : " << init_node.getPosition().x << "," << init_node.getPosition().y << std::endl;
	// std::cout << "Destination : " << init_node.getGoal().x << "," << init_node.getGoal().y << std::endl;

	// controllers::map test_map(96, 192);
	// map_builder::build_real_space_map(3, 96, 192, test_map);
	// test_map.print();

	// std::cout << "Passed to real space builder" << std::endl;

	// // a_star::a_star(init_node, test_map);
	// a_star::a_star(50, 23, startDirection, 100, 28, test_map);
}
