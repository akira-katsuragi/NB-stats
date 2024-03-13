#include <cmath>
#include <iomanip>
#include <sstream>

#include "statistics.hpp"


// Function to find the minimum value in a vector of doubles using standard library min_element
double statistics::minvalue(const vector<double>& vec) {
    return *min_element(vec.begin(), vec.end());  // Return the minimum element in the vector
}
// Function to find the maximum value in a vector of doubles using standard library max_element
double statistics::maxvalue(const vector<double>& vec) {
    return *max_element(vec.begin(), vec.end());  // Return the maximum element in the vector
}
// Function to calculate the mean (average) of a vector of doubles
double statistics::mean(const vector<double>& vec) {
	double sum{ 0.0 };
	for (int i = 0; i < vec.size(); i++) sum += vec[i]; // Iterate through the vector and accumulate the sum of elements
	return sum / static_cast<int>(vec.size()); // Calculate the mean by dividing the sum by the number of elements
}
// Function to calculate the median of a vector of doubles
double statistics::median(const vector<double>& vec) {
	int size = static_cast<int>(vec.size());
	if (size % 2 != 0) return vec[size / 2];// Check if the size of the vector is odd or even
    else return (vec[static_cast<std::vector<double, std::allocator<double>>::size_type>(size / 2) - 1] + vec[size / 2]) / 2.0;// Calculate the median for an even-sized vector
}
// Function to calculate the variance of a vector of doubles
double statistics::variance(const vector<double>& vec) {
	double m{ mean(vec) }, sum{0.0};//were m is considered to be median :)
	int size{ static_cast<int>(vec.size()) };
    // Calculate the sum of squared differences from the mean
	for (int i = 0; i < size; i++) sum += pow((vec[i] - m), 2);
    // Return the variance
	return sum / size;
}
// Function to calculate the standard deviation of a vector of doubles
double statistics::standard_deviation(const vector<double>& vec) {
	return sqrt(variance(vec));// Return the square root of the variance
}
string statistics::mode(const vector<double>& vec) {
    // Track all modes and their frequencies
    vector<double> modes;
    vector<int> frequencies;
    // Handle initial element 
    int current_count = 1;
    // Iterate through the vector (starting from the second element)
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] == vec[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) - 1]) {
            current_count++;
        }
        else {
            // Update modes and frequencies if applicable
            if (current_count > (frequencies.empty() ? 0 : frequencies[0])) {
                modes.clear();
                frequencies.clear();
                modes.push_back(vec[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) - 1]);
                frequencies.push_back(current_count);
            }
            else if (current_count == (frequencies.empty() ? 0 : frequencies[0])) {
                modes.push_back(vec[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) - 1]);
                frequencies.push_back(current_count);
            }
            current_count = 1;
        }
    }
    // Handle last element (if it's a mode)
    if (current_count >= (frequencies.empty() ? 0 : frequencies[0])) {
        modes.push_back(vec.back());
        frequencies.push_back(current_count);
    }
    // Build the output string
    string result;
    if (modes.empty() || frequencies[0] == 1) {
        result = "No mode";
    }
    else {
        if (modes.size() == 1) {
            stringstream ss;
            ss << fixed << setprecision(1) << modes[0];
            result = "{ " + ss.str() + " }x" + to_string(frequencies[0]);
        }
        else {
            result = "Multimodal: { ";
            for (int i = 0; i < modes.size(); i++) {
                stringstream ss;
                ss << fixed << setprecision(1) << modes[i];
                result += ss.str();
                if (i != modes.size() - 1)  result += " , ";
            }
            result += " }x" + to_string(frequencies[0]);
        }
    }

    return result;
}

