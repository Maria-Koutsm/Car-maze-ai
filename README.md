For the representation of the problem, the following structures were used:  
Struct for the representation of cars with fields:  int x, y which are the coordinates for determining the car's position on the grid.  
                                                    char dir for determining its direction, ‘V’ for vertical orientation and ‘H’ for horizontal.  
vector for the representation of the set of cars.  
an array (obstacles[][]) with the size of the grid's dimensions for the representation of static obstacles.

METHODS
void setObstacle(int x,int y,bool value) for placing obstacles on the grid where it is checked if the x,y coordinates are within the bounds of the grid. If it is, in the specific position of the array, true is placed if there is an obstacle and false if there isn't.
void addCar(Car c) for adding a car to the cars vector.
bool isFree(int x, int y) which checks if a field on the grid is empty. Specifically, it checks if the field with coordinates x,y is outside the grid, has an obstacle, or another car. If any of the three cases is true, the method returns false; otherwise, it returns true.
CarMaze* moveNorth(int i): Initially, it calculates the new position the car will go to if the movement north can be performed. Then, it examines if the new coordinate (newy) exceeds the height of the grid. If this is true, it means the car is exiting the grid, and for this reason, a copy of the current state is created, the car is deleted from the cars vector, and finally, the new state is linked to the old one using the setPrevious method, and the action is named "EXITED". If the previous condition is not true, it is checked if the new position is empty using the isFree method (i.e., there is no obstacle or car). If it is free, the new state is created, and the car's y coordinate takes the value newy, the movement is saved in actionName (using setActionName), and the method returns the new state. If both previous moves cannot be performed, then the car cannot be moved and the function returns nullptr.
With similar logic, the methods CarMaze* moveSouth(int i), CarMaze* moveEast(int i), CarMaze* moveWest(int i) are implemented for moving the car south, east, and west respectively.
vector<CarMaze*> expand(): This method, based on the current state of the algorithm, generates all possible next moves. Specifically, it first creates a vector (children) in which it will store the pointers to the new states that will be generated. For each car, it checks if it has a vertical or horizontal orientation and accordingly checks if the respective move can be performed (i.e., if it has a vertical orientation, whether it can move north or south, and if it has a horizontal orientation, whether it can move east or west). If the move is valid, it adds it to the initial children vector. In the end, the function returns the children vector.
unsigned long getKey(): The method converts the states into a unique number in order to use it to store the already visited states in the closed set of the BFS.
bool isGoal(): Checks when the algorithm terminates, i.e., when all cars have exited the parking lot.
int getDepth(): Calculates how many moves were made until all cars exited the parking lot. This is calculated by starting from the current state and, using the prev pointer which points to the respective parent, going backwards. This iteration continues until there is no previous state.

ASSUMPTIONS
A car exits the parking lot when its coordinates are greater than the size of the grid (i.e., greater than WIDTH or HEIGHT).  

BFS IMPLEMENTATION
For the implementation of BFS, I used the queue structure to represent the search frontier and the unordered map structure for the closed set. Initially, I put the initial state in the queue. As long as the queue is not empty, it takes the first state and checks if it belongs to the closed set. If this check is true, it checks if the goal has been achieved in order to return the solution. If it has not been achieved, I add the current state to the closed set and through expand() I find all possible next moves. Finally, I check if the new states, i.e., the children, belong to the closed set so that if they don't, I can add them to the queue.  
STATISTICS  
Simple case
I make the grid 4x3,  I have 3 obstacles [(2,0),(0,1),(3,2)] and 3 cars: 2 with horizontal orientation [(1,1),(2,2)] and 1 with vertical [(2,1)].
I observe that the solution is found very quickly in 0.001 sec and little memory is used. Also, the states the algorithm visits until it finds the solution are few. 
Medium complexity case
I make the grid 6x6, I have 4 obstacles [(0,0),(5,5),(5,0),(0,5)] and 9 cars: 4 with horizontal orientation [(1,1),(3,4),(1,3),(4,3)] and 5 with vertical [(1,2),(4,2),(2,1),(3,1),(2,4)].
I observe that increasing the dimensions of the grid, the number of cars by 6, and the addition of one more obstacle made the problem more complex, resulting in it needing about 1.5 minutes to be solved and much more memory compared to the simple case. Also, the states the algorithm visited increased.
High complexity
To the medium complexity problem, I added 3 more obstacles (1,4),(2,5),(3,0) and two cars, one vertical at point (4,4) and one with horizontal orientation at point (2,3).
I observe that the addition of more obstacles and cars makes the problem even more complex, resulting in it needing more time and memory. Also, the states visited by the program were almost double compared to the medium complexity problem.
