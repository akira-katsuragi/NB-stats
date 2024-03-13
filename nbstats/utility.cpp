#include <iostream>
#include <algorithm>
#include <iomanip>
#include "utility.hpp"
#include "statistics.hpp"
#include "NewcombBenford.hpp"

using namespace std;
// Function to check if a specific string exists in the command-line arguments
// Returns true if found, otherwise false
bool cmd_arg_check_range(const char* const argv[], int argc, const std::string& str) {
    for (int i = 0; i < argc; ++i) {
        // Using strcmp to compare C-style strings
        if (strcmp(argv[i], str.c_str()) == 0) {
            return true;
        }
    }
    return false;
}
// Function to find the filename in command-line arguments
// Skips the executable name (e.g., "nbstats.exe") and returns the first non-option argument
// If no filename is found, returns the default "CNF"
string find_filename(const char* const argv[], int argc) {
    for (int i = 1; i < argc; ++i) {
        // Skip the executable name
        if (argv[i] == "nbstats.exe")continue;
        // Check if the argument is not an option (doesn't start with '--')
        if (argv[i][0] != '-' && argv[i][1] != '-') return argv[i];
    }
    // Default filename if none is found
    return "CNF";
}// Function to extract the first digit of a double number
int getFirstDigit(double num)
{
	while (num >= 10)num /= 10;
	return (int)num;
}
// Function to display help information based on the 'help' flag
void display_help(bool help)
{
    if (help) {
        cout << "usage: "<< " stats[--(help | fancy | skipbad | version)] * [filename]" << endl;
          

        cout << setw(45)<<"--help          display instructions" << endl;
        cout << setw(62)<<"--fancy         use codepage 850 characters in output" << endl;
        cout << setw(46)<<"--skipbad       skip bad input values" << endl;
        cout << setw(44)<<"--version       show version number" << endl;
        cout << endl;
    }
}
// Function to display the version information based on the 'version' flag
void display_version(bool version)
{
    if (version)cout << "2024.0.0" << endl;
}
// Function to generate a string of bars based on the value 'm' and whether to use 'fancy' characters
string bars(double m, bool fancy) {
    m = int(m);
    // Initialize the string with a default character based on the 'fancy' flag
    string bars{ (fancy) ? "³" : "|" };
    // Append additional characters based on the integer value of 'm'
    for (int i = 0; i < m; i++)(fancy) ? bars += "þ" : bars += "#";
    return bars;
}
// Create instances of the statistics and NewcombBenford classes for analysis
statistics stats;
NewcombBenford NB;
// Constructor for the 'format' class, performs statistical analysis on the input vector 'v'
format::format(const vector<double>& v) :numlist(v){
    // Sort the input vector in ascending order
    sort(numlist.begin(), numlist.end());
    // Initialize various statistical properties of the data
    numelements = numlist.size();
    min = stats.minvalue(numlist);
    max = stats.maxvalue(numlist);
    mean = stats.mean(numlist);
    median = stats.median(numlist);
    variance = stats.variance(numlist);
    std_deviation = stats.standard_deviation(numlist);
    mode = stats.mode(numlist);
    // Perform Newcomb-Benford's analysis
    NB_variance = NB.NB_variance(numlist);
    NB_deviation = NB.NB_Deviation(numlist);
}
// Function to display standard statistical analysis, with optional fancy formatting
void format::std_analysis(bool fancy) const {
    // If the number of any frequencies exceeds 50, the graph needs to be outputted from 0 - 100,
    // if it's less than 50, output from 0 - 50
	cout << "       Standard Analysis" << endl;
    // Display a fancy or standard separator based on the 'fancy' flag
    if (fancy)cout<< "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << endl;
    else      cout<< "=================================" << endl;
    // Display basic statistical properties
    cout << "# elements         = " << numelements << endl;
    cout << "Range              = [" << min << "..." << max << "]" << endl;
    cout << "Arithmetic mean    = " << mean << endl;
    cout << "Arithmetic median  = " << median << endl;
    cout << "Variance           = " << variance << endl;
    cout << "Standard Deviation = " << std_deviation << endl;
    cout << "Mode               = " << mode << endl;
    cout << endl;
    // Display frequency table
    cout << "Frequency Table : ";
    cout << " [" << 1 << "] = " << NB.raw_frequency(numlist, 1) << endl;
    for (int i = 2; i < 10; i++)cout<< setw(20) << "[" << i << "] = " << NB.raw_frequency(numlist, i) << endl;
   
}
// Function to display Newcomb-Benford's Law Analysis
void format:: NewcombBenfords_analysis(bool fancy) {
    // Check if any frequencies exceed 50 to determine the length of the graph
    bool hunderds{ false }; for (int i = 0; i < 10; i++) if (NB.actual_frequency(numlist, i) > 50) hunderds = true;
    int length{ (hunderds) ? 100 : 50 };// Set the length of the graph based on the frequencies

    // Display Newcomb-Benford's Law Analysis
    cout << "       Newcomb-Benford's Law Analysis" << std::endl;
    // Output the header based on the length of the graph
    if (fancy) {
        if (hunderds) {
            cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << endl;
            cout << "exp    dig   freq    0         10        20        30        40        50         60        70        80        90        100" << endl;
            cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << endl;
            cout << "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ ÚÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÄ" << endl;
            cout << fixed << setprecision(2);
            for (int i = 1; i < 10; i++) cout << setw(5) << NB.expected_frequency(i) << "%" << " [" << i << "] = " << setw(5) << NB.actual_frequency(numlist, i) << "%  " << bars(NB.actual_frequency(numlist, i), fancy) << endl;
            cout << "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ ÀÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÄ" << endl;
            cout << fixed << setprecision(5);
            cout << "Variance = " << NB_variance << "%" << endl;
            cout << "Std. Dev = " << NB_deviation << "%" << endl;
            cout << NB.relationship_analysis(numlist) << endl;
            cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << endl;
        }
        else {
            cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << endl;
            cout << "exp    dig   freq    0         10        20        30        40        50" << endl;
            cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << endl;
            cout << "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ ÚÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÂÄ" << endl;
            cout << fixed << setprecision(2);
            for (int i = 1; i < 10; i++) cout << setw(5) << NB.expected_frequency(i) << "%" << " [" << i << "] = " << setw(5) << NB.actual_frequency(numlist, i) << "%  " << bars(NB.actual_frequency(numlist, i), fancy) << endl;
            cout << "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ ÀÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÁÄ" << endl;
            cout << fixed << setprecision(5);
            cout << "Variance = " << NB_variance << "%" << endl;
            cout<< "Std. Dev = " << NB_deviation << "%" << endl;
            cout << NB.relationship_analysis(numlist) << endl;
            cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << endl;
        }
    }
    else {
        if (hunderds) {
            cout << "=============================================================================================================================" << endl;
            cout << "exp    dig   freq    0         10        20        30        40        50         60        70        80        90        100" << endl;
            cout << "-------------------- +---------+---------+---------+---------+---------+----------+---------+---------+---------+---------+--" << endl;
            cout << fixed << setprecision(2);
            for (int i = 1; i < 10; i++) cout << setw(5) << NB.expected_frequency(i) << "%" << " [" << i << "] = " << setw(5) << NB.actual_frequency(numlist, i) << "%  " << bars(NB.actual_frequency(numlist, i), fancy) << endl;
            cout << "-------------------- +---------+---------+---------+---------+---------+----------+---------+---------+---------+---------+--" << endl;
            cout << fixed << setprecision(5);
            cout << "Variance = " << NB_variance << "%" << endl;
            cout << "Std. Dev = " << NB_deviation << "%" << endl;
            cout << NB.relationship_analysis(numlist) << endl;
            cout << "=============================================================================================================================" << endl;
        }
        else {
            cout << "=========================================================================" << endl;
            cout << "exp    dig   freq    0         10        20        30        40        50" << endl;
            cout << "-------------------- +---------+---------+---------+---------+---------+-" << endl;
            cout << fixed << setprecision(2);
            for (int i = 1; i < 10; i++) cout << setw(5) << NB.expected_frequency(i) << "%" << " [" << i << "] = " << setw(5) << NB.actual_frequency(numlist, i) << "%  " << bars(NB.actual_frequency(numlist, i), fancy) << endl;
            cout << "-------------------- +---------+---------+---------+---------+---------+-" << endl;
            cout << fixed << setprecision(5);
            cout << "Variance = " << NB_variance << "%" << endl;
            cout << "Std. Dev = " << NB_deviation << "%" << endl;
            cout << NB.relationship_analysis(numlist) << endl;
            cout << "=========================================================================" << endl;
        }
    }


}
// Function to print the formatted statistical analysis and Newcomb-Benford's analysis
void format::print_format(bool fancy) {
    // Display standard statistical analysis
	std_analysis(fancy);
    // Display Newcomb-Benford's analysis
    cout << endl;
    NewcombBenfords_analysis(fancy);
}