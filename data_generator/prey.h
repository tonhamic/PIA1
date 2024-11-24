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
void update(std::vector<prey>& others);
double getX() const { return x; };
double getY() const { return y; };
double getVX() const { return vx; };
double getVY() const { return vy; };


protected: 
double x, y; 
int sight = 200;   //distance required for change in direction
double vx, vy;
double v_size = 10.0;

private: 

void limitVelocity();
const double attractionRange = 500.0;  
const double repulsionRange = 100.0;  
static constexpr double G = 2000.0;
};

#endif