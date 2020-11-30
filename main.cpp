#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

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
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (int i = 0; i < line.length(); ++i) {
            if (isspace(line.at(i))) {
                ++counter;
            }
        }
        for (std::string word; stream >> word;) {
            counter = counter + word.size();
        }
    }
    std::cout << "Number of chars in specified file: " << counter << '\n';
}

void find_anagrams(std::string file, std::string anagrams_to_find) {
    std::vector<std::string> anagrams;
    std::map<char, int> occurrences_in_anagrams_to_find;

    for (auto c : anagrams_to_find) {
        occurrences_in_anagrams_to_find[c] += 1;
    }
    std::cout << "Word: " << anagrams_to_find << '\n';
    for (auto[k, value] : occurrences_in_anagrams_to_find) {
        std::cout << k << " - " << value << '\n';
    }
    std::cout << "Anagram size: " << anagrams_to_find.length() << '\n';
    std::fstream input_file(file);
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (std::string s; stream >> s;) {
            std::map<char, int> occurrences;
            std::cout << "Word: " << s << '\n';
            for (auto c : s) {
                occurrences[c] += 1;
            }
            for (auto[k, value] : occurrences) {
                std::cout << k << " - " << value << '\n';
            }
            std::string tmp;
            std::vector<std::string> first;
            std::string tmp1;
            std::vector<std::string> second;
            for (auto[key, value] : occurrences_in_anagrams_to_find) {
                std::ostringstream oss;
                oss << key << " + " << value;
                tmp = oss.str();
                first.push_back(tmp);
                //std::cout << tmp << '\n';
            }
            for (auto[key, value] : occurrences) {
                std::ostringstream oss;
                oss << key << " + " << value;
                tmp1 = oss.str();
                second.push_back(tmp1);
                //std::cout << tmp1 << '\n';
            }
            int counter = 0;
            for (int i = 0; i < first.size(); ++i) {
                tmp = first[i];
                tmp1 = second[i];
                if (tmp == tmp1) {
                    std::cout << "OK\n";
                }
                std::cout << "TMP equals to TMP1\n";
                ++counter;
                std::cout << "Counter status: " << counter << '\n';

            }
            /*for (int i = 0; i < first.size(); ++i) {
                std::cout << "First: " << first[i] << '\n';
            }
            for (int i = 0; i < second.size(); ++i) {
                std::cout << "Second: " << second[i] << '\n';
            }*/
            if (counter == anagrams_to_find.length()) {
                std::cout << "Word " << s << " is an anagram to " << anagrams_to_find << '\n';
            }
        }
    }

}

int main() {
    std::string file = R"(C:\Users\minto.MSI-B450TM\CLionProjects\PJAText\test.txt)";
    linesAmount(file);
    numberAmount(file);
    digitAmount(file);
    charAmount(file);
    std::string anagramExample = "listen";
    find_anagrams(file, anagramExample);
}
