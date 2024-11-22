#include <string>
#include <fstream>
#include <random>
#include <cmath>
#include "prey.h"
#include "predator.h"

using namespace std;

prey::prey(float startX, float startY) : animal(startX, startY) {
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

//looking for prey in close proximity, for change in direction
std::vector<std::pair<double,double>> prey::look_for_friends(const std::vector<prey>& vec_prey) const{
    std::vector<std::pair<double,double>> r_matrix_friends;
    r_matrix_friends.clear();
    for (const auto& prey:vec_prey) {
        if (&prey != this) {
            double r_x = (prey.x - this->x);
            double r_y = (prey.y - this->y);
            if (std::sqrt(r_x*r_x + r_y*r_y) <sight) {
                r_matrix_friends.push_back(std::make_pair(r_x,r_y));
            }
        }
    }
    return r_matrix_friends;
}

//looking for predators in close proximity
std::vector<std::pair<double, double>> prey::look_for_predator(const std::vector<predator>& vec_predator) const{
    std::vector<std::pair<double, double>> r_matrix_foes;
    for (const auto& prey:vec_predator) {
        double r_x = (prey.getVX() - this->x);
        double r_y = (prey.getVY() - this->y);
        if (std::sqrt(r_x*r_x + r_y*r_y) <sight) {
            r_matrix_foes.push_back(std::make_pair(r_x,r_y));
        }
    }
    return r_matrix_foes;

}

//prey attraction
void prey::attraction(std::vector<std::pair<double, double>>& r_matrix_friends, prey& self) {
    for (const auto& pair:r_matrix_friends) {
        double rx1 = pair.first/std::sqrt(pair.first*pair.first + pair.second*pair.second);
        double ry1 = pair.second/std::sqrt(pair.first*pair.first + pair.second*pair.second);
        double vx1 = self.getVX()/std::sqrt(self.getVX()*self.getVX() + self.getVY()*self.getVY());
        double vy1 = self.getVY()/std::sqrt(self.getVX()*self.getVX() + self.getVY()*self.getVY());
        double alpha = sight/std::sqrt(pair.first*pair.first + pair.second*pair.second);
        double vx_d = (1-alpha)*vx1 + alpha*rx1;
        double vy_d = (1-alpha)*vy1 + alpha*ry1;
        double vx_delta = v_size*vx_d/std::sqrt(vx_d*vx_d + vy_d*vy_d);
        double vy_delta = v_size*vy_d/std::sqrt(vx_d*vx_d + vy_d*vy_d);
        vx = vx_delta;
        vy = vy_delta;
    }

}

//predator flight
void prey::flight(std::vector<std::pair<double, double>>& r_matrix_foes, prey& self) {
    for (const auto& pair:r_matrix_foes) {
        double rx1 = pair.first/std::sqrt(pair.first*pair.first + pair.second*pair.second);
        double ry1 = pair.second/std::sqrt(pair.first*pair.first + pair.second*pair.second);
        double vx1 = self.getVX()/std::sqrt(self.getVX()*self.getVX() + self.getVY()*self.getVY());
        double vy1 = self.getVY()/std::sqrt(self.getVX()*self.getVX() + self.getVY()*self.getVY());
        double alpha = sight/std::sqrt(pair.first*pair.first + pair.second*pair.second);
        double vx_d = (1-alpha)*vx1 + alpha*(-rx1);
        double vy_d = (1-alpha)*vy1 + alpha*(-ry1);
        double vx_delta = v_size*vx_d/std::sqrt(vx_d*vx_d + vy_d*vy_d);
        double vy_delta = v_size*vy_d/std::sqrt(vx_d*vx_d + vy_d*vy_d);
        vx = vx_delta;
        vy = vy_delta;
    }

}



//position update (or change of velocity according to relative position with "borders")
void prey::update() {
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