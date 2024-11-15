#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <fstream>

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
int windowWidth = 1280;
int windowHeight = 720;
private: 

};

#endif