#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <random>
#include "animal.h"
#include "predator.h"
#include "prey.h"
#include "generate_preys.h"
#include "generate_predators.h"
#include "settings.h"


int main() {
    //SETTINGS
    int fps = get_param("fps");                             //desired FPS
    int sim_time = get_param("sim_time");                   //simulation time
    int totalFrames = fps * sim_time;                       //total number of frames
    std::vector<prey> preys = generate_preys(get_param("n_preys")); //starting number of preys
    std::vector<predator> predators = generate_predators(get_param("n_predators")); //starting number of predators
    //--------------------------------------------------------------------------------------------

    //creating directory "simulation_data"
    // clear it first from previous simulations

    const std::string folderName = "simulation_data";
    if (std::filesystem::exists(folderName)) {
        std::filesystem::remove_all(folderName);
    }
    std::filesystem::create_directory(folderName);


//simulation
    for (int frame = 0; frame < totalFrames; ++frame) {
        std::cout << "Frame: " << frame << std::endl;
        int n_prey = preys.size();
        int n_predator = predators.size();
        std::cout << "Number of preys and predators: " << n_prey << " " << n_predator << std::endl;
        //create data.txt 
        std::string filePath = folderName + "/" + std::to_string(frame) + ".txt";

        std::ofstream outFile(filePath);
        if (!outFile) {
            std::cerr << "Error creating file: " << filePath << std::endl;
            return 1;
        }

        //write data from current iteration into file
        for (int i =0;i<n_prey; i++) {
            outFile << preys[i].getX() << "; " << preys[i].getY() << "; "
                    << preys[i].getVX() << "; " << preys[i].getVY() << "\n";
        }

        outFile << " " << "\n";

        for (int i =0;i<n_predator; i++) {
            outFile << predators[i].getX() << "; " << predators[i].getY() << "; "
                    << predators[i].getVX() << "; " << predators[i].getVY() <<"\n";
        }

        outFile.close();

        //update object position
        std::vector<prey> new_preys;
        std::vector<int> dead_preys;
        for (int i =0;i<n_prey; i++) {
            preys[i].update(preys);
            preys[i].run(predators);
            if (preys[i].getAlive() >= preys[i].getReq_alive()) {
                new_preys.push_back(prey(preys[i].getX(),preys[i].getY()));
            }   

            if (preys[i].is_eaten() == true) {
                dead_preys.push_back(i);
            }  
        }
        for (size_t i = 0; i < new_preys.size(); i++) {
            preys.push_back(new_preys[i]);
        }
        new_preys.clear();

        for (int i = dead_preys.size() - 1; i >= 0; --i) {
            preys.erase(preys.begin() + dead_preys[i]);
        }
        dead_preys.clear();

        std::vector<predator> new_predators;
        std::vector<int> dead_predators;
        for (int i = 0;i<n_predator; i++) {
            predators[i].update(predators); 
            predators[i].chase(preys);  
            if (predators[i].getScore() >= predators[i].getReq_score()) {
                new_predators.push_back(predator(predators[i].getX(),predators[i].getY()));
            }

            if(predators[i].getScore() <= get_param("predator_death_score")) {
                dead_predators.push_back(i);
            }
            // std::cout << predators[i].getScore() << " ";
        }

        for (size_t i = 0; i < new_predators.size(); i++) {
            predators.push_back(new_predators[i]);
        }
        new_predators.clear();

        for (size_t i = 0; i < dead_predators.size(); i++){
            // std::cout << dead_predators[i] << std::endl;
        }

        for (int i = dead_predators.size() - 1; i >= 0; --i){
            predators.erase(predators.begin() + dead_predators[i]);
        }
        dead_predators.clear();

        n_predator = predators.size();
        n_prey = preys.size();
        if (n_predator ==  0 || n_prey == 0) {
            std::cout << "Simulation ended, only one type alive." << std::endl;
            break;
        } 
    }
    


    

    //simulation
//   for (int frame = 0; frame < totalFrames; ++frame) {
//         //create data.txt 
//         std::string filePath = folderName + "/" + std::to_string(frame) + ".txt";

//         std::ofstream outFile(filePath);
//         if (!outFile) {
//             std::cerr << "Error creating file: " << filePath << std::endl;
//             return 1;
//         }

//         //write data from current iteration into file
//         for (int i =0;i<n_prey; i++) {
//             outFile << preys[i].getX() << "; " << preys[i].getY() << "; "
//                     << preys[i].getVX() << "; " << preys[i].getVY() <<"\n";
//         }
//         for (int i =0;i<n_predator; i++) {
//             outFile << predators[i].getX() << "; " << predators[i].getY() << "; "
//                     << predators[i].getVX() << "; " << predators[i].getVY() <<"\n";
//         }

//         outFile.close();

//         //update object position
//         for (int i =0;i<n_prey; i++) {
//             std::vector<std::pair<double,double>> r_matrix = preys[i].look_for_friends(preys);
//             preys[i].attraction(r_matrix, preys[i]);
//             preys[i].update();
//         }
//         for (int i =0;i<n_predator; i++) {
//             std::pair<double,double> r_min = predators[i].look_for_prey(preys);
//             if (r_min.first != 0.0 && r_min.second != 0.0) {
//                 std::cout << "r_min je " << r_min.first << std::endl;
//                 predators[i].persue(r_min, predators[i]);
//             }
            
//             predators[i].update();
//         }
//     }

    std::cout << "Simulation completed. Files created in folder: " << folderName << std::endl;
    
return 0;
}