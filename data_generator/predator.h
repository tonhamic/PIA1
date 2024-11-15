#ifndef PREDATOR_H
#define PREDATOR_H

#include <string>
#include <fstream>
#include "animal.h"

using namespace std;

class  predator : public animal {
public:
predator(float startX, float startY);
void update();
float getX() const { return x; };
float getY() const { return y; };
float getVX() const { return vx; };
float getVY() const { return vy; };

protected: 
float x, y;           
float vx, vy;   
float v_size = 70.0;       
private: 


};

#endif