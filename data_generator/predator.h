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
predator(float startX, float startY);
void update();
float getX() const { return x; };
float getY() const { return y; };
float getVX() const { return vx; };
float getVY() const { return vy; };
//matrix of distances from prey in close proximity
std::pair<double, double> look_for_prey(const std::vector<prey>& vec_prey) const;
//calculation of change in direction
void persue(std::pair<double, double>& r_min, predator& self);

protected: 
float x, y;           
float vx, vy;   
float v_size = 15.0;   
int sight = 300;   //distance required for change in direction    
private: 


};

#endif