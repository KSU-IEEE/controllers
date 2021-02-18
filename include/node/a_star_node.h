#include <cstdlib>
#include <math.h>

namespace a_star{
  //Creates a coordinate type that can be asked for x and y
	typedef struct{int x; int y;} coord;

  //Enum for 8 directions: 4 cardinal. Gives better readability.
  enum direction {north, east, south, west};

	//a_star_node stuff placeholder for queue and trees
	class a_star_node{

    private:
		    coord position;
        coord goal;
        direction dir;

		    int distance_to_here;
        int dist_to_goal;
        

		    a_star_node *parent;

        int getManhattanDist();
        double getEuclidDist();

        const double root2 = 1.41421;

    public:
        //Constructor && Copy Constructor
		    a_star_node(coord initial_position, direction direction, coord destination);
        a_star_node(a_star_node *parent, direction direction);
        ~a_star_node();

        //Returns reference to a_star_node before this one (null if first)
        a_star_node* getParent() const;

        //Construct all a_star_nodes near this point
        void exploreChildren();

        coord getPosition() const;
        coord getGoal() const;
        direction getDirection() const;

        int getX() const;
        int getH() const;
        int getAStar() const;

        //Bool operator to make the class comparable, and usable in a priority queue
        // bool operator () (const a_star_node& a, const a_star_node& b) const;

        static coord getMove(coord startLocation, direction dir);

        a_star_node& operator=(const a_star_node& other);
        bool operator<(const a_star_node& other) const;
	};

  class a_star_node_compare{
      public:
          int operator()(const a_star_node &a, const a_star_node &b);
  };
}