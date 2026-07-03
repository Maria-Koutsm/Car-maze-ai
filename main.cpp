#include <iostream>
#include <queue>
#include <unordered_map>
#include <ctime>
#include "CarMaze.h"

CarMaze* BFS(CarMaze* initial, long long &examined, long long &mem){
    queue<CarMaze*> agenda;
    unordered_map<unsigned long, bool> closed;
    agenda.push(initial);
    examined=0;
    mem=1;
    while(agenda.size()>0) {
        if(agenda.size()+ closed.size()>mem) {
            mem =agenda.size()+closed.size();
        }
        CarMaze* s= agenda.front();
        agenda.pop();
        if (closed.count(s->getKey())==0) {
            examined++;
            if (s->isGoal()){
                return s;
            }
            pair<unsigned long, CarMaze*>k (s->getKey(),s);
            closed.insert(k);
            vector<CarMaze*> children=s->expand();
            for(unsigned int i=0;i<children.size();i++)
                if(closed.count(children[i]->getKey())==0)
                    agenda.push(children[i]);
        }
    }
    return nullptr;
}

int main() {
    CarMaze* initial=new CarMaze();
    // Απλή περίπτωση WIDTH 4 HEIGHT 3

    initial->setObstacle(2,0,true);
    initial->setObstacle(0,1,true);
    initial->setObstacle(3,2,true);
    initial->addCar({1,1,'H'});
    initial->addCar({2,1,'V'});
    initial->addCar({2,2,'H'});

    //Μέτριας πολυπλοκότητας κανω στο αρχείο CarMaze.h WIDTH 6, HEIGHT 6
    /*
    initial->setObstacle(0,0,true);
    initial->setObstacle(5,5,true);
    initial->setObstacle(5,0,true);
    initial->setObstacle(0,5,true);
    initial->addCar({1,1,'H'});
    initial->addCar({1,2,'V'});
    initial->addCar({4,2,'V'});
    initial->addCar({2,1,'V'});
    initial->addCar({3,1,'V'});
    initial->addCar({2,4,'V'});
    initial->addCar({3,4,'H'});
    initial->addCar({1,3,'H'});
    initial->addCar({4,3,'H'});
    */
    //Υψηλης πολυπλοκότητας κάνω στο αρχείο CarMaze.h WIDTH 6, HEIGHT 6
    /*
    initial->setObstacle(0,0,true);
    initial->setObstacle(5,5,true);
    initial->setObstacle(5,0,true);
    initial->setObstacle(0,5,true);
    initial->setObstacle(1,4,true);
    initial->setObstacle(2,5,true);
    initial->setObstacle(3,0,true);
    initial->addCar({1,1,'H'});
    initial->addCar({1,2,'V'});
    initial->addCar({4,2,'V'});
    initial->addCar({2,1,'V'});
    initial->addCar({3,1,'V'});
    initial->addCar({2,4,'V'});
    initial->addCar({4,4,'V'});
    initial->addCar({2,3,'H'});
    initial->addCar({3,4,'H'});
    initial->addCar({1,3,'H'});
    initial->addCar({4,3,'H'});
    */
    long long examined=0;
    long long mem=0;
    clock_t start=clock();
    CarMaze* solution=BFS(initial,examined,mem);
    clock_t end=clock();
    double duration=(double)(end-start)/CLOCKS_PER_SEC;
    if (solution){
         cout<<"depth = "<<solution->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<", Time: "<<duration<<"sec"<<endl;
    } else {
        cout<<"Problem unsolvable"<<endl;
    }
    return 0;
}
