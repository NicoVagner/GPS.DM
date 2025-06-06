#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

const int MAX_NUM = 19585; // Change this to the maximum value of <NUM>

int main() {
    for (int i = 12814; i <= MAX_NUM; ++i) {
        std::string filename = "chi1k" + std::to_string(i) + ".out";
        std::ifstream infile(filename);
        std::ofstream outfile("chi1k" + std::to_string(i) + "_delete.out");

        if (!infile) {
            std::cerr << "Error: Unable to open input file " << filename << std::endl;
            continue;
        }

        if (!outfile) {
            std::cerr << "Error: Unable to create output file chi1k" << i << "_delete.out" << std::endl;
            infile.close();
            continue;
        }

        std::string line;
        while (std::getline(infile, line)) {
            double val1, val2, val3, val4, val6, val8, val9, val10, val11;
            std::string val5, val7;

            std::istringstream iss(line);
            if (!(iss >> val1 >> val2 >> val3 >> val4 >> val5 >> val6 >> val7 >> val8 >> val9 >> val10 >> val11)) {
                std::cerr << "Error: Invalid format in line: " << line << std::endl;
                continue;
            }

            if (fabs(val3) < 6.15) {
                outfile << val1 << " " << val4 << " " << val11 << std::endl;
            }
        }

        infile.close();
        outfile.close();
    }

    return 0;
}