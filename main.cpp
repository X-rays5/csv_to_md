#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>

// split string by token
std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

// read file into vector
std::vector<std::string> read_file(const std::string& filename) {
    std::vector<std::string> lines;
    std::string line;
    std::ifstream file(filename);
    if (file.is_open()) {
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

int main(int argc, char* argv[]) {
    // check if argv[1] is a file
    if (argc < 3 || !std::ifstream(argv[1]).good()) {
        std::cout << "Usage: " << argv[0] << " <filename> <delimiter>" << std::endl;
        return 1;
    }
    // check if argv[2] is a single char
    if (argc < 3 || strlen(argv[2]) != 1) {
        std::cout << "Usage: " << argv[0] << " <filename> <delimiter>" << std::endl;
        return 1;
    }

    // read argv[1] into a vector
    std::vector<std::string> lines = read_file(argv[1]);

    // split each line by argv[2] and put it into a 2 dimensional vector
    std::vector<std::vector<std::string>> tokens;
    for (auto line : lines) {
        tokens.push_back(split(line, argv[2][0]));
    }

    // convert the tokens vector to a markdown table in output.md
    std::ofstream out("output.md");
    bool first_line = true;
    for (auto&& line : tokens) {
        for (auto&& token : line) {
            // if token is empty, replace it with "-"
            if (token.empty()) {
                token = "-";
            }
            // trim spaces at front and back
            token.erase(0, token.find_first_not_of(' '));
            token.erase(token.find_last_not_of(' ') + 1);
            out << " " << token << " |";
        }
        out << std::endl;
        // after the first line print a line with dashes
        if (first_line) {
            first_line = false;
            if (tokens.begin() != tokens.end()) {
                for (int i = 0; i < line.size(); i++) {
                    out << " --- |";
                }
                out << std::endl;
            }
        }
    }
    out.close();
    return 0;
}
