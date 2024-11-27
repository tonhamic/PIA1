#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include "predator.h"
#include "prey.h"
using namespace std;

predator::predator(double startX, double startY) : animal(startX, startY) {
    x = startX;
    y = startY;
    //randomly generated components of velocity vector
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_real_distribution<double> rand(-1.0, 1.0); //range within the numbers will be created

    double vx_rand, vy_rand, norm;
    do {
        //two random doubles
        vx_rand = rand(gen);
        vy_rand = rand(gen);

        //Euclidean norm of those two doubles
        norm = sqrt(vx_rand * vx_rand + vy_rand * vy_rand);
    } while (norm == 0.0f); //avoiding division by zero

    //scaling these two random doubles to velocity size
    vx = v_size * (vx_rand / norm);
    vy = v_size * (vy_rand / norm);
}

void predator::limitVelocity() {
    double velocityNorm = sqrt(vx * vx + vy * vy);
    if (velocityNorm > v_size) {
        vx = (vx / velocityNorm) * v_size;
        vy = (vy / velocityNorm) * v_size;
    }
}

void predator::update(std::vector<predator>& others) {
    //iteration through prey objects for possible interactions
    for (predator& other : others) {
        if (&other == this) continue; //avoiding self-interaction

        double dx = other.x - x;
        double dy = other.y - y;
        double distance = sqrt(dx * dx + dy * dy);

        
        // if (distance > 0 && distance < attractionRange) {
        //     //attraction force (m1,2 = 1)
        //     double force = G / (distance * distance); //analogy with newton's gravity law
        //     double fx = force * (dx / distance);      //x component of force
        //     double fy = force * (dy / distance);      //y component of force

        //     //new velocity
        //     vx += fx;
        //     vy += fy;
        // }

        if (distance > 0 && distance < repulsionRange) {
            //repulsion force (m1,2 = 1)
            double force = -repulsion_coef / (distance * distance); //analogy with newton's gravity law
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

void predator::chase(std::vector<prey> enemies){
        double min_distance = eat_distance + 1.0;
    for (auto& enemy : enemies) {

        double dx = enemy.getX() - x;
        double dy = enemy.getY() - y;
        double distance = sqrt(dx * dx + dy * dy);

        
        if (distance > 0 && distance < chaseRange) {
            //attraction force (m1,2 = 1)
            double force = chase_coef / (distance * distance); //analogy with newton's gravity law
            double fx = force * (dx / distance);      //x component of force
            double fy = force * (dy / distance);      //y component of force

            //new velocity
            vx += fx;
            vy += fy;
        }

        if(distance<min_distance){
            min_distance = distance;
        }


    }

    if(min_distance <= eat_distance){
        score++;
    }
    else {
        score--;
    }
    if(score > req_score){
        score = 0;
    }
}


// //looking for the closest prey in proximity
// std::pair<double,double> predator::look_for_prey(const std::vector<prey>& vec_prey) const{
//     std::vector<std::pair<double,double>> rr_matrix;
//     std::pair<double,double> r_min;
//     int n = 0;
//     rr_matrix.clear();
//     for (const auto& prey:vec_prey) {
//         double r_x = (prey.getVX() - this->x);
//         double r_y = (prey.getVY() - this->y);
//         if (std::sqrt(r_x*r_x + r_y*r_y) <sight) {
//             rr_matrix.push_back(std::make_pair(r_x,r_y));
//             n += 1;   
//         }
//     }
//     if (rr_matrix.size()==0){
//         r_min = {0.0,0.0};
//     } else {
//         int min_n = 0;
//         double min_r = std::sqrt(rr_matrix[0].first*rr_matrix[0].first + rr_matrix[0].second*rr_matrix[0].second);
//         for (int i=0; i<n; i++) {
//             if (std::sqrt(rr_matrix[i].first*rr_matrix[i].first + rr_matrix[i].second*rr_matrix[i].second) < min_r) {
//                 min_r = std::sqrt(rr_matrix[i].first*rr_matrix[i].first + rr_matrix[i].second*rr_matrix[i].second);
//                 min_n = i;
//                 }
//         }
//         r_min = rr_matrix[min_n];
//     }
//     return r_min;
// }

// //prey persue
// void predator::persue(std::pair<double, double>& r_min, predator& self) {
//     double rx1 = r_min.first/std::sqrt(r_min.first*r_min.first + r_min.second*r_min.second);
//     double ry1 = r_min.second/std::sqrt(r_min.first*r_min.first + r_min.second*r_min.second);
//     double vx1 = self.getVX()/std::sqrt(self.getVX()*self.getVX() + self.getVY()*self.getVY());
//     double vy1 = self.getVY()/std::sqrt(self.getVX()*self.getVX() + self.getVY()*self.getVY());
//     double alpha = sight/std::sqrt(r_min.first*r_min.first + r_min.second*r_min.second);
//     double vx_d = (1-alpha)*vx1 + alpha*rx1;
//     double vy_d = (1-alpha)*vy1 + alpha*ry1;
//     double vx_delta = v_size*vx_d/std::sqrt(vx_d*vx_d + vy_d*vy_d);
//     double vy_delta = v_size*vy_d/std::sqrt(vx_d*vx_d + vy_d*vy_d);
//     std::cout << vx << ", " << vx_delta << std::endl;
//     vx = vx_delta;
//     vy = vy_delta;

// }



// //position update (or change of velocity according to relative position with "borders")
// void predator::update() {
//     animal::update();
//     x += vx;
//     y += vy;
    
//     if (x >= windowWidth) {
//         x = windowWidth-5;
//         vx = -vx;
//     }
//     if (x <= 0) {
//         x = 5;
//         vx = -vx;
//     }
//     if (y >= windowHeight) {
//         y = windowHeight-5;
//         vy = -vy;
//     }
//     if (y <= 0){
//         y = 5;
//         vy = -vy;
//     }
// }
