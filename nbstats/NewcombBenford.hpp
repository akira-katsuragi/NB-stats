#pragma once

#include <string>
#include <vector>
#include <array>

using namespace std;

// Structure to encapsulate Newcomb-Benford analysis functions
struct NewcombBenford {
    // Function to calculate the raw frequency of a specific first digit in a vector
    int raw_frequency(const vector<double>&, int);

    // Function to calculate the actual frequency of a specific first digit in a vector
    double actual_frequency(const vector<double>&, int);

    // Function to calculate the expected frequency of the first digit
    double expected_frequency(int);

    // Function to calculate the Newcomb-Benford variance of a vector
    double NB_variance(const vector<double>&);

    // Function to calculate the Newcomb-Benford standard deviation of a vector
    double NB_Deviation(const vector<double>&);

    // Function to perform relationship analysis based on Newcomb-Benford deviation
    string relationship_analysis(const vector<double>&);
};
