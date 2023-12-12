#include<bits/stdc++.h>
using namespace std;

int main() {

    // Reading input file.
    ifstream file("input.csv");

    vector<int> arr;
    string line;
    int value;
    while(getline(file, line)) {
        value = stoi(line);
        arr.push_back(value);
    }

    file.close();

    int choice;
    cout<<"Enter choice:"<<endl;
    cout<<"1. Equal Frequency Binning."<<endl<<"2. Equal Width Binning."<<endl;
    cin>>choice;

    int nbins;
    cout<<"Enter number of bins:"<<endl;
    cin>>nbins;

    if(choice == 1) {
        // Equal Frequency Binning.

        int n = arr.size();
        int freq = ceil((float)n/nbins);
        cout<<freq<<endl;

        vector<vector<int>> bins;
        for(int i=0;i<nbins;i++) {
            vector<int> bin;
            for(int j=i*freq; j<(i+1)*freq;j++) {
                if(j>=n) break;
                bin.push_back(arr[j]);
            }
            bins.push_back(bin);
        }

        ofstream out_file("output.csv");

        for(int i=0;i<bins.size();i++) {
            out_file<<"Bin "<<i+1<<",";
            for(int j=0;j<bins[i].size();j++) {
                out_file<<bins[i][j]<<",";
            }
            out_file<<endl;
        }

        out_file.close();
    }
    else if(choice == 2) {
        // Equal Width Binning. 

        int n = arr.size();

        int maxi = INT_MIN;
        int mini = INT_MAX;

        for(int i=0;i<arr.size();i++) {
            maxi = max(maxi, arr[i]);
            mini = min(mini, arr[i]);
        }

        int width = (maxi-mini)/nbins;
        
        vector<int> temp;
        for(int i=0;i<=nbins;i++) {
            temp.push_back(mini + width*i);
        }

        vector<vector<int>> bins;
        for(int i=0;i<nbins;i++) {
            vector<int> bin;
            for(int j=0;j<arr.size();j++) {
                if(arr[j] >= temp[i] and arr[j] <= temp[i+1]) {
                    bin.push_back(arr[j]);
                }
            }
            bins.push_back(bin);
        }

        ofstream out_file("output.csv");

        for(int i=0;i<bins.size();i++) {
            out_file<<"Bin "<<i+1<<",";
            for(int j=0;j<bins[i].size();j++) {
                out_file<<bins[i][j]<<",";
            }
            out_file<<endl;
        }

        out_file.close();
    }

    return 0;
}