#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

const int START = 0;
const int END = 6771;

// Function to read chihit files and store values from the forth column
std::unordered_map<int, double> readChihitFiles(const std::string& folderPath) {
    std::unordered_map<int, double> resultMap;
    std::ifstream inFile;
    std::string line;

    for (int i = START; i <= END; ++i) {
        std::string filePath = folderPath + "/chihit" + std::to_string(i+12814) + ".out";
        inFile.open(filePath);
        if (inFile.is_open()) {
            while (std::getline(inFile, line)) {
                std::istringstream iss(line);
                int key;
                double value;
                if (iss >> key >> value >> value >> value) {
                    resultMap[key] = value;
                }
            }
            inFile.close();
        }
    }
    return resultMap;
}

// Function to update chi1k files with values from chihit files
void updateChi1kFiles(const std::string& chihitFolderPath, const std::string& chi1kFolderPath, const std::unordered_map<int, double>& chihitValues) {
    for (int i = START; i <= END; ++i) {
        std::string chihitFilePath = chihitFolderPath + "/chihit" + std::to_string(i+12814) + ".out";
        std::string chi1kFilePath = chi1kFolderPath + "/chi1k" + std::to_string(i+12814) + ".out";
        std::ifstream chihitFile(chihitFilePath);
        std::ifstream chi1kFile(chi1kFilePath);
        if (chihitFile && chi1kFile) {
            std::ofstream outFile(chi1kFilePath + ".tmp");
            std::string line;
            while (std::getline(chi1kFile, line)) {
                int key;
                if (std::istringstream(line) >> key) {
                    auto it = chihitValues.find(key);
                    if (it != chihitValues.end()) {
                        std::string chihitValue = std::to_string(it->second);
                        line += " " + chihitValue;
                    }
                }
                outFile << line << '\n';
            }
            chihitFile.close();
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

    // Read values from chihit files
    std::unordered_map<int, double> chihitValues = readChihitFiles(chihitFolderPath);

    // Update chi1k files with values from chihit files
    updateChi1kFiles(chihitFolderPath, chi1kFolderPath, chihitValues);

    std::cout << "Files updated successfully." << std::endl;
    return 0;
}
