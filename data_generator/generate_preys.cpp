#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <random>
#include "animal.h"
#include "predator.h"
#include "prey.h"

 std::vector<prey> generate_preys(int n){
    //object generation, into vectors
    std::vector<prey> preys;
    //random positon generator
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> x_rand(0,1280.0);
    std::uniform_real_distribution<double> y_rand(0,720.0);



    for (int i = 0; i<n;++i) {
        double x_sur = x_rand(gen);
        double y_sur = y_rand(gen);
        preys.push_back(prey(x_sur,y_sur));
        
    }
    return preys;
}