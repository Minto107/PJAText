#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>


void lines_amount(const std::string &file, const std::string &output) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        ++counter;
    }
    if (output.empty() || output == " ") {
        std::cout << "Amount of lines in specified file: " << counter << '\n';
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << "Amount of lines in specified file: " << counter << '\n';
        os.close();
    }
}

void number_amount(const std::string &file, const std::string &output) {
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
    if (output.empty() || output == " ") {
        std::cout << "Numbers in specified file: " << counter << '\n';
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << "Numbers in specified file: " << counter << '\n';
        os.close();
    }
}

void digit_amount(const std::string &file, const std::string &output) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (std::string s; stream >> s;) {
            for (char i : s) {
                if (isdigit(i)) {
                    counter++;
                }
            }
        }
    }
    if (output.empty() || output == " ") {
        std::cout << "Digits in specified file: " << counter << '\n';
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << "Digits in specified file: " << counter << '\n';
        os.close();
    }

}

void char_amount(const std::string &file, const std::string &output) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (char i : line) {
            if (isspace(i)) {
                ++counter;
            }
        }
        for (std::string word; stream >> word;) {
            counter = counter + word.size();
        }
    }
    if (output.empty() || output == " ") {
        std::cout << "Number of chars in specified file: " << counter << '\n';
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << "Number of chars in specified file: " << counter << '\n';
        os.close();
    }
}

void find_anagrams(const std::string &file, const std::vector<std::string> &anagrams_to_find, const std::string &output) {
    for (const auto &anagram_to_find : anagrams_to_find) {
        std::map<char, int> occurrences_in_anagrams_to_find;
        for (auto c : anagram_to_find) {
            occurrences_in_anagrams_to_find[c] += 1;
        }
        if (output.empty() || output == " ") {
            std::cout << "Anagrams for word " << anagram_to_find << ": ";
        } else {
            std::ofstream os;
            os.open(output, std::ios_base::app);
            os << "Anagrams for word " << anagram_to_find << ": ";
            os.close();
        }
        std::fstream input_file(file);
        for (std::string line; std::getline(input_file, line);) {
            std::stringstream stream(line);
            for (std::string s; stream >> s;) {
                std::map<char, int> occurrences;
                for (auto c : s) {
                    occurrences[c] += 1;
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
                }
                for (auto[key, value] : occurrences) {
                    std::ostringstream oss;
                    oss << key << " + " << value;
                    tmp1 = oss.str();
                    second.push_back(tmp1);
                }
                if (first == second) {
                    if (output.empty() || output == " ") {
                        std::cout << s << ", ";
                    } else {
                        std::ofstream os;
                        os.open(output, std::ios_base::app);
                        os << s << ", ";
                        os.close();
                    }
                }
            }
        }
        if (output.empty() || output == " ") {
            std::cout << '\n';
        } else {
            std::ofstream os;
            os.open(output, std::ios_base::app);
            os << '\n';
            os.close();
        }
    }
}

void find_palindrome(const std::string &file, const std::vector<std::string> &palindromes, const std::string &output) {
    for (auto palindrome : palindromes) {
        std::fstream input_file(file);
        if (output.empty() || output == " ") {
            std::cout << "Palindromes for word " << palindrome << ": ";
        } else {
            std::ofstream os;
            os.open(output, std::ios_base::app);
            os << "Palindromes for word " << palindrome << ": ";
            os.close();
        }
        std::reverse(palindrome.begin(), palindrome.end());
        for (std::string line; std::getline(input_file, line);) {
            std::stringstream stream(line);
            for (std::string word; stream >> word;) {
                std::string tmp = word;
                std::reverse(tmp.begin(), tmp.end());
                if (tmp == palindrome) {
                    if (output.empty() || output == " ") {
                        std::cout << tmp << ", ";
                    } else {
                        std::ofstream os;
                        os.open(output, std::ios_base::app);
                        os << tmp << ", ";
                        os.close();
                    }
                }
            }
        }
        if (output.empty() || output == " ") {
            std::cout << '\n';
        } else {
            std::ofstream os;
            os.open(output, std::ios_base::app);
            os << '\n';
            os.close();
        }
    }
}

void sort_alphabetically(const std::string &file, const std::string &output) {

    std::fstream input_file(file);
    std::vector<std::string> sorted;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (std::string word; stream >> word;) {
            sorted.push_back(word);
        }
    }
    std::sort(sorted.begin(), sorted.end(), [](std::string x, std::string y) {
        for (auto &ref:x)
            ref = tolower(ref);
        for (auto &ref:y)
            ref = tolower(ref);
        return x < y;
    });
    for (const auto &i : sorted) {
        if (output.empty() || output == " ") {
            std::cout << i << ' ';
        } else {
            std::ofstream os;
            os.open(output, std::ios_base::app);
            os << i << ' ';
            os.close();
        }
    }
    if (output.empty() || output == " ") {
        std::cout << '\n';
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << '\n';
        os.close();
    }
}

void sort_reverse_alphabetically(const std::string &file, const std::string &output) {

    std::fstream input_file(file);
    std::vector<std::string> sorted;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (std::string word; stream >> word;) {
            sorted.push_back(word);
        }
    }
    std::sort(sorted.begin(), sorted.end(), [](std::string x, std::string y) {
        for (auto &ref:x)
            ref = tolower(ref);
        for (auto &ref:y)
            ref = tolower(ref);
        return x > y;
    });
    for (const auto &i : sorted) {
        if (output.empty() || output == " ") {
            std::cout << i << ' ';
        } else {
            std::ofstream os;
            os.open(output, std::ios_base::app);
            os << i << ' ';
            os.close();
        }
    }
    if (output.empty() || output == " ") {
        std::cout << '\n';
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << '\n';
        os.close();
    }
}

int main() {
    std::string file = R"(C:\Users\minto.MSI-B450TM\CLionProjects\PJAText\test.txt)";
    std::string output = R"(C:\Users\minto.MSI-B450TM\CLionProjects\PJAText\output.txt)";
    std::string clr;
    lines_amount(file, clr);
    number_amount(file, clr);
    digit_amount(file, clr);
    char_amount(file, clr);
    std::string anagramExample = "listen";
    std::vector<std::string> anagram_v;
    anagram_v.push_back(anagramExample);
    anagram_v.emplace_back("pap");
    anagram_v.emplace_back("life");
    find_anagrams(file, anagram_v, clr);
    std::string palindrome = "test";
    std::vector<std::string> palindromes;
    palindromes.push_back(palindrome);
    palindromes.emplace_back("there");
    find_palindrome(file, palindromes, clr);
    sort_alphabetically(file, clr);
    sort_reverse_alphabetically(file, clr);
}
