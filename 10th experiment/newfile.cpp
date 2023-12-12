#include <bits/stdc++.h>
using namespace std;

double finddist(pair<double,double>p1, pair<double,double>p2){
    double x1 = p1.first;
    double x2 = p2.first;
    double y1 = p1.second;
    double y2 = p2.second;

    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main(){
    string line;
    ifstream input("cluster_input.csv");
    vector<pair<double, double>>points;
    int j = 0;
    while(getline(input,line)){
        stringstream str(line);
        
        if(j==0){
            j++;
            continue;
        }
        string name,x,y;
        getline(str,name,',');
        getline(str,x,',');
        getline(str,y);

        points.push_back({stoi(x), stoi(y)});
    }
    input.close();

    double x_sum, y_sum, x_mean, y_mean;
    int n = points.size();
    for(auto it : points){
        x_sum += it.first;
        y_sum += it.second;
    }
    x_mean = x_sum/n;
    y_mean = y_sum/n;

    //calculate distance of each point from every point
    ofstream output("output.csv");
    output<<","<<"p1," <<"p2,"<<"p3,"<<"p4,"<<"p5"<<endl;
    for(int i = 0; i<points.size();i++){
        output<<"p"<<i+1<<",";
        for(int j = 0; j<=i;j++){
            if(i==j){
                output<<"0,";
            }
            else{
            double ans = finddist(points[i],points[j]);
                output<<ans<<",";
            }
        }
        output<<endl;
    }

    output<<"centroid,";
    for(int i = 0; i<points.size(); i++){
           double ans = finddist(points[i],{x_mean,y_mean});
                output<<ans<<",";
    }
    cout << endl;
    output.close();

      
}