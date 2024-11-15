#include <string>
#include <fstream>
#include <random>
#include <cmath>
#include "predator.h"
using namespace std;

predator::predator(float startX, float startY) : animal(startX, startY) {
    x = startX;
    y = startY;
    //randomly generated components of velocity vector
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_real_distribution<float> rand(-1.0, 1.0); //range within the numbers will be created

    float vx_rand, vy_rand, norm;
    do {
        //two random floats
        vx_rand = rand(gen);
        vy_rand = rand(gen);

        //Euclidean norm of those two floats
        norm = sqrt(vx_rand * vx_rand + vy_rand * vy_rand);
    } while (norm == 0.0f); //avoiding division by zero

    //scaling these two random floats to velocity size
    vx = v_size * (vx_rand / norm);
    vy = v_size * (vy_rand / norm);
}

//position update (or change of velocity according to relative position with "borders")
void predator::update() {
    animal::update();
    x += vx;
    y += vy;
    
    if (x <= 0 || x >= windowWidth){
        vx = -vx;
    }

    if (y <= 0 || y >= windowHeight){
        vy = -vy;
    }
}