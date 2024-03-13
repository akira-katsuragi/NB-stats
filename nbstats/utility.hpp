#pragma once

#include <vector>
#include <string>
using namespace std;

// Function to get the first digit of a double
int getFirstDigit(double);

// Function to find the filename from command line arguments
string find_filename(const char* const [], int);

// Function to check the presence of a command line argument within a specified range
bool cmd_arg_check_range(const char* const [], int, const std::string&);

// Function to create a string of bars based on the input value and a flag for styling
string bars(double, bool);

// Function to display help information based on a boolean flag
void display_help(bool);

// Function to display version information based on a boolean flag
void display_version(bool);

// Class to perform various statistical and Newcomb-Benford's analyses and format printing
class format {
    vector<double> numlist;  // Vector to store the input numbers
    size_t numelements{ 0 };  // Number of elements in the vector
    double min{ 0 }, max{ 0 }, mean{ 0 }, median{ 0 }, variance{ 0 }, std_deviation{ 0 };  // Statistical measures
    string mode{ NULL };  // Mode of the input numbers
    double NB_variance{ 0 }, NB_deviation{ 0 };  // Newcomb-Benford's statistics

public:
    // Constructor to initialize the format object with a vector of numbers
    format(const vector<double>&);

    // Function to perform standard statistical analysis based on a boolean flag
    void std_analysis(bool) const;

    // Function to perform Newcomb-Benford's analysis based on a boolean flag
    void NewcombBenfords_analysis(bool);

    // Function to print the formatted analysis results based on a boolean flag
    void print_format(bool);
};
