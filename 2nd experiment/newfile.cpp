#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<climits>
using namespace std;

double min_max_norm(double val,double min,double max,double new_min,double new_max)
{
    double final_result=((val-min)/(max-min))*(new_max-new_min)+new_min;
    return final_result;
}

double z_score(double val,double mean,double sd)
{
    double result=(val-mean)/sd;
    return result;
}

vector<double>decimalscaling(vector<double>data){
      double max = *max_element(data.begin(), data.end());
      int n = ceil(log10(max));

      vector<double>deci_scaling;  
      for(double val:data){
         val = val/pow(10,n);
         deci_scaling.push_back(val);
      }
      return deci_scaling;
}
int main()
{
    ifstream input_file("input.csv");

    ofstream output_file("output_min_max.csv");
    ofstream output_file1("output_zscore.csv");
    ofstream output_file2("output_decimal.csv");
    
    //minmax normalization
     vector<double> data;
    double value;
     while(input_file>>value)
     {
        data.push_back(value);
     }
    
    double min_ele=INT_MAX;
    double max_ele=INT_MIN;

    for(int i=0;i<data.size();i++)
    {
        min_ele=min(min_ele,data[i]);
        max_ele=max(max_ele,data[i]);
    }
     //double min=*min_element(data.begin(),data.end());
     //double max=*max_element(data.begin(),data.end());
    double new_min=0.0;
    double new_max=0.0;
    cout<<"Enter new range that is min and max element of new range"<<endl;
    cin>>new_min>>new_max;
    for(const double &val : data)
    {
        double result=min_max_norm(val,min_ele,max_ele,new_min,new_max);
        output_file<<result<<endl;
    }
  cout<<"output is generated in output_minmax.csv"<<endl;
  //zscore normalization
    double sum=0.0;
    for(const double &v:data)
    {
        sum=sum+v;
    }
    double mean=sum/data.size();

    double diff_summ=0.0;
    for(const double &v:data)
    {
        diff_summ=diff_summ+pow((v-mean),2);
    }
    double sd=sqrt(diff_summ/data.size());

    for(const double &v:data)
    {
        double result=z_score(v,mean,sd);
        output_file1<<result<<endl;
    }
    cout<<"output is generated in output_zscore.csv"<<endl;

    //decimal scaling normalization
    vector<double> res_decimal;
    res_decimal=decimalscaling(data);
    for(const double &v:res_decimal)
    {
        output_file2<<v<<endl;
    }

    input_file.close();
    output_file.close();
    

    return 0;
}