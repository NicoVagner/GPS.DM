/*
    Created by Jiten Singh, 6/28/2022
*/

/*
    The goal of this program is to take each day's epochs,
    split the epochs into windows, select the highest |SNR|
    value per-window, and save to a file. 

    The file produced by this program is a list of "SNR-max" 
    values which can be compared to the underlying distribution.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

void get_FileList(std::string pathToFiles, std::vector<std::string>& chi2Files);
bool checkIfEmpty(std::string pathToFiles, std::string chi2File);
void get_chi2Data_rows(std::string pathToFiles, std::string chi2File, std::vector<std::string>& chi2Data);
std::vector<std::string> split(std::string s, std::string delimiter);
int findHighestInWindow(int firstEpochOfWindow, int lastEpochOfWindow, int numOfEpochs, int arrayPos, std::vector<int>& currentWindowEpochs, std::vector<double>& epoch_snr);
void recordAs_maxSNR_inWindow(std::string pathToFiles, std::string chihitFiles, std::string highestSNREpoch_string);

int main(){
    //  Specifying the directory of chi2_[gpsday].out files
    //  These files contain each epoch's SNR value per GPS Day

    std::string pathToFiles = "../SearchBackground_1/results3/"; //Directory of chi2 files
    //std::string pathToFiles = "testFiles_results3/"; //Directory of test chi2 files

    //  Creating a list of chi2 files based on specified directory
    std::vector<std::string> chi2Files;
    get_FileList(pathToFiles, chi2Files); //chi2Files now contains each chi2 file name

    //  Looping through chi2 file list to grab data, then analyze
    //  The integer "i" enumerates the chi2 files in the specified directory!
    //  Note: chi2Files.size() returns the number files in the directory
    for(int i = 0; i < chi2Files.size(); i++){
        //  To test a specific file, comment out the "for" loop and change the value of i:
        // int i = 0;

        //  Check to see if the file is empty. If not, analyze it.
        if(checkIfEmpty(pathToFiles, chi2Files[i]) == false){
            //  Grab each epoch's data (epoch number, SNR)
            std::vector<std::string> chi2Data;  //this will hold each epoch's data
            get_chi2Data_rows(pathToFiles, chi2Files[i], chi2Data);   //chi2Data now contains each epoch's data

            //  For each chi2 file, save each column to its own vector
            //  Note: chi2Data.size() returns the number of epochs in the current file
            std::vector<int> epochs(chi2Data.size());
            std::vector<double> epoch_snr(chi2Data.size());
            std::vector<double> epoch_chiSquare(chi2Data.size());
            std::vector<int> num_clocks(chi2Data.size());

            //  Save each epoch's information to its own vector
            //  the integer "j" enumerates each epoch of the current chi2 file!
            for(int j = 0; j < chi2Data.size(); j++){
                std::vector<std::string> split_chi2Data = split(chi2Data[j], " ");
                epochs[j] = std::stoi(split_chi2Data[0]);
                epoch_snr[j] = std::stod(split_chi2Data[1]);
                epoch_chiSquare[j] = std::stod(split_chi2Data[3]);
                num_clocks[j] = std::stoi(split_chi2Data[4]);
            }  

            //  Now...deal with the windows, and grab the highest |SNR| value
            //  Remember, a window is defined as [tw + tw+1) (notice the brackets)
            int firstEpochOfWindow = epochs[0];
            int lastEpochOfWindow = epochs[0] + 61;
            int currentEpoch = 0;
            int totalNumOfEpochs_so_far = 0;
            std::vector<int> currentWindowEpochs;
            std::vector<std::string> maxSNRs;

            //  This first "if" statement is just for safety.
            if(chi2Data.size() > 1){

                //  Determine the windows, then find max |SNR|
                //  Loop through each epoch to determine windows
                for(currentEpoch = 0; currentEpoch < chi2Data.size(); currentEpoch++){
                    totalNumOfEpochs_so_far = currentEpoch;

                    //  Check to see if we're in the same window still
                    if(epochs[currentEpoch] < lastEpochOfWindow){
                        //std::cout << "Epoch " << epochs[currentEpoch] << " is in the window from " << firstEpochOfWindow << " to " << lastEpochOfWindow << "\n";
                        currentWindowEpochs.push_back(epochs[currentEpoch]);
                    }

                    //  This indicates that we're at the last epoch of the current window 
                    if(epochs[currentEpoch] >= lastEpochOfWindow){

                        //  Determine the highest |SNR| value of the current window
                        int epochWithHighestSNR = findHighestInWindow(currentWindowEpochs.front(), currentWindowEpochs.back(), totalNumOfEpochs_so_far, currentEpoch, currentWindowEpochs, epoch_snr);
                        //std::cout << epochs[epochWithHighestSNR] << "\n\n";

                        //  Record this SNR value to a file for the current GPS Day
                        recordAs_maxSNR_inWindow(pathToFiles, chi2Files[i], chi2Data[epochWithHighestSNR]);
                        //std::cout << "The epoch with highest SNR is at epoch " << epochs[epochWithHighestSNR] << " with SNR: " << epoch_snr[epochWithHighestSNR] << "\n";

                        // Define the new window, clean-up 
                        firstEpochOfWindow = epochs[currentEpoch];
                        lastEpochOfWindow = epochs[currentEpoch] + 61;
                        currentWindowEpochs.clear();
                        //std::cout << "The new window boundary is: " << firstEpochOfWindow << " to " << lastEpochOfWindow << "\n";
                        //std::cout << "Epoch " << epochs[currentEpoch] << " is in the window from " << firstEpochOfWindow << " to " << lastEpochOfWindow << "\n";
                        currentWindowEpochs.push_back(epochs[currentEpoch]);
                    }

                    //  This "if" statement exists to check if we are about to hit the end of the file
                    if(currentEpoch + 1 == chi2Data.size()){
                        int epochWithHighestSNR = findHighestInWindow(currentWindowEpochs.front(), currentWindowEpochs.back(), totalNumOfEpochs_so_far+1, currentEpoch,currentWindowEpochs, epoch_snr);
                        recordAs_maxSNR_inWindow(pathToFiles, chi2Files[i], chi2Data[epochWithHighestSNR]);
                        //std::cout << "The epoch with highest SNR is at epoch " << epochs[epochWithHighestSNR] << " with SNR: " << epoch_snr[epochWithHighestSNR] << "\n";
                        currentWindowEpochs.clear();
                    }
                }
            }
            else{
                std::cout << "This file only has one epoch...? " << chi2Files[i] << "\n";
                //std::cout << "Epoch " << epochs[0] << " is in the window from " << firstEpochOfWindow << " to " << lastEpochOfWindow << "\n";
                recordAs_maxSNR_inWindow(pathToFiles, chi2Files[i], chi2Data[0]);
            }
        }
        else{
            std::cout << "\nThe file " << chi2Files[i] << " is empty!\n\n";
        }

    }

    return 0;
}

void get_FileList(std::string pathToFiles, std::vector<std::string>& chi2Files)
/*
    This function saves the list of chi2 files to a vector called chi2Files
*/
{
    //  Listing all the chi2 files in this directory
    std::string listFiles_string = "cd " + pathToFiles + ";" + " ls chi2_*.out >> /home/jitens/snr_max_determinations/currentDir_chi2_files.txt";
    const char *listFilesCommand = listFiles_string.c_str();
    system(listFilesCommand);

    //  Grabbing chi2 file list and saving it to the chi2Files vector
    int number_of_files = 0;
    std::string currentFile;
    std::ifstream currentDir_chi2_files("currentDir_chi2_files.txt");
    if(currentDir_chi2_files.is_open()){
        //  First: count the total number of files present
        while(std::getline(currentDir_chi2_files, currentFile)){
            ++number_of_files;
        }
        chi2Files.resize(number_of_files);
        currentDir_chi2_files.clear();
        currentDir_chi2_files.seekg(0);
    
        //  Grabbing each file's name, storing to chi2Files vector
        int currentFileNumber = 0;
        while(std::getline(currentDir_chi2_files, currentFile)){
            chi2Files[currentFileNumber] = currentFile;
            currentFileNumber++;
        }
        currentDir_chi2_files.close();
    }  
    else{
        std::cout << "Unable to open the list of chi2 files!\n"; 
    }

    //  Deleting the old list of chi2 files (this is just a list of files, temporary storage)
    std::string cleanup_currentDir_chi2_files_string = "rm currentDir_chi2_files.txt";
    const char *cleanup_currentDir_chi2_files_command = cleanup_currentDir_chi2_files_string.c_str();
    system(cleanup_currentDir_chi2_files_command);
}

bool checkIfEmpty(std::string pathToFiles, std::string chi2File)
/*
    Checks if the specified chi2File is empty 
    TRUE: File is empty
    FALSE: File is not empty
*/
{
    //  Open the file specified by chi2File
    std::string pathToChi2File_string = pathToFiles + chi2File;
    const char *pathToChi2File = pathToChi2File_string.c_str();
    std::ifstream currentFile (pathToChi2File);

    //  Check if the file is empty. Return bool
    if(currentFile.peek() == std::ifstream::traits_type::eof()){
        return true;
    }
    else{
        return false;
    }
}

void get_chi2Data_rows(std::string pathToFiles, std::string chi2File, std::vector<std::string>& chi2Data)
/*
    Opens the specified chi2File, saves each epoch's data to the vector chi2Data
*/
{
    //  Open the file specified
    std::string pathToChi2File_string = pathToFiles + chi2File;
    const char *pathToChi2File = pathToChi2File_string.c_str();
    int numberOfEpochs = 0;
    std::string currentEpoch;
    std::ifstream currentFile(pathToChi2File);
    if(currentFile.is_open()){
        //  Count the number of epochs present in the current file
        while(std::getline(currentFile, currentEpoch)){
            ++numberOfEpochs;
        }
        chi2Data.resize(numberOfEpochs);
        currentFile.clear();
        currentFile.seekg(0);

        //  Grab each epoch's information and save it to the vector chi2Data
        int i = 0;
        while(std::getline(currentFile, currentEpoch)){
            chi2Data[i] = currentEpoch;
            i++;
        }
        currentFile.close();
    }
    else{
        std::cout << "Unable to open the file: " << chi2File << " in directory: " << pathToFiles << "!\n";
    }
}

std::vector<std::string> split(std::string s, std::string delimiter)
/*
    Splits the string s based on the delimiter provided
*/
{   
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int findHighestInWindow(int firstEpochOfWindow, int lastEpochOfWindow, int numOfEpochs, int arrayPos, std::vector<int>& currentWindowEpochs, std::vector<double>& epoch_snr)
/*
    Loops through the window, compares each epoch's |SNR| values
    to find the highest one. Returns the array position of the 
    epoch with the highest |SNR| value
*/
{
    int currentPos = 0;
    int epochWithHighestSNR = 0;
    double highestSNR = 0.0;
    int lengthOfCurrentWindow = currentWindowEpochs.size();
    int i = numOfEpochs - lengthOfCurrentWindow;

    //  If, for some reason, there is only one epoch in this window,
    //  return it as the epoch with the highest |SNR|
    if(lengthOfCurrentWindow == 1){
        epochWithHighestSNR = i;
    }
    else{

        //  Loop through the epochs of this window, compare to highestSNR
        while(currentWindowEpochs[currentPos] < lastEpochOfWindow + 1 && currentPos < lengthOfCurrentWindow){
            if(fabs(epoch_snr[i]) >= fabs(highestSNR)){
                highestSNR = epoch_snr[i];
                epochWithHighestSNR = i;
            }
            i++;
            currentPos++;
        }
    }

    //std::cout << "The array. pos with the highest |SNR| is " << epochWithHighestSNR << "\n";

    return epochWithHighestSNR;
}

void recordAs_maxSNR_inWindow(std::string pathToFiles, std::string chihitFiles, std::string highestSNREpoch_string)
/*
    Saves the highest |SNR| to a file
*/
{
    std::vector<std::string> fileDir = split(pathToFiles, "/");
    std::string unfilteredEventFileName_string = "maxSNR_" + fileDir[1] + ".txt";
    const char *unfilteredEventFileName = unfilteredEventFileName_string.c_str();
    std::ofstream unfilteredEventsFile;
    unfilteredEventsFile.open(unfilteredEventFileName, std::ios_base::app);
    const char *highestSNREpoch = highestSNREpoch_string.c_str();
    std::string gpsDay = chihitFiles.substr(5,5);
    unfilteredEventsFile << gpsDay << "  " << highestSNREpoch << "\n";
}



