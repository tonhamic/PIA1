#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


// funkce, která rozdělí linku settings podle oddělovače
std::vector<std::string> split (const std::string &s) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, '=')) {
        result.push_back (item);
    }

    return result;
}

// funkce, která načte parametr ze settings.txt
int get_param(std::string param_name) {
    std::ifstream settings("data_generator/settings.txt");
    std::string line;
    while (std::getline(settings, line)) {
        std::string param = split(line)[0];
        std::string value = split(line)[1];
        if (param == param_name) {
            return std::stoi(value);
        }
    }
    // throw error if parameter not found
    throw std::invalid_argument("Parameter not found in settings.txt: " + param_name);
}
