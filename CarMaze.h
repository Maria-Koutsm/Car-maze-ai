#ifndef CARMAZE_H
#define CARMAZE_H
#define WIDTH 4
#define HEIGHT 3
#include <vector>
#include <string>
using namespace std;

struct Car{
    int x,y;
    char dir;//'V' για κάθετο προσανατολισμό και 'H' για οριζόντιο προσανατολισμό
};

class CarMaze{
public:
    CarMaze();
    CarMaze(const CarMaze& other);
    void setObstacle(int x,int y,bool value);
    void addCar(Car c);
    CarMaze* moveNorth(int i);
    CarMaze* moveSouth(int i);
    CarMaze* moveEast(int i);
    CarMaze* moveWest(int i);
    unsigned long getKey();
    bool isFree(int x, int y);
    bool isGoal();
    int getDepth();
    vector<CarMaze*> expand();
    void setPrevious(CarMaze* p){prev=p;}
    CarMaze* getPrevious(){return prev;}
    void setActionName(string s){actionName=s;}
    string getActionName(){return actionName;}
private:
    vector<Car> cars;
    bool obstacles[WIDTH][HEIGHT];
    CarMaze* prev;
    string actionName;
};

#endif
