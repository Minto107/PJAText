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
            ref = static_cast<char>(tolower(ref));
        for (auto &ref:y)
            ref = static_cast<char>(tolower(ref));
        return x < y;
    }
} alphabetical_order;

/**
 * @brief Reads words from file to a std::vector of std::string's.
 * @param file Specifies the file that will be read.
 * @return Returns vector containing words from a specified file.
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
 * @param file specifies the file that will be read.
 * @param output (optional) specifies file that result will be written to.
 */

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

/**
 * @brief Function counts numbers in a file
 * @param file specifies the file that will be read
 * @param output (optional) specifies file that result will be written to
 */

void number_amount(const std::string &file, const std::string &output = "") {
    std::fstream input_file(file);
    std::regex expr("^[-]?[\\s]?[0-9]*[.]?[0-9]*$");
    int counter = 0;
    for (std::string line; std::getline(input_file, line);) {
        std::stringstream stream(line);
        for (std::string s; stream >> s;) {
            if (std::regex_match(s, expr)) {
                if (s == "-") {
                    --counter;
                }
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

/**
 * Function counts digit in a file
 * @param file specifies the file that will be read
 * @param output (optional) specifies file that result will be written to
 */

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

/**
 * Function counts every character in a file including whitespaces
 * @param file specifies the file that will be read
 * @param output (optional) specifies file that result will be written to
 */

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
            counter += word.size();
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
 * Function finds anagrams specified by anagrams_to_find in file
 * @param file specifies the file that will be read
 * @param anagrams_to_find vector containing std::string, vector contents will be checked if anagrams for these words exist
 * @param output (optional) specifies file that result will be written to
 */

void find_anagrams(const std::string &file, const std::vector<std::string> &anagrams_to_find,
                   const std::string &output = "") {
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

/**
 * Function finds palindromes specified by palindromes in a file
 * @param file specifies the file that will be read
 * @param palindromes vector containing std::string, vector contents will be checked if palindromes for these words exist
 * @param output (optional) specifies file that result will be written to
 */

void
find_palindrome(const std::string &file, std::vector<std::string> &palindromes, const std::string &output = "") {
    for (int i = 0; i < palindromes.size(); ++i) {
        std::string tmp = palindromes.at(i);
        std::reverse(tmp.begin(), tmp.end());
        if (tmp != palindromes.at(i)) {
            palindromes.erase(palindromes.begin() + i);
        }
    }
    for (const auto &palindrome : palindromes) {
        std::fstream input_file(file);
        if (output.empty() || output == " ") {
            std::cout << "Palindrome count for word " << palindrome << ": ";
        } else {
            std::ofstream os;
            os.open(output, std::ios_base::app);
            os << "Palindrome count for word " << palindrome << ": ";
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

/**
 * @brief Function sorts file in alphabetical order
 * @param file specifies the file that will be read
 * @param output (optional) specifies file that result will be written to
 */

void sort_alphabetically(const std::string &file, const std::string &output = "") {
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
    if (!(output.empty() || output == " ")) {
        for (const auto &i : sorted) {
            std::ofstream os;
            os.open(output, std::ios_base::app);
            os << i << ' ';
            os.close();
        }
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << '\n';
        os.close();
    } else {
        print_vector(sorted);
    }
}

/**
 * @brief Function sorts file in reverse alphabetical order
 * @param file specifies the file that will be read
 * @param output (optional) specifies file that result will be written to
 */

void sort_reverse_alphabetically(const std::string &file, const std::string &output = "") {
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
    if (!(output.empty() || output == " ")) {
        for (const auto &i : sorted) {
            std::ofstream os;
            os.open(output, std::ios_base::app);
            os << i << ' ';
            os.close();
        }
        std::ofstream os;
        os.open(output, std::ios_base::app);
        os << '\n';
        os.close();
    } else {
        print_vector(sorted);
    }
}

/**
 * @brief displays help
 */

void help() {
    std::ifstream input_file(R"(C:\Users\minto.MSI-B450TM\CLionProjects\PJAText\help.txt)");
    for (std::string line; getline(input_file, line);) {
        std::cout << line << '\n';
    }
}

/**
 * @brief Function converts str from std::string and returns it as an Integer value
 * @param str std::string that needs to be converted into an Integer value
 * @param offset defaults to 0
 * @return Returns std::string as Integer value
 */

constexpr unsigned int string_to_int(const char *str, int offset = 0) {
    return str[offset] ? (string_to_int(str, offset + 1) * 33) ^ str[offset] : 5381;
}

/**
 * @brief Handles flags and parses parameters
 * @return Returns execution status code. 0 = execution was successful, -1 = means wrong or no flag were provided.
 */

int main(int argc, char **argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::string file;
    std::string output;
    std::vector<std::string> words_to_find;
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
                    if (std::regex_match(args[1], std::regex("^[\\d\\w]+[.]txt$"))) {
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
    bool skip = false;
    for (int i = 0; i < args.size(); ++i) {
        if (i != 0) {
            switch (string_to_int(args[i].data())) {
                case string_to_int("-n"):
                case string_to_int("--newlines"):
                    lines_amount(file, output);
                    break;
                case string_to_int("-d"):
                case string_to_int("--digits"):
                    digit_amount(file, output);
                    break;
                case string_to_int("-dd"):
                case string_to_int("--numbers"):
                    number_amount(file, output);
                    break;
                case string_to_int("-c"):
                case string_to_int("--chars"):
                    char_amount(file, output);
                    break;
                case string_to_int("-a"):
                case string_to_int("--words_to_find"):
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
                case string_to_int("-p"):
                case string_to_int("--palindromes"):
                    for (int j = i; j < args.size(); ++j) {
                        if (args[j] == "-a" || args[j] == "--words_to_find" || args[j] == "-o" ||
                            args[j] == "--output") {
                            skip = true;
                        } else if (!(args[j].find("--") == 0 || args[j].find('-') == 0) && !skip) {
                            words_to_find.push_back(args[j]);
                        }
                    }
                    find_palindrome(file, words_to_find, output);
                    return 0;
                case string_to_int("-s"):
                case string_to_int("--sorted"):
                    sort_alphabetically(file, output);
                    break;
                case string_to_int("-rs"):
                case string_to_int("--reverse-sorted"):
                    sort_reverse_alphabetically(file, output);
                    break;
                case string_to_int("-o"):
                case string_to_int("--output"):
                    ++i;
                    break;
                default:
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
            switch (string_to_int(args[i].data())) {
                case string_to_int("--help"):
                case string_to_int(""):
                    help();
                    return 0;
                case string_to_int("-f"):
                case string_to_int("--file"):
                    if (std::ifstream(args[i + 1]).good()) {
                        if (std::regex_match(args[i + 1], std::regex("^[\\d\\w]+[.]txt$"))) {
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
                    break;
                default:
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
