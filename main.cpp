#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void linesAmount(std::string file) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        ++counter;
    }
    std::cout << "Amount of lines in specified file: " << counter << '\n';
}

void numberAmount(std::string file) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (std::string s; stream >> s;) {
            std::string::const_iterator it = s.begin();
            while (it != s.end() && std::isdigit(*it)) ++it;
            if (!s.empty() && s.find_first_not_of("-0123456789") == std::string::npos) {
                ++counter;
            }
        }
    }
    std::cout << "Numbers in specified file: " << counter << '\n';
}


void digitAmount(std::string file) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (std::string s; stream >> s;) {
            for (int i = 0; i < s.size(); ++i) {
                if (isdigit(s[i])) {
                    counter++;
                }
            }
        }
    }
    std::cout << "Digits in specified file: " << counter << '\n';

}

void charAmount(std::string file) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line); ) {
        std::stringstream stream(line);
        for (int i = 0; i < line.length(); ++i) {
            if (isspace(line.at(i))){
                ++counter;
            }
        }
        for (std::string word; stream >> word; ) {
            counter = counter + word.size();
        }
    }
    std::cout << "Number of chars in specified file: " << counter << '\n';
}

int main() {
    std::string file = R"(C:\Users\minto.MSI-B450TM\CLionProjects\PJAText\test.txt)";
    linesAmount(file);
    numberAmount(file);
    digitAmount(file);
    charAmount(file);
}
