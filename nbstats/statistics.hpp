#pragma once

#include <vector>
#include <string>

using namespace std;

// Structure to encapsulate statistical analysis functions
struct statistics {
    // Function to calculate the minimum value in a vector
    double minvalue(const vector<double>&);

    // Function to calculate the maximum value in a vector
    double maxvalue(const vector<double>& vec);

    // Function to calculate the mean of a vector
    double mean(const vector<double>&);

    // Function to calculate the median of a vector
    double median(const vector<double>&);

    // Function to calculate the mode of a vector
    string mode(const vector<double>&);

    // Function to calculate the variance of a vector
    double variance(const vector<double>&);

    // Function to calculate the standard deviation of a vector
    double standard_deviation(const vector<double>&);
};
