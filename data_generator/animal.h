#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <fstream>
#include "settings.h"

using namespace std;

class animal {
public:
void update();
float getX() const { return x; };
float getY() const { return y; };
float getVX() const { return vx; };
float getVY() const { return vy; };

protected: 
animal(float startX, float startY); // to avoid creating object directly from animal class
float x, y;           
float vx, vy;
//fixed resolution          
int windowWidth = get_param("window_width");
int windowHeight = get_param("window_height");
double eat_distance = get_param("eat_distance");
private: 

};

#endif