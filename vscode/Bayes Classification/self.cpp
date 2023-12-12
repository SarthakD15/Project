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

        // Bayes Classification.
    vector<string> x;
    for(int i=0;i<header.size()-1;i++) {
        string ch;
        cin>>ch;
        x.push_back(ch);
    }

    for(auto main_class:col_attri[mainClass]) {
        double probab = 1.0;
        probab *= (double)(attr_count[main_class])/count;

        for(auto x_attr:x) {
            double val = count_mat[x_attr][main_class];
            probab *= (double)val/attr_count[main_class];
        }

        cout<<main_class<<" "<<probab;
        cout<<endl;
    }
    return 0;
}