#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

float calmedian(vector<int>a)
{
    int n=a.size();
    if(n%2 == 1)
    {
        return a[n/2];
    }
    else{
        return (a[(n/2)-1]+a[n/2])/2.0;
    }
}

float calQ1(vector<int> a)
{
    vector<int>first;
    int n=a.size();
    for(int i=0;i<n/2;i++)
    {
        first.push_back(a[i]);
    }
    return calmedian(first);
}

float calQ3(vector<int> a)
{
    vector<int> last;
    int n=a.size();
    if(n%2 ==0)
    {
        for(int i=n/2;i<n;i++)
        {
            last.push_back(a[i]);
        }
    }
    else{
        for(int i=n/2 + 1;i<n;i++)
        {
            last.push_back(a[i]);
        }
    }
    return calmedian(last);
}
int main()
{

    ifstream input("five_number_input.csv");

    ofstream output("output.csv");

    int i=0;
    string mark , line;
    vector<int> arr;

    while(getline(input,line))
    {
        if(i==0)
        {
            i++;
            continue;
        }

        stringstream str(line);
        getline(str,mark,',');
        int x=stoi(mark);
        arr.push_back(x);
    }
    int n=arr.size();
    sort(arr.begin(),arr.end());

    output<< "Minimum value: "
          <<","<<arr[0]<<"\n";  
    output<< " First quartile Q1: "
          <<"," <<calQ1(arr)<<"\n";
     output<< " Third quartile Q3: "
          <<"," <<calQ3(arr)<<"\n";
     output<< " Median: "
          <<"," <<calmedian(arr)<<"\n";
     output<< " Maximum value: "
          <<"," <<arr[n-1]<<"\n";
       


    return 0;
}