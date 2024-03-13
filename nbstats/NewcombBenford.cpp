#include <cmath>
#include <array>
#include "NewcombBenford.hpp"
#include "utility.hpp"
// Function to calculate the expected frequency of the first digit
double NewcombBenford::expected_frequency(int d) {
	return (log10(1.0 + (1.0 / d))) * 100.0;
}
// Function to calculate the raw frequency of a specific first digit in a vector
int NewcombBenford::raw_frequency(const vector<double>& vec, int n) {
	int F{ 0 };
	for (int i = 0; i < vec.size(); i++) {
		if (n == getFirstDigit(vec[i]))F++;
	}
	return F;
}
// Function to calculate the actual frequency of a specific first digit in a vector
double NewcombBenford::actual_frequency(const vector<double>& vec, int num)
{
	return (raw_frequency(vec, num) / (double)vec.size()) * 100;
}
// Function to calculate the Newcomb-Benford variance of a vector
double NewcombBenford::NB_variance(const vector<double>& vec)
{	
	double variance{ 0.0 };
	for (int d = 1; d < 10; d++)
	{
		double AF{ actual_frequency(vec, d) }, EXPF{ expected_frequency(d)};
		variance += pow(AF / EXPF - 1, 2);
	}
	return (variance / 9) * 100;
}
// Function to calculate the Newcomb-Benford standard deviation of a vector
double NewcombBenford::NB_Deviation(const vector<double>& vec)
{
	return sqrt(NB_variance(vec)) * 10;
}
// Function to perform relationship analysis based on Newcomb-Benford deviation
string NewcombBenford::relationship_analysis(const vector<double>& vec)
{
	double NBdev{NB_Deviation(vec) / 100};
	string R{};
	if (NBdev >= 0 && NBdev < 0.1) R = "a very strong";
	else if (NBdev >= 0.1 && NBdev < 0.2) R = "a strong";
	else if (NBdev >= 0.2 && NBdev < 0.35) R = "a moderate";
	else if (NBdev >= 0.35 && NBdev < 0.5) R = "a weak";
	else R = "not a";
	return "There is " + R + " Benford relationship.";
}
