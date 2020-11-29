#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void linesAmount(std::string file){
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line); ) {
        std::stringstream stream(line);
        ++counter;
    }
    std::cout << counter;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string file = "test.txt";
    linesAmount("C:\\Users\\minto.MSI-B450TM\\CLionProjects\\PJAText\\test.txt");
    return 0;
}
