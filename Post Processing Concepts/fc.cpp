#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>

//Bounds

const int START = 12814;
const int END = 19585;
const int ARRAY_SIZE = END - START + 1;

// Function to read chihit files and store values from the forth column
void readChihitFiles(const std::string& folderPath, double chihitValues[][3]) {
    std::ifstream inFile;
    std::string line;

    for (int i = START; i <= END; ++i) {
        std::string filePath = folderPath + "/chihit" + std::to_string(i) + ".out";
        inFile.open(filePath);
        if (inFile.is_open()) {
            while (std::getline(inFile, line)) {
                //I have no idea what this line does but it doesn't work without it. Cortesy of StackOverflow
                std::istringstream iss(line);
                int key;
                double value;
                if (iss >> key >> value >> value >> value) {
                    chihitValues[i - START][0] = key;
                    chihitValues[i - START][1] = value;
                }
            }
            inFile.close();
        }
    }
}

//Update chi1k files with values from chihit files
void updateChi1kFiles(const std::string& chihitFolderPath, const std::string& chi1kFolderPath, const double chihitValues[][3]) {
    for (int i = START; i <= END; ++i) {
        std::string chihitFilePath = chihitFolderPath + "/chihit" + std::to_string(i) + ".out";
        std::string chi1kFilePath = chi1kFolderPath + "/chi1k" + std::to_string(i) + ".out";
        std::ifstream chi1kFile(chi1kFilePath);
        if (chi1kFile) {
            std::ofstream outFile(chi1kFilePath + ".tmp");
            //More black magic
            std::string line;
            while (std::getline(chi1kFile, line)) {
                int key;
                if (std::istringstream(line) >> key) {
                    double chihitValue = chihitValues[i - START][1];
                    line += " " + std::to_string(chihitValue);
                }
                outFile << line << '\n';
            }
            chi1kFile.close();
            outFile.close();
            std::remove(chi1kFilePath.c_str());
            std::rename((chi1kFilePath + ".tmp").c_str(), chi1kFilePath.c_str());
        }
    }
}

int main() {
    std::string chihitFolderPath = "results2";
    std::string chi1kFolderPath = "results3";

    // Initialize array for chihit values
    double chihitValues[ARRAY_SIZE][3];

    // Read values from chihit files
    readChihitFiles(chihitFolderPath, chihitValues);

    // Update chi1k files with values from chihit files
    updateChi1kFiles(chihitFolderPath, chi1kFolderPath, chihitValues);

    std::cout << "Files updated successfully." << std::endl;
    return 0;
}
