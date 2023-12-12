#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>
#include <climits>
#include<cmath>
using namespace std;
//equal frequency
vector<vector<int>> equi_frequency(vector<int> data,double m)
{
    
    double n=data.size();
    double ele=ceil(n/m);

    vector<vector<int>> totalbins;
    for(int i=0;i<m;i++)
    {
        vector<int> bin;
        for(int j=i*ele;j<(i+1)*ele;j++)
        {
            if(j>=n)
            {
                break;
            }
            bin.push_back(data[j]);
        }
        totalbins.push_back(bin);
    }
    return totalbins;
}

//equal width
vector<vector<int>>equi_width(vector<int> data,int m)
{
    int n=data.size();

    int min_ele=INT_MAX;
    int max_ele=INT_MIN;

    for(int i=0;i<data.size();i++)
    {
        min_ele= min(min_ele,data[i]);
        max_ele= max(max_ele,data[i]);
    }
    int w = (max_ele-min_ele)/m;
    int min1=min_ele;

    vector<int> arr;
    for(int i=0;i<m+1;i++)
    {
        arr.push_back(min1+w*i);
    }

    vector<vector<int>> arri;

    for(int i=0;i<m;i++)
    {
        vector<int> temp;
        for(int k:data)
        {
            if(k>=arr[i] && k<=arr[i+1])
            {
                temp.push_back(k);
            }
        }
        arri.push_back(temp);
    }
return arri;
}

// Write binning outputs to CSV
void writeCSV(string filename, vector<vector<int>> bins)
{
  ofstream outputFile(filename);
  for (int i = 0; i < bins.size(); i++)
  {
    outputFile << "Bin " << i + 1 << ":"<<" ";
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

    ifstream inputf("input.csv");
    

    vector<int> data;
    int val;
    while(inputf>>val)
    {
        data.push_back(val);
    }
    sort(data.begin(),data.end());
     int method,m;
  cout << "Choose binning method: " << endl;
  cout << "1. Equal Frequency Binning" << endl;
  cout << "2. Equal Width Binning" << endl;
  cout << "\nEnter method number: ";
  cin >> method;
  cout << "\nEnter number of bins: ";
  cin >> m;

  if (method == 1)
  {
    vector<vector<int>> freqBins = equi_frequency(data, m);
    writeCSV("output_equi_frequency.csv", freqBins);
  }
  else if (method == 2)
  {
    vector<vector<int>> widthBins = equi_width(data, m);
    writeCSV("output_equi_width.csv", widthBins);
  }
  else
  {
    cout << "Invalid method choice." << endl;
  }


    return 0;

}