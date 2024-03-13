#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "utility.hpp"  
using namespace std;

int main(int argc, char* argv[]) {
    // Vector to store entered numbers
    vector<double> nlist;
    // Find the filename from the command line arguments
    string filename{ find_filename(argv, argc) };
    // Check if the user wants to skip bad input
    bool skipbad{ cmd_arg_check_range(argv, argc, "--skipbad") };

    // Display help message and exit if "--help" is present in command line arguments
    if (cmd_arg_check_range(argv, argc, "--help")) {
        display_help(cmd_arg_check_range(argv, argc, "--help"));
        return 0;
    }

    // Display version information and exit if "--version" is present in command line arguments
    if (cmd_arg_check_range(argv, argc, "--version")) {
        display_version(cmd_arg_check_range(argv, argc, "--version"));
        return 0;
    }

    // If a filename is provided
    if (filename != "CNF") {
        double n{};
        ifstream filein(filename);

        // Check if the file is successfully opened
        if (!filein.is_open()) {
            cerr << "Error: Unable to locate or open file " << filename << endl;
            exit(1);
        }

        // Read numbers from the file and populate the vector
        while (filein >> n) {
            if (filein.fail()) exit(1);
            if (n < 1) continue;
            nlist.push_back(n);
        }

        filein.close();  // Close the file
        nlist.shrink_to_fit();  // Reduce the vector's capacity to fit its size

        // If the vector is empty, display a message and exit
        if (nlist.empty()) {
            cout << "Data set is empty!" << endl;
            exit(0);
        }
    }
    else {
        // Display information about the program
        cout << "       Newcomb - Benford Stats " << endl;

        // Display a horizontal line based on whether "--fancy" is present or not
        if (cmd_arg_check_range(argv, argc, "--fancy"))
            cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << endl;
        else
            cout << "===================================================================" << endl;

        // Display instructions for entering numbers
        cout << "Enter white-space separated real numbers. Terminate input with ^Z" << endl;
        cout << endl;

        string input{};
        while (cin >> input && !cin.eof()) {
            double n{};
            try {
                if (cin.eof()) break;  // Exit the loop if end-of-file is reached
                n = stod(input);

                // Check for infinite numbers
                if (isinf(n)) {
                    cout << "Infinite number detected on " << input << endl;
                    continue;
                }

                // Check for overflow
                if (n > std::numeric_limits<double>::max()) {
                    cout << "ERROR: Overflow detected on < " << input << " >" << endl;
                    if (skipbad == false) return 1;
                    else continue;
                }

                // Skip numbers less than 1
                if (n <= 0) continue;

                // Add valid numbers to the vector
                nlist.push_back(n);
            }
            catch (const invalid_argument& e) {
                cout << "Invalid Input < " << input << " > has been rejected" << endl;
                if (skipbad == false) return 1;
            }
        }
    }

    // Create a format object and print the format based on the "--fancy" flag
    format format(nlist);
    format.print_format(cmd_arg_check_range(argv, argc, "--fancy"));
    return 0;
}
