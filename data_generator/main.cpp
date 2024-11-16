#include <iostream>
#include <fstream>
#include <filesystem>
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
    prey prey(400.0, 300.0);
    
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
        outFile << prey.getX() << "; " << prey.getY() << "; "
                << prey.getVX() << "; " << prey.getVY();

        outFile.close();

        //update object position
        prey.update();
    }

    std::cout << "Simulation complete. Files created in folder: " << folderName << std::endl;
    
return 0;
}