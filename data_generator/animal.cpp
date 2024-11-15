#include <string>
#include <fstream>
#include "animal.h"

using namespace std;

animal::animal(float startX, float startY) {
    x = startX;
    y = startY;
}

//position update (or change of velocity according to relative position with "borders")
void animal::update() {
    x += vx;
    y += vy;
    
    if (x <= 0 || x >= windowWidth){
        vx = -vx;
    }

    if (y <= 0 || y >= windowHeight){
        vy = -vy;
    }
}


