#include<iostream>
#include<sstream>
#include<map>
#include<fstream>

using namespace std;
struct cellData
{
    int count;
    int tWeight;
    int dWeight;
};

void readData(const string &filename,map<string,map<string,cellData>> &Celldata,map<string,int> &coltotal,map<string,int> &rowtotal)
{
    fstream in(filename,ios::in);
    if(!in.is_open())
    {
        cout<<"couldn't open file"<<filename<<endl;
        return;
    }

    string line,row,col,count;
    int val;
    int ln=0;
    while (getline(in,line))
    {
        stringstream str(line);
        if(ln==0)
        {
            ln++;
            continue;
        }
        getline(str,row,',');
        getline(str,col,',');
        getline(str,count,',');
        val=stoi(count);


        Celldata[row][col].count +=val;
        coltotal[col]+=val;
        rowtotal[row]+=val;

    }
}
 void writeData(const string &filename, const map<string, map<string, cellData>> &CellData,
                 const map<string, int> &columnTotal, const map<string, int> &rowTotal)
{
    ofstream fw(filename, ios::out);

    fw << "Column\\Row, Count, T-Weight, D-Weight, Count, T-Weight, D-Weight, Count, T-Weight, D-Weight" << endl;
    int total1 = 0;
    for (const auto &rowEntry : rowTotal)
    {
        total1 += rowEntry.second;
    }
    for (const auto &rowEntry : rowTotal)
    {
        const string &row = rowEntry.first;
        fw << row << ",";

       for (const auto &colEntry : columnTotal)
        {
            const string &col = colEntry.first;
            const cellData &cell = CellData.at(row).at(col);

            fw << cell.count << ",";
            fw << ((float)cell.count / rowTotal.at(row)) * 100 << "%,";
            fw << ((float)cell.count / colEntry.second) * 100 << "%,";
        }

        fw << rowTotal.at(row) << ","
           << "100%," << ((float)rowTotal.at(row) / total1) * 100 << "%" << endl;
    }

    fw << "Total,";
    int total = 0;
    for (const auto &colEntry : columnTotal)
    {
        total += colEntry.second;
    }

    for (const auto &colEntry : columnTotal)
    {
        fw << colEntry.second << ",";
        fw << ((float)colEntry.second / total) * 100 << "%,";
        fw << "100%,";
    }

    fw << total << ",100%, 100%" << endl;
}

int main()
{

    map<string,map<string,cellData>> Celldata;
    map<string,int> coltotal;
    map<string,int>rowtotal;

    readData("t-d-weight-input.csv",Celldata,coltotal,rowtotal);
    writeData("t-d-weight-output.csv",Celldata,coltotal,rowtotal);

    cout<<"Processing is competetd and result is write to the output file.."<<endl;

    return 0;
}