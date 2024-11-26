#ifndef PREY_H
#define PREY_H

#include <string>
#include <fstream>
#include <vector>
#include "animal.h"
#include "predator.h"

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
int sight = 200;   //distance required for change in direction
double vx, vy;
double v_size = 10.0;

private: 

void limitVelocity();
static constexpr double attractionRange = 500.0;  
static constexpr double repulsionRange = 100.0;  
static constexpr double G = 2000.0;
static constexpr double R = 1500.0;
int alive = 0;
bool eaten ;
int req_alive = 60;
};

#endif