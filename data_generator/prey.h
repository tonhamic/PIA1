#ifndef PREY_H
#define PREY_H

#include <string>
#include <fstream>
#include <vector>
#include "animal.h"
#include "predator.h"
#include "settings.h"

using namespace std;
class predator;
class  prey : public animal {
public:
prey(double startX, double startY);
void run(std::vector<predator> enemies);
void update(std::vector<prey>& others);
double getX() const { return x; };
double getY() const { return y; };
double getVX() const { return vx; };
double getVY() const { return vy; };
int getAlive() const { return alive; };
bool is_eaten() const { return eaten; };
int getReq_alive() const { return req_alive; }

protected: 
double x, y; 
// int sight = 200;   //distance required for change in direction
double vx, vy;
double v_size = get_param("prey_maxv");

private: 

void limitVelocity();
int attractionRange = get_param("prey_attraction_range");  
int repulsionRange = get_param("prey_repulsion_range");  
int runRange = get_param("prey_run_range");
int attraction_coef = get_param("prey_attraction_coef");
int repulsion_coef = get_param("prey_repulsion_coef");
int run_coef = get_param("prey_run_coef");
int alive = 0;
bool eaten ;
int req_alive = get_param("prey_req_alive");
};

#endif