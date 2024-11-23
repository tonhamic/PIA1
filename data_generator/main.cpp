#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <random>
#include "animal.h"
#include "predator.h"
#include "prey.h"


int main() {
    int fps = 30;                      //desired FPS
    int sim_time = 30;                  //simulation time
    int totalFrames = fps * sim_time;  //total number of frames

    //creating directory "simulation_data"
    const std::string folderName = "simulation_data";
    std::filesystem::create_directory(folderName);

    //test object
    //prey prey(400.0, 300.0);
    
    
    //object generation, into vectors
    std::vector<predator> vec_predator;
    std::vector<prey> vec_prey;
    int n_prey = 2; //number of prey
    int n_predator = 2; //number of predators
    //random positon generator
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> x_rand(0,1280);
    std::uniform_int_distribution<int> y_rand(0,720);

    for (int i = 0; i<n_predator;++i) {
        int x_sur = x_rand(gen);
        int y_sur = y_rand(gen);
        vec_predator.push_back(predator(x_sur,y_sur));
       
    }

    for (int i = 0; i<n_prey;++i) {
        int x_sur = x_rand(gen);
        int y_sur = y_rand(gen);
        vec_prey.push_back(prey(x_sur,y_sur));
        
    }
    

    //simulation
    for (int frame = 0; frame < totalFrames; ++frame) {
        //create data.txt 
        std::string filePath = folderName + "/" + std::to_string(frame) + ".txt";

        std::ofstream outFile(filePath);
        if (!outFile) {
            std::cerr << "Error creating file: " << filePath << std::endl;
            return 1;
        }

        //write data from current iteration into file
        for (int i =0;i<n_prey; i++) {
            outFile << vec_prey[i].getX() << "; " << vec_prey[i].getY() << "; "
                    << vec_prey[i].getVX() << "; " << vec_prey[i].getVY() <<"\n";
        }
        for (int i =0;i<n_predator; i++) {
            outFile << vec_predator[i].getX() << "; " << vec_predator[i].getY() << "; "
                    << vec_predator[i].getVX() << "; " << vec_predator[i].getVY() <<"\n";
        }

        outFile.close();

        //update object position
        for (int i =0;i<n_prey; i++) {
            std::vector<std::pair<double,double>> r_matrix = vec_prey[i].look_for_friends(vec_prey);
            vec_prey[i].attraction(r_matrix, vec_prey[i]);
            vec_prey[i].update();
        }
        for (int i =0;i<n_predator; i++) {
            std::pair<double,double> r_min = vec_predator[i].look_for_prey(vec_prey);
            if (r_min.first != 0.0 && r_min.second != 0.0) {
                std::cout << "r_min je " << r_min.first << std::endl;
                vec_predator[i].persue(r_min, vec_predator[i]);
            }
            
            vec_predator[i].update();
        }
    }

    std::cout << "Simulation complete. Files created in folder: " << folderName << std::endl;
    
return 0;
}