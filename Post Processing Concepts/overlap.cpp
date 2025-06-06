#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iomanip>

int main() {
    // Define the minimum and maximum expected file number range
    const int MIN_NUM = 12814;
    const int MAX_NUM = 19585;
    const int RANGE = 32;

    // Loop through all possible filenames
    for (int i = MIN_NUM; i <= MAX_NUM; ++i) {
        std::string filename = "chi1k" + std::to_string(i) + ".out";
        std::ifstream file(filename);
        if (!file.is_open()) {
            // Handle missing file gracefully
            std::cerr << "Failed to open file: " << filename << std::endl;
            continue;
        }

        // Use a set to store unique numbers
        std::set<int> unique_numbers;
        std::string line;
        
        // Read each line and extract the first number
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int number;
            if (iss >> number) {
                unique_numbers.insert(number);
            }
        }
        
        file.close();

        // Prepare to write to the output file
        std::string output_filename = "chi1k" + std::to_string(i) + "_delete.out";
        std::ofstream outfile(output_filename);

        // Check for pairs of numbers that meet the criteria
        std::vector<int> numbers(unique_numbers.begin(), unique_numbers.end());
        for (size_t j = 0; j < numbers.size(); ++j) {
            for (size_t k = j + 1; k < numbers.size(); ++k) {
                int diff = numbers[k] - numbers[j];
                if (diff < RANGE && diff > 1) {
                    outfile << numbers[j] << std::endl << numbers[k] << std::endl;
                }
            }
        }

        outfile.close();
    }

    return 0;
}
