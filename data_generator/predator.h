#ifndef PREDATOR_H
#define PREDATOR_H

#include <string>
#include <fstream>
#include <vector>
#include "animal.h"
class prey;
#include "prey.h"

using namespace std;
class  predator : public animal {
public:
predator(double startX, double startY);
void update();
double getX() const { return x; };
double getY() const { return y; };
double getVX() const { return vx; };
double getVY() const { return vy; };
//matrix of distances from prey in close proximity
std::pair<double, double> look_for_prey(const std::vector<prey>& vec_prey) const;
//calculation of change in direction
void persue(std::pair<double, double>& r_min, predator& self);

protected: 
double x, y;           
double vx, vy;   
double v_size = 15.0;   
int sight = 300;   //distance required for change in direction    
private: 


};

#endif