#include<bits/stdc++.h>
using namespace std;

int main() {
    ifstream f1("info-gain.csv");


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

    // Information of Main Class.
    double info_main = 0.0;
    for(auto attributes:col_attri[mainClass]) {
        double val = attr_count[attributes];
        info_main += -(val/count)*(log2(val/count));
    }

    // Information for other classes.
    for(int i=0;i<header.size();i++) {
        if(i != ind) {
            double info = 0.0;
            for(auto col_attr:col_attri[header[i]]) {
                double entropy = 0.0;
                double tot = attr_count[col_attr];

                for(auto main_attr:col_attri[mainClass]) {
                    double val = count_mat[col_attr][main_attr];
                    if(val != 0) {
                        entropy += -(val/tot)*(log2(val/tot));
                    }
                }
                info += (tot/count)*entropy;
            }

            cout<<"Information of "<<header[i]<<" is:"<<info<<endl;
            cout<<"Information Gain:"<<info_main-info<<endl;
        }
    }
    return 0;
}