#include <string>
#include <fstream>
#include <random>
#include <cmath>
#include <algorithm>
#include "prey.h"
#include "predator.h"

using namespace std;

prey::prey(double startX, double startY) : animal(startX, startY) {
    x = startX;
    y = startY;

    // Randomly generated components of velocity vector
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> rand(-1.0, 1.0);  // Range within the numbers will be created

    double vx_rand, vy_rand, norm;
    do {
        vx_rand = rand(gen);
        vy_rand = rand(gen);

        // Euclidean norm of those two doubles
        norm = sqrt(vx_rand * vx_rand + vy_rand * vy_rand);
    } while (norm == 0.0);  // Avoid division by zero

    // Scaling these two random doubles to velocity size
    vx = v_size * (vx_rand / norm);
    vy = v_size * (vy_rand / norm);
}

void prey::limitVelocity() {
    double velocityNorm = sqrt(vx * vx + vy * vy);
    if (velocityNorm > v_size) {
        vx = (vx / velocityNorm) * v_size;
        vy = (vy / velocityNorm) * v_size;
    }
}

void prey::update(std::vector<prey>& others) {
    //iteration through prey objects for possible interactions
    for (prey& other : others) {
        if (&other == this) continue; //avoiding self-interaction

        double dx = other.x - x;
        double dy = other.y - y;
        double distance = sqrt(dx * dx + dy * dy);

        
        if (distance > 0 && distance < attractionRange) {
            //attraction force (m1,2 = 1)
            double force = G / (distance * distance); //analogy with newton's gravity law
            double fx = force * (dx / distance);      //x component of force
            double fy = force * (dy / distance);      //y component of force

            //new velocity
            vx += fx;
            vy += fy;
        }

        if (distance > 0 && distance < repulsionRange) {
            //repulsion force (m1,2 = 1)
            double force = -G / (distance * distance); //analogy with newton's gravity law
            double fx = force * (dx / distance);       //x component of force
            double fy = force * (dy / distance);       //y component of force

            //new velocity
            vx += fx;
            vy += fy;
        }
    }



    //limit velocity to maximal velocity of class prey
    limitVelocity();

    //boundary conditions
    if (x >= windowWidth) {
        x = windowWidth - 1;
        vx = -vx;  
    }
    if (x <= 0) {
        x = 1;
        vx = -vx;  
    }
    if (y >= windowHeight) {
        y = windowHeight - 1;
        vy = -vy;  
    }
    if (y <= 0) {
        y = 1;
        vy = -vy;  
    }

    //update position based on calculated velocity
    x += vx;
    y += vy;
}
