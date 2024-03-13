
# NB-Stats

NB-stats is a statistical analysis tool designed to analyze numerical data and perform Newcomb-Benford's Law analysis. It provides various statistical measures such as mean, median, mode, variance, and standard deviation, along with an analysis of the conformity of the data to Benford's Law.


## Features

- Standard statistical analysis including mean, median, mode, variance, and standard deviation.
- Newcomb-Benford's Law analysis to check the conformity of data with the expected      distribution of first digits.
- Command-line interface for easy input and analysis.
- Support for reading data from files or entering data interactively.


## Usage
Command Line Arguments.

The program accepts the following command-line arguments:

- --help: Displays instructions.
- --fancy: Enables fancy formatting in the output.
- --skipbad: Skips bad input values.
- --version: Displays the version number.

### Input Data
Data can be provided in two ways:

- From File: Provide a filename as a command-line argument. The program will read the data from the specified file.
- Interactive Input: If no filename is provided, the program will prompt you to enter data manually.

### Output
The program outputs the following information:

#### Standard Analysis:

- Number of elements.
- Range (minimum and maximum values).
- Arithmetic mean.
- Arithmetic median.
- Variance.
- Standard deviation.
- Mode.
- Frequency Table:

Frequency of each first digit (1 to 9) according to Newcomb-Benford's Law.

#### Newcomb-Benford's Law Analysis:

- Expected frequency of each first digit.
- Actual frequency of each first digit in the data.
- Variance from the expected distribution.
- Standard deviation of the distribution.
- Relationship analysis indicating the conformity of the data to Benford's Law.

### Examples
#### Reading from File:  
`./nbstats --fancy data.txt`


#### Interactive Input:
`./nbstats --skipbad`

## License

©(2024) Garth Santor, Liane Wong, and Janice Manning

NB-stats was created based on the ideas and concepts originally developed by Garth Santor, Liane Wong, and Janice Manning as a college project.




