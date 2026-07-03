#include "CarMaze.h"
#include <algorithm>

CarMaze::CarMaze() {
    for (int i = 0;i<WIDTH; i++)
        for (int j=0; j<HEIGHT; j++)
            obstacles[i][j]=false;
    setPrevious(nullptr);
    actionName="";
}
CarMaze::CarMaze(const CarMaze& other) {
    cars=other.cars;
    for (int i=0;i<WIDTH;i++)
        for (int j=0; j<HEIGHT;j++)
            obstacles[i][j]=other.obstacles[i][j];
    setPrevious(nullptr);
    actionName="";
}
void CarMaze::setObstacle(int x, int y, bool value) {
   if (x >= 0&& x<WIDTH &&y>= 0&&y <HEIGHT) {
        obstacles[x][y]=value;
    }
}

void CarMaze::addCar(Car c) {
    cars.push_back(c);
}

bool CarMaze::isFree(int x, int y){
    if (x<0 || x>= WIDTH || y<0 || y>=HEIGHT)
        return false;
    if (obstacles[x][y])
        return false;
    for (int i=0;i<cars.size();i++) {
        if (cars[i].x==x&& cars[i].y==y) {
            return false;
        }
    }
    return true;
}
CarMaze* CarMaze::moveNorth(int i) {
    int newx=cars[i].x;
    int newy=cars[i].y+1;
    if (newy >= HEIGHT){
        CarMaze* next=new CarMaze(*this);
        next->cars.erase(next->cars.begin()+i);
        next->setPrevious(this);
        next->setActionName("EXITED");
        return next;
    }
    if (isFree(newx, newy)) {
        CarMaze* next=new CarMaze(*this);
        next->cars[i].y=newy;
        next->setPrevious(this);
        next->setActionName("North");
        return next;
    }
    return nullptr;
}

CarMaze* CarMaze::moveSouth(int i) {
    int newx=cars[i].x;
    int newy=cars[i].y-1;
    if (newy<0){
        CarMaze* next=new CarMaze(*this);
        next->cars.erase(next->cars.begin()+i);
        next->setPrevious(this);
        next->setActionName("EXITED");
        return next;
    }
    if (isFree(newx,newy)) {
        CarMaze* next=new CarMaze(*this);
        next->cars[i].y=newy;
        next->setPrevious(this);
        next->setActionName("South");
        return next;
    }
    return nullptr;
}

CarMaze* CarMaze::moveEast(int i) {
    int newx=cars[i].x + 1;
    int newy=cars[i].y;
    if (newx>=WIDTH){
        CarMaze* next = new CarMaze(*this);
        next->cars.erase(next->cars.begin() + i);
        next->setPrevious(this);
        next->setActionName("EXITED");
        return next;
    }
    if (isFree(newx,newy)){
        CarMaze* next= new CarMaze(*this);
        next->cars[i].x=newx;
        next->setPrevious(this);
        next->setActionName("East");
        return next;
    }
    return nullptr;
}

CarMaze* CarMaze::moveWest(int i) {
    int newx=cars[i].x-1;
    int newy=cars[i].y;
    if (newx < 0){
        CarMaze* next=new CarMaze(*this);
        next->cars.erase(next->cars.begin() + i);
        next->setPrevious(this);
        next->setActionName("EXITED");
        return next;
    }
    if (isFree(newx,newy)) {
        CarMaze* next=new CarMaze(*this);
        next->cars[i].x=newx;
        next->setPrevious(this);
        next->setActionName("West");
        return next;
    }
    return nullptr;
}

vector<CarMaze*> CarMaze::expand() {
    vector<CarMaze*> children;
    for (int i=0;i<cars.size();i++) {
        CarMaze* child=nullptr;
        if (cars[i].dir=='V') {
            if ((child=moveNorth(i)))
                children.push_back(child);
            if ((child= moveSouth(i)))
                children.push_back(child);
        } else {
            if ((child=moveEast(i)))
                children.push_back(child);
            if ((child= moveWest(i)))
             children.push_back(child);
        }
    }
    return children;
}

unsigned long CarMaze::getKey() {
    unsigned long k=0;
    unsigned long m=1;
    for (int i=0;i<cars.size();i++) {
        int pos=cars[i].y*WIDTH+cars[i].x;
        k=k+(pos*m);
        m=m*100;
    }
    return k;
}

bool CarMaze::isGoal() {
    return cars.empty();
}

int CarMaze::getDepth() {
    int count=0;
    CarMaze* car =this;
    while (car->prev) {
        count++;
        car =car->prev;
    }
    return count;
}



