#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

double min_max_scaling(double x, double x_min, double x_max, double x_newmin, double x_newmax) {
    return ((x - x_min) / (x_max - x_min)) * (x_newmax - x_newmin) + x_newmin;
}

int main() {
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");

    vector<double> data;
    double value;

    while (input_file >> value) {
        data.push_back(value);
    }

    double x_min = *min_element(data.begin(), data.end());
    double x_max = *max_element(data.begin(), data.end());

    double x_newmin = 1.0; 
    double x_newmax = 10.0; 

    for (const double &x : data) {
        double normalized_value = min_max_scaling(x, x_min, x_max, x_newmin, x_newmax);
        output_file << normalized_value << endl;
    }

    input_file.close();
    output_file.close();

    cout << "output is generated in output_minmax file" << endl;

    return 0;
}
