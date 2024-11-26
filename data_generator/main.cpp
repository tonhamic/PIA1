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


int main() {
    //SETTINGS
    int fps = 30;                                               //desired FPS
    int sim_time = 30;                                          //simulation time
    int totalFrames = fps * sim_time;                           //total number of frames
    std::vector<prey> preys = generate_preys(20);               //starting number of preys
    std::vector<predator> predators = generate_predators(5);    //starting number of predators
    //--------------------------------------------------------------------------------------------

    //creating directory "simulation_data"
    const std::string folderName = "simulation_data";
    std::filesystem::create_directory(folderName);





//simulation
    for (int frame = 0; frame < totalFrames; ++frame) {
        int n_prey = preys.size();
        int n_predator = predators.size();
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

        //empty line between preys and predators, just uncomment and use when the renderer will be ready for it
        outFile << " " << "\n";

        for (int i =0;i<n_predator; i++) {
            outFile << predators[i].getX() << "; " << predators[i].getY() << "; "
                    << predators[i].getVX() << "; " << predators[i].getVY() <<"\n";
        }

        outFile.close();

        //update object position
        for (int i =0;i<n_prey; i++) {
            preys[i].update(preys);       
        }

        for (int i =0;i<n_predator; i++) {
            predators[i].update(predators); 
            predators[i].chase(preys);  
            if (predators[i].getScore() == 5) {
                predators.push_back(predator(predators[i].getX(),predators[i].getY()));
            }  
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