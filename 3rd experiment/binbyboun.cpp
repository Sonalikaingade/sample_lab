#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to perform binning by boundary
void binByBoundary(const vector<double>& data, const vector<double>& boundaries, const string& outputFilename) {
    int dataSize = data.size();
    int numBoundaries = boundaries.size();

    // Sort the data
    vector<double> sortedData = data;
    sort(sortedData.begin(), sortedData.end());

    // Create bins
    vector<vector<double>> bins(numBoundaries + 1);
    int boundaryIndex = 0;
    for (const double& value : sortedData) {
        while (boundaryIndex < numBoundaries && value >= boundaries[boundaryIndex]) {
            boundaryIndex++;
        }
        bins[boundaryIndex].push_back(value);
    }

    // Write binned data to output file
    ofstream outputFile(outputFilename);
    for (int i = 0; i <= numBoundaries; ++i) {
        if (i == 0) {
            outputFile << "Bin Below " << boundaries[i] << ": ";
        } else if (i == numBoundaries) {
            outputFile << "Bin Above " << boundaries[i - 1] << ": ";
        } else {
            outputFile << "Bin " << i << ": ";
        }
        for (const double& value : bins[i]) {
            outputFile << value << " ";
        }
        outputFile << endl;
    }
    outputFile.close();

    cout << "Binning by boundary completed and saved to '" << outputFilename << "'." << endl;
}

int main() {
    string inputFilename = "input1.txt";
    string outputFilename = "output_binning_by_boundary.txt";

    // Define bin boundaries
    vector<double> boundaries = {40, 60, 80};  // You can adjust these boundaries

    ifstream inputFile(inputFilename);
    vector<double> data;
    double value;

    while (inputFile >> value) {
        data.push_back(value);
    }
    inputFile.close();

    binByBoundary(data, boundaries, outputFilename);

    return 0;
}
