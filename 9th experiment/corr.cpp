#include <iostream>
#include<fstream>
#include<sstream>
#include <cmath>
#include <vector>

using namespace std;

// Function to calculate mean of a vector
double mean(const vector<double>& data) {
    double sum = 0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

// Function to calculate standard deviation of a vector
double standardDeviation(const vector<double>& data) {
    double meanValue = mean(data);
    double sumSquaredDifferences = 0;

    for (double value : data) {
        sumSquaredDifferences += pow(value - meanValue, 2);
    }

    return sqrt(sumSquaredDifferences / (data.size() - 1));
}

// Function to calculate correlation coefficient
float correlationCoefficient(const vector<double>& a, const vector<double>& b,int n) {
    double meanA = mean(a);
    double meanB = mean(b);
    double sigmaA = standardDeviation(a);
    double sigmaB = standardDeviation(b);

    float numerator = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        numerator += (a[i] - meanA) * (b[i] - meanB);
    }

    return numerator / ((n-1)*(sigmaA * sigmaB));
}

int main() {
    // Example data
   vector<double>x;
   vector<double>y;

   ifstream input("input.csv");
   string line;
   while(getline(input, line)){
    stringstream str(line);
    string x_val, y_val;
     getline(str,x_val,',');
     getline(str,y_val);

    int a=stoi(x_val);
    int b=stoi(y_val);
     x.push_back(a);
     y.push_back(b);}

     int n = x.size();

    // Calculate correlation coefficient
    float gammaAB = correlationCoefficient(x,y,n);

    // Display the result
    cout << "Correlation Coefficient (Gamma_AB): " << gammaAB << endl;
    ofstream out("output.csv");
    out<<gammaAB<<endl;
    return 0;
}
