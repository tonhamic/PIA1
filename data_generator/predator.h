#ifndef PREDATOR_H
#define PREDATOR_H

#include <string>
#include <fstream>
#include <vector>
#include "animal.h"
class prey;
#include "prey.h"
#include "settings.h"


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
int getReq_score() const { return req_score; };
// //matrix of distances from prey in close proximity
// std::pair<double, double> look_for_prey(const std::vector<prey>& vec_prey) const;
// //calculation of change in direction
// void persue(std::pair<double, double>& r_min, predator& self);

protected: 
double x, y;           
double vx, vy;   
double v_size = get_param("predator_maxv");   
// int sight = 300;   //distance required for change in direction  

private:
int score = 0; 
int req_score = get_param("predator_req_score");
void limitVelocity();
int attractionRange = get_param("predator_attraction_range");
int chaseRange = get_param("predator_chase_range");
int repulsionRange = get_param("predator_repulsion_range");
int chase_coef = get_param("predator_chase_coef");
int repulsion_coef = get_param("predator_repulsion_coef");


};

#endif