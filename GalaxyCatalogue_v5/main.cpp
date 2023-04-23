#include "interface.cpp"
#include <stdexcept>
#include <sstream>
#include <vector>
#include <cmath>
using namespace observable;
int main() {
    std::vector<astronomical_object<double>*> data;
    // Read data from file or user input
    int input;
    bool end;
    while(!end){
        std::cout << std::string(69, '*') << std::endl;
        std::cout << std::string(30, '-') << "MAIN MENU" << std::string(30, '-') << std::endl;
        std::cout << std::string(69, '*') << std::endl;
        std::cout << " 1. File Input " << std::endl;
        std::cout << " 2. Manual Input" << std::endl;
        std::cout << " 3. Catalogue Output" << std::endl;
        std::cin >> input;
        if (input == 1) {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            read_file<double>(data, filename);
        } else if (input == 2) {
            read_input<double>(data);
        } else if (input == 3) {
            std::cout << "\n\t Exiting Program" << std::endl;
            end == 1;
            // Write data to file
            write<double>(data, "catalog_output.txt");
            // Print data as a table in the terminal
            print<double>(data);
            // Free memory
            for (auto obj : data) {
                delete obj;
            }
            return 0;
            
        } else {
            std::cerr << "Error: Invalid input." << std::endl;
            return 0;
        };
    };
    return 0;
}

 