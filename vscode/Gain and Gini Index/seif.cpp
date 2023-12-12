#include<bits/stdc++.h>
using namespace std;

int main() {
    ifstream f1("input.csv");


    vector<string>header;
    map<string,map<string,int>>count_mat;
    map<string,int>attr_count;
    map<string,set<string>>col_attri;

    
    int ind;
    cout<<"ENter Base class"<<endl;
    cin>>ind;
    string line,data;
    int i=0;
    int count = 0;
    while ((getline(f1,line)))
    {
        stringstream str(line);
        if(i == 0) {
            while(getline(str, data, ',')) {
                header.push_back(data);
            }
            i++;continue;
        }

        vector<string> rowVal;
        while(getline(str,data,','))
        {
            rowVal.push_back(data);
        }

        for(int i=0;i<rowVal.size();i++) {
            attr_count[rowVal[i]]++;
            count_mat[rowVal[i]][rowVal[ind]]++;
            col_attri[header[i]].insert(rowVal[i]);
        }

        count++;
    }

    string mainClass = header[ind];
    // Gini Index of all attributes.
    for(int i=0;i<header.size();i++) {
        double gini = 0;
        for(auto col_attr:col_attri[header[i]]) {
            double tot = attr_count[col_attr];
            double result = 0;

            for(auto main_attr:col_attri[mainClass]) {
                double val = count_mat[col_attr][main_attr];
                if(val != 0) {
                    result += (val/tot)*(val/tot);
                }
            }

            gini += (tot/count)*(1-result);
        }

        cout<<"Gini Index of "<<header[i]<<" is:"<<gini<<endl;
    }
    return 0;
}