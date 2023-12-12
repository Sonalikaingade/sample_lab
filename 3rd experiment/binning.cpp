#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>

using namespace std;

// Equal Frequency Binning
vector<vector<int>> equi_frequency_binning(vector<int> data, int m)
{
  int a = data.size();
  int n = a / m;
  vector<vector<int>> bins;
  for (int i = 0; i < m; i++)
  {
    vector<int> bin;
    for (int j = i * n; j < (i + 1) * n; j++)
    {
      if (j >= a)
      {
        break;
      }
      bin.push_back(data[j]);
    }
    bins.push_back(bin);
  }
  return bins;
}

// Equal Width Binning
vector<vector<int>> equi_width_binning(vector<int> data, int m)
{
  int a = data.size();

  int max_ele = INT_MIN;
  int min_ele = INT_MAX;

  for (int i = 0; i < data.size(); i++)
  {
    max_ele = max(max_ele, data[i]);
    min_ele = min(min_ele, data[i]);
  }

  int w = (max_ele - min_ele) / m;
  int min1 = min_ele;

  vector<int> arr;
  for (int i = 0; i < m + 1; i++)
  { //arr is the vector that shoes the range of the data to be pushed in the bins
    arr.push_back(min1 + w * i); 
  }

  vector<vector<int>> arri;
  for (int i = 0; i < m; i++)
  {
    vector<int> temp;
    for (int j : data)
    {
      if (j >= arr[i] && j <= arr[i + 1])
      {
        temp.push_back(j);
      }
    }
    arri.push_back(temp);
  }
  return arri;
}

// Reading data from CSV
vector<int> readCSV(string filename)
{
  ifstream inputFile(filename);
  vector<int> data;
  string line, value;
  while (getline(inputFile, line))
  {
    stringstream ss(line);
    while (getline(ss, value, ','))
    {
      data.push_back(stoi(value));
    }
  }
  inputFile.close();
  return data;
}

// Write binning outputs to CSV
void writeCSV(string filename, vector<vector<int>> bins)
{
  ofstream outputFile(filename);
  for (int i = 0; i < bins.size(); i++)
  {
    outputFile << "Bin " << i + 1 << ",";
    for (int num : bins[i])
    {
      outputFile << num << ",";
    }
    outputFile << "\n";
  }
  outputFile.close();
}

int main()
{
  vector<int> data = readCSV("data.csv");
  int m;

  int method;
  cout << "Choose binning method: " << endl;
  cout << "1. Equal Frequency Binning" << endl;
  cout << "2. Equal Width Binning" << endl;
  cout << "\nEnter method number: ";
  cin >> method;
  cout << "\nEnter number of bins: ";
  cin >> m;

  if (method == 1)
  {
    vector<vector<int>> freqBins = equi_frequency_binning(data, m);
    writeCSV("output_equi_frequency_binning.csv", freqBins);
  }
  else if (method == 2)
  {
    vector<vector<int>> widthBins = equi_width_binning(data, m);
    writeCSV("output_equi_width_binning.csv", widthBins);
  }
  else
  {
    cout << "Invalid method choice." << endl;
  }

  return 0;
}