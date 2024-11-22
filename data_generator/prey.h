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
prey(float startX, float startY);
void update();
float getX() const { return x; };
float getY() const { return y; };
float getVX() const { return vx; };
float getVY() const { return vy; };
//matrix of distances from others in close proximity
std::vector<std::pair<double, double>> look_for_friends(const std::vector<prey>& vec_prey) const;
std::vector<std::pair<double, double>> look_for_predator(const std::vector<predator>& vec_predator) const;
//calculation of change in direction
void attraction(std::vector<std::pair<double, double>>& r_matrix, prey& self);
void flight(std::vector<std::pair<double, double>>& r_matrix, prey& self);


protected: 
float x, y; 
int sight = 200;   //distance required for change in direction
float vx, vy;
float v_size = 10.0;

private: 


};

#endif