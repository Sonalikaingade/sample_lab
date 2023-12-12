#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double z_score(double x, double mean, double std_dev) {
    return (x - mean) / std_dev;
}

int main() {
    ifstream input_file("input.txt");
    ofstream output_file("output_zscore.txt");

    vector<double> data;
    double value;

    while (input_file >> value) {
        data.push_back(value);
    }

    double sum = 0.0;
    for (const double &x : data) {
        sum += x;
    }
    double mean = sum / data.size();

    double squared_diff_sum = 0.0;
    for (const double &x : data) {
        squared_diff_sum += pow(x - mean, 2);
    }
    double std_dev = sqrt(squared_diff_sum / data.size());

    for (const double &x : data) {
        double normalized_value = z_score(x, mean, std_dev);
        output_file << normalized_value << endl;
    }

    input_file.close();
    output_file.close();

    cout << "output is generated in output_zscore file" << endl;

    return 0;
}
