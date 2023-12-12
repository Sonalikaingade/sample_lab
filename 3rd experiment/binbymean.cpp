#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to perform binning by mean
void binByMean(const vector<double>& data, int numBins, const string& outputFilename) {
    int dataSize = data.size();

    // Calculate the mean of the data
    double sum = 0.0;
    for (const double& value : data) {
        sum += value;
    }
    double mean = sum / dataSize;

    // Sort the data
    vector<double> sortedData = data;
    sort(sortedData.begin(), sortedData.end());

    // Create bins
    vector<vector<double>> bins(numBins);
    for (const double& value : sortedData) {
        int binIndex = min(static_cast<int>(floor((value - mean) / (mean / numBins)) + numBins / 2), numBins - 1);
        bins[binIndex].push_back(value);
    }

    // Write binned data to output file
    ofstream outputFile(outputFilename);
    for (int i = 0; i < numBins; ++i) {
        outputFile << "Bin " << i + 1 << ": ";
        for (const double& value : bins[i]) {
            outputFile << value << " ";
        }
        outputFile << endl;
    }
    outputFile.close();

    cout << "Binning by mean completed and saved to '" << outputFilename << "'." << endl;
}

int main() {
    string inputFilename = "input.txt";
    string outputFilename = "output_binning_by_mean.txt";
    int numBins = 3;

    ifstream inputFile(inputFilename);
    vector<double> data;
    double value;

    while (inputFile >> value) {
        data.push_back(value);
    }
    inputFile.close();

    binByMean(data, numBins, outputFilename);

    return 0;
}
