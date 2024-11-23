#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include "predator.h"
#include "prey.h"
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

//looking for the closest prey in proximity
std::pair<double,double> predator::look_for_prey(const std::vector<prey>& vec_prey) const{
    std::vector<std::pair<double,double>> rr_matrix;
    std::pair<double,double> r_min;
    int n = 0;
    rr_matrix.clear();
    for (const auto& prey:vec_prey) {
        double r_x = (prey.getVX() - this->x);
        double r_y = (prey.getVY() - this->y);
        if (std::sqrt(r_x*r_x + r_y*r_y) <sight) {
            rr_matrix.push_back(std::make_pair(r_x,r_y));
            n += 1;   
        }
    }
    if (rr_matrix.size()==0){
        r_min = {0.0,0.0};
    } else {
        int min_n = 0;
        double min_r = std::sqrt(rr_matrix[0].first*rr_matrix[0].first + rr_matrix[0].second*rr_matrix[0].second);
        for (int i=0; i<n; i++) {
            if (std::sqrt(rr_matrix[i].first*rr_matrix[i].first + rr_matrix[i].second*rr_matrix[i].second) < min_r) {
                min_r = std::sqrt(rr_matrix[i].first*rr_matrix[i].first + rr_matrix[i].second*rr_matrix[i].second);
                min_n = i;
                }
        }
        r_min = rr_matrix[min_n];
    }
    return r_min;
}

//prey persue
void predator::persue(std::pair<double, double>& r_min, predator& self) {
    double rx1 = r_min.first/std::sqrt(r_min.first*r_min.first + r_min.second*r_min.second);
    double ry1 = r_min.second/std::sqrt(r_min.first*r_min.first + r_min.second*r_min.second);
    double vx1 = self.getVX()/std::sqrt(self.getVX()*self.getVX() + self.getVY()*self.getVY());
    double vy1 = self.getVY()/std::sqrt(self.getVX()*self.getVX() + self.getVY()*self.getVY());
    double alpha = sight/std::sqrt(r_min.first*r_min.first + r_min.second*r_min.second);
    double vx_d = (1-alpha)*vx1 + alpha*rx1;
    double vy_d = (1-alpha)*vy1 + alpha*ry1;
    double vx_delta = v_size*vx_d/std::sqrt(vx_d*vx_d + vy_d*vy_d);
    double vy_delta = v_size*vy_d/std::sqrt(vx_d*vx_d + vy_d*vy_d);
    std::cout << vx << ", " << vx_delta << std::endl;
    vx = vx_delta;
    vy = vy_delta;

}



//position update (or change of velocity according to relative position with "borders")
void predator::update() {
    animal::update();
    x += vx;
    y += vy;
    
    if (x >= windowWidth) {
        x = windowWidth-5;
        vx = -vx;
    }
    if (x <= 0) {
        x = 5;
        vx = -vx;
    }
    if (y >= windowHeight) {
        y = windowHeight-5;
        vy = -vy;
    }
    if (y <= 0){
        y = 5;
        vy = -vy;
    }
}
