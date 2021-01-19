#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>

/**
 * @brief Template to print an std::vector of any type.
 * @tparam T Type of the std::vector to be printed.
 * @param vec std::vector to be printed.
 */

template<typename T>
void print_vector(const std::vector<T> &vec) {
    for (const auto &i : vec) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

/**
 * @brief Template to check if passed std::vector of any type is empty or not.
 * @tparam T Type of the std::vector to be analyzed.
 * @param vec std::vector to be analyzed.
 * @param output Specifies file that result will be written to.
 * @return Returns true if vec is empty or returns false when it is not empty.
 */

template<typename T>
bool check_if_empty(const std::vector<T> &vec, const std::string &output) {
    if (vec.empty()) {
        if (output.empty() || output == " ") {
            std::cout << "No words have been passed.\n";
        } else {
            std::ofstream os;
            os.open(output, std::ios_base::app);
            os << "No words have been passed.\n";
            os.close();
        }
        return true;
    }
    return false;
}

/**
 * @brief Structure used to sort std::string's in alphabetical order.
 */

struct {
    /**
     * @brief Operator that compares std::string's and sorts them in alphabetical order.
     * @param x First std::string to compare.
     * @param y Second std::string to compare.
     */
    bool operator()(std::string &x, std::string &y) const {
        for (auto &ref:x)
            ref = tolower(ref);
        for (auto &ref:y)
            ref = tolower(ref);
        return x < y;
    }
} alphabetical_order;

/**
 * @brief Reads words from file to a std::vector of std::string's.
 * @param file Specifies the file that will be read.
 * @return Returns std::vector containing words from a specified file.
 */

std::vector<std::string> insert_words_from_file_to_vector(const std::string &file) {
    std::vector<std::string> vec;
    std::fstream input_file(file);
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (std::string word; stream >> word;) {
            vec.push_back(word);
        }
    }
    return vec;
}

/**
 * @brief Function that counts amount of lines in a file.
 * @param file Specifies the file that will be read.
 * @param output Specifies file that result will be written to.
 */

void line_amount(const std::string &file, const std::string &output) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        ++counter;
    }
    if (output.empty() || output == " ") {
        std::cout << "Lines in file: " << counter << '\n';
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << "Lines in file: " << counter << '\n';
        os.close();
    }
}

/**
 * @brief Function counts numbers in a file.
 * @param file Specifies the file that will be read.
 * @param output Specifies file that result will be written to.
 */

void number_amount(const std::string &file, const std::string &output) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (std::string s; stream >> s;) {
            if (std::regex_match(s, std::regex("^[-]?[\\s]?[0-9]*[.]?[0-9]*$"))) {
                if (s == "-") {
                    --counter;
                }
                ++counter;
            }
        }
    }
    if (output.empty() || output == " ") {
        std::cout << "Numbers in file: " << counter << '\n';
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << "Numbers in file: " << counter << '\n';
        os.close();
    }
}

/**
 * @brief Function counts digits in a file.
 * @param file Specifies the file that will be read.
 * @param output Specifies file that result will be written to.
 */

void digit_amount(const std::string &file, const std::string &output) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (std::string s; stream >> s;) {
            for (char i : s) {
                if (isdigit(i)) {
                    ++counter;
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

/**
 * @brief Function counts every character in a file including whitespaces.
 * @param file Specifies the file that will be read.
 * @param output Specifies file that result will be written to.
 */

void char_amount(const std::string &file, const std::string &output) {
    std::fstream input_file(file);
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        counter += line.length();
    }
    if (output.empty() || output == " ") {
        std::cout << "Chars in file: " << counter << '\n';
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << "Chars in file: " << counter << '\n';
        os.close();
    }
}


/**
 * @brief Function converts std::map to std::vector.
 * @param my_map std::map to convert.
 * @return Returns std::map converted to std::vector.
 */

std::vector<std::string> analyze_word(const std::map<char, int> &my_map) {
    std::vector<std::string> vec;
    for (auto[key, value] : my_map) {
        std::ostringstream oss;
        oss << key << " - " << value;
        vec.push_back(oss.str());
    }
    return vec;
}

/**
 * @brief Function finds anagrams specified by anagrams_to_find in file.
 * @param file specifies the file that will be read.
 * @param anagrams_to_find std::vector containing std::string, std::vector contents will be checked if anagrams for these words exist.
 * @param output Specifies file that result will be written to.
 */

void find_anagrams(const std::string &file, const std::vector<std::string> &anagrams_to_find,
                   const std::string &output) {
    if (!check_if_empty(anagrams_to_find, output)) {
        for (const auto &anagram_to_find : anagrams_to_find) {
            if (output.empty() || output == " ") {
                std::cout << "Anagrams for word " << anagram_to_find << ": ";
            } else {
                std::ofstream os;
                os.open(output, std::ios_base::app);
                os << "Anagrams for word " << anagram_to_find << ": ";
                os.close();
            }
            std::map<char, int> occurrences_in_anagrams_to_find;
            for (auto c : anagram_to_find) {
                occurrences_in_anagrams_to_find[c] += 1;
            }
            std::fstream input_file(file);
            for (std::string line; std::getline(input_file, line);) {
                std::stringstream stream(line);
                for (std::string s; stream >> s;) {
                    std::map<char, int> occurrences;
                    for (auto c : s) {
                        occurrences[c] += 1;
                    }
                    auto analyzed_word_from_vector = analyze_word(occurrences_in_anagrams_to_find);
                    auto analyzed_word_from_file = analyze_word(occurrences);
                    if (analyzed_word_from_vector == analyzed_word_from_file) {
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
}

/**
 * @brief Function finds palindromes specified by palindromes in a file.
 * @param file Specifies the file that will be read.
 * @param palindromes std::vector containing std::string, std::vector contents will be checked if palindromes for these words exist.
 * @param output Specifies file that result will be written to.
 */

void
find_palindrome(const std::string &file, std::vector<std::string> &palindromes, const std::string &output) {
    if (!check_if_empty(palindromes, output)) {
        for (int i = 0; i < palindromes.size(); ++i) {
            std::string tmp = palindromes.at(i);
            std::reverse(tmp.begin(), tmp.end());
            if (tmp != palindromes.at(i)) {
                palindromes.erase(palindromes.begin() + i);
            }
        }
        if (!check_if_empty(palindromes, output)) {
            for (const auto &palindrome : palindromes) {
                std::fstream input_file(file);
                if (output.empty() || output == " ") {
                    std::cout << "Palindromes count for word " << palindrome << ": ";
                } else {
                    std::ofstream os;
                    os.open(output, std::ios_base::app);
                    os << "Palindromes count for word " << palindrome << ": ";
                    os.close();
                }
                int counter = 0;
                for (std::string line; std::getline(input_file, line);) {
                    std::stringstream stream(line);
                    for (std::string word; stream >> word;) {
                        if (word == palindrome) {
                            ++counter;
                        }
                    }
                }
                if (output.empty() || output == " ") {
                    std::cout << counter << '\n';
                } else {
                    std::ofstream os;
                    os.open(output, std::ios_base::app);
                    os << counter << '\n';
                    os.close();
                }
            }
        }
    }
}

/**
 * @brief Function sorts file in alphabetical order.
 * @param file Specifies the file that will be read.
 * @param output Specifies file that result will be written to.
 */

void sort_alphabetically(const std::string &file, const std::string &output) {
    auto sorted = insert_words_from_file_to_vector(file);
    if (output.empty() || output == " ") {
        std::cout << "Words in alphabetical order from " << file << " file: ";
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << "Words in alphabetical order from " << file << " file: ";
        os.close();
    }
    std::sort(sorted.begin(), sorted.end(), alphabetical_order);
    if (output.empty() || output == " ") {
        print_vector(sorted);
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        for (const auto &i : sorted) {
            os << i << ' ';
        }
        os << '\n';
        os.close();
    }
}

/**
 * @brief Function sorts file in reverse alphabetical order.
 * @param file Specifies the file that will be read.
 * @param output Specifies file that result will be written to.
 */

void sort_reverse_alphabetically(const std::string &file, const std::string &output) {
    auto sorted = insert_words_from_file_to_vector(file);
    if (output.empty() || output == " ") {
        std::cout << "Words in reverse alphabetical order from " << file << " file: ";
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << "Words in reverse alphabetical order from " << file << " file: ";
        os.close();
    }
    std::sort(sorted.begin(), sorted.end(), alphabetical_order);
    std::reverse(sorted.begin(), sorted.end());
    if (output.empty() || output == " ") {
        print_vector(sorted);
    } else {
        std::ofstream os;
        os.open(output, std::ios_base::app);
        for (const auto &i : sorted) {
            os << i << ' ';
        }
        os << '\n';
        os.close();
    }
}

/**
 * @brief Displays help.
 */

void help() {
    std::cout << "================================================================================\n"
                 "=                                  PJAText                                     =\n"
                 "================================================================================\n"
                 "    --help              - opens this file\n"
                 "-f  --file              - specifies path to the input file(must be a .txt file)\n"
                 "-n  --newlines          - counts lines in specified file\n"
                 "-d  --digits            - counts digits in specified file\n"
                 "-dd --numbers           - counts numbers in specified file\n"
                 "-c  --chars             - counts chars in specified file\n"
                 "-a  --anagrams          - finds anagrams to provided words in specified file\n"
                 "-p  --palindromes       - finds palindromes to provided words in specified file\n"
                 "-s  --sorted            - sorts specified file in alphabetical order\n"
                 "-rs --reverse-sorted    - sorts specified file in reverse alphabetical order\n"
                 "-o  --output            - redirects output to a specified file\n"
                 "-i  --input             - reads flags and arguments from specified file\n"
                 "\n"
                 "Example usage: PJAText.exe -f example.txt -n -c\n"
                 "Example output: \n"
                 "Amount of lines in specified file: X\n"
                 "Number of chars in specified file: Y\n";
}

/**
 * @brief Handles flags and parses parameters.
 * @return Returns execution status code. 0 = execution was successful, -1 = means wrong or no flag were provided.
 */

int main(int argc, char **argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::string file;
    std::string output;
    if (args.empty()) {
        help();
        std::cout << "\nThis application cannot be run without launch flags.\n"
                     "Please refer to the help above.\n";
        return -1;
    }
    std::vector<std::string> input;
    for (int i = 0; i < args.size(); ++i) {
        if (args[i] == "-i" || args[i] == "--input") {
            if (args[0] == "-i" || args[0] == "--input") {
                if (std::ifstream(args[1]).good()) {
                    if (std::regex_match(args[1], std::regex(R"(^[C-Z]:[\\\w\-.]*.txt$)")) ||
                        std::regex_match(args[1], std::regex("^[\\w\\-]*.txt$"))) {
                        std::fstream input_file(args[1]);
                        for (std::string line; std::getline(input_file, line);) {
                            std::stringstream stream(line);
                            for (std::string word; stream >> word;) {
                                input.push_back(word);
                            }
                            args = input;
                            i = 1;
                        }
                    } else {
                        std::cout << "Input file needs to have .txt extension.\n";
                        return -1;
                    }
                }
            } else {
                help();
                std::cout << "\nParameter " << args[i] << " should be the only one provided.\n"
                                                          "Please refer to the help table above.\n";
                return 0;
            }
        }
        if (args[i] == "-o" || args[i] == "--output") {
            if (!(args[i + 1].find("--") == 0 || args[i + 1].find('-') == 0)) {
                output = args[i + 1];
            } else {
                help();
                std::cout << "\nAfter " << args[i] << " you need to specify file before using any other options.\n";
                return -1;
            }
        }
    }
    for (int i = 0; i < args.size(); ++i) {
        if (i != 0) {
            if (args[i] == "-n" || args[i] == "--newlines") {
                line_amount(file, output);
            } else if (args[i] == "-d" || args[i] == "--digits") {
                digit_amount(file, output);
            } else if (args[i] == "-dd" || args[i] == "--numbers") {
                number_amount(file, output);
            } else if (args[i] == "-c" || args[i] == "--chars") {
                char_amount(file, output);
            } else if (args[i] == "-a" || args[i] == "--anagrams") {
                std::vector<std::string> words_to_find;
                bool skip = false;
                for (int j = i; j < args.size(); ++j) {
                    if (args[j] == "-p" || args[j] == "--palindromes" || args[j] == "-o" ||
                        args[j] == "--output") {
                        skip = true;
                    } else if (!(args[j].find("--") == 0 || args[j].find('-') == 0) && !skip) {
                        words_to_find.push_back(args[j]);
                    }
                }
                find_anagrams(file, words_to_find, output);
                return 0;
            } else if (args[i] == "-p" || args[i] == "--palindromes") {
                std::vector<std::string> words_to_find;
                bool skip = false;
                for (int j = i; j < args.size(); ++j) {
                    if (args[j] == "-a" || args[j] == "--anagrams" || args[j] == "-o" ||
                        args[j] == "--output") {
                        skip = true;
                    } else if (!(args[j].find("--") == 0 || args[j].find('-') == 0) && !skip) {
                        words_to_find.push_back(args[j]);
                    }
                }
                find_palindrome(file, words_to_find, output);
                return 0;
            } else if (args[i] == "-s" || args[i] == "--sorted") {
                sort_alphabetically(file, output);
            } else if (args[i] == "-rs" || args[i] == "--reverse-sorted") {
                sort_reverse_alphabetically(file, output);
            } else if (args[i] == "-o" || args[i] == "--output") {
                ++i;
            } else {
                help();
                if (!(args[i] == "-i" || args[i] == "--input")) {
                    std::cout << "\nParameter " << args[i] << " has not been recognised\n"
                                                              "Please refer to the help above.\n";
                } else {
                    std::cout << "\nParameter " << args[i] << " should be the only one provided.\n"
                                                              "Please refer to the help above.\n";
                }
                return -1;
            }
        } else {
            if (args[i] == "--help") {
                help();
                return 0;
            } else if (args[i] == "-f" || args[i] == "--file") {
                if (std::ifstream(args[i + 1]).good()) {
                    if (std::regex_match(args[i + 1], std::regex(R"(^[C-Z]:[\\\w\-.]*.txt$)")) ||
                        std::regex_match(args[i + 1], std::regex("^[\\w\\-]*.txt$"))) {
                        file = args[i + 1];
                        ++i;
                    } else {
                        std::cout << "File to be analyzed needs to have .txt extension.\n";
                        return -1;
                    }
                } else {
                    std::cout << "\nCannot find the file in specified path.\n"
                                 "Check if file path is correct and try again.\n";
                    return -1;
                }
            } else {
                help();
                std::cout << "\nParameter " << args[i]
                          << " has not been recognised or should be provided later\n"
                             "You should start with -f/--file or -i/--input.\n";
                return -1;
            }
        }
    }
    return 0;
}
