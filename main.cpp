#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

void lines_amount(const std::string &file, const std::string &output = "") {
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

void number_amount(const std::string &file, const std::string &output = "") {
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

void digit_amount(const std::string &file, const std::string &output = "") {
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

void char_amount(const std::string &file, const std::string &output = "") {
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

void find_anagrams(const std::string &file, const std::vector<std::string> &anagrams_to_find,
                   const std::string &output = "") {
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

void
find_palindrome(const std::string &file, const std::vector<std::string> &palindromes, const std::string &output = "") {
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

void sort_alphabetically(const std::string &file, const std::string &output = "") {

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

void sort_reverse_alphabetically(const std::string &file, const std::string &output = "") {

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

void help() {
    std::ifstream input_file("C:\\Users\\minto.MSI-B450TM\\CLionProjects\\PJAText\\help.txt");
    std::string line;
    for (std::string line; getline(input_file, line);) {
        std::cout << line << '\n';
    }
}

constexpr unsigned int str2int(const char *str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

int main(int argc, char **argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::string file;
    std::string output;
    std::vector<std::string> anagrams;
    std::vector<std::string> palindromes;
    std::vector<std::string> skip_those;
    std::ifstream read_commands("C:\\Users\\minto.MSI-B450TM\\CLionProjects\\PJAText\\help.txt");
    std::string line_1;
    if (args.empty()){
        help();
    } else {
        for (std::string line_1; getline(read_commands, line_1);) {
            std::stringstream stream(line_1);
            for (std::string word; stream >> word;) {
                if (word.find('-') == 0 || word.find("--") == 0) {
                    skip_those.push_back(word);
                }
            }
        }
        std::vector<std::string> input;
        for (int i = 0; i < args.size(); ++i) {
            if (args[i] == "-i" || args[i] == "--input") {
                std::fstream input_file(args[1]);
                for (std::string line; std::getline(input_file, line);) {
                    std::stringstream stream(line);
                    for (std::string word; stream >> word;) {
                        input.push_back(word);
                    }
                    args = input;
                    i = 1;
                }
            }
            if (args[i] == "-o" || args[i] == "--output") {
                output = args[i + 1];
            }
        }
        bool skip = false;
        bool skip1 = false;

        for (int i = 0; i < args.size(); ++i) {
            if (i != 0) {
                switch (str2int(args[i].data())) {
                    case str2int("-n"):
                    case str2int("--newlines"):
                        lines_amount(file, output);
                        break;
                    case str2int("-d"):
                    case str2int("--digits"):
                        digit_amount(file, output);
                        break;
                    case str2int("-dd"):
                    case str2int("--numbers"):
                        number_amount(file, output);
                        break;
                    case str2int("-c"):
                    case str2int("--chars"):
                        char_amount(file, output);
                        break;
                    case str2int("-a"):
                    case str2int("--anagrams"):
                        for (int j = i; j < args.size(); ++j) {
                            if (args[j] == "-p" || args[j] == "--palindromes") {
                                skip = true;
                            } else if (args[j] == "-o" || args[j] == "--output") {
                                skip = true;
                            } else if (!(args[j].find("--") == 0 || args[j].find('-') == 0) && !skip) {
                                anagrams.push_back(args[j]);
                            }
                        }
                        i = i + anagrams.size();
                        find_anagrams(file, anagrams, output);
                        break;
                    case str2int("-p"):
                    case str2int("--palindromes"):
                        for (int j = i; j < args.size(); ++j) {
                            if (args[j] == "-a" || args[j] == "--anagrams" || args[j] == "-o" ||
                                args[j] == "--output") {
                                skip1 = true;
                            } else if (args[j] == "-o" || args[j] == "--output") {
                                skip1 = true;
                            } else if (!(args[j].find("--") == 0 || args[j].find('-') == 0) && !skip1) {
                                palindromes.push_back(args[j]);
                            }
                        }
                        i = i + palindromes.size();
                        find_palindrome(file, palindromes, output);
                        break;
                    case str2int("-s"):
                    case str2int("--sorted"):
                        sort_alphabetically(file, output);
                        break;
                    case str2int("-rs"):
                    case str2int("--reverse-sorted"):
                        sort_reverse_alphabetically(file, output);
                        break;
                    case str2int("-o"):
                    case str2int("--output"):
                        ++i;
                        break;
                    default:
                        /*if (args[i].find('-') == 0 || args[i].find("--") == 0) {
                            help();
                            std::cout << "\nInvalid parameter usage, please refer to the help above.";
                        }*/
                        help();
                        std::cout << "\nParameter " << args[i] << " has not been recognised\n"
                                                                  "Please refer to the table above.";
                        break;
                }
            } else {
                switch (str2int(args[i].data())) {
                    case str2int("--help"):
                    case str2int(""):
                        help();
                        break;
                    case str2int("-f"):
                    case str2int("--file"):
                        file = args[i + 1];
                        ++i;
                        break;
                    default:
                        help();
                        std::cout << "\nParameter " << args[i]
                                  << " has not been recognised or should be provided later\n"
                                     "You should start with -f or -i.";
                        break;
                }
            }
        }
    }
}
