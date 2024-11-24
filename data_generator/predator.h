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
void update(std::vector<predator>& others);
void chase(std::vector<prey> enemies);
double getX() const { return x; };
double getY() const { return y; };
double getVX() const { return vx; };
double getVY() const { return vy; };
int getScore() const { return score; };
// //matrix of distances from prey in close proximity
// std::pair<double, double> look_for_prey(const std::vector<prey>& vec_prey) const;
// //calculation of change in direction
// void persue(std::pair<double, double>& r_min, predator& self);

protected: 
double x, y;           
double vx, vy;   
double v_size = 15.0;   
// int sight = 300;   //distance required for change in direction  

private:
int score; 
void limitVelocity();
const double attractionRange = 1000.0;  
const double repulsionRange = 400.0;  
static constexpr double G = 1500.0;
static constexpr double K = 2000.0;


};

#endif