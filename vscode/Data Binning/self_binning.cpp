# include<bits/stdc++.h>
using namespace std;
int main()
{
    ifstream f1("input.csv");
    vector<int>arr;
    string s;
    while(getline(f1,s))
    {
        int temp=stoi(s);
        arr.push_back(temp);
    }
    int choice;
    cout<<"Enter choice:"<<endl;
    cout<<"1. Equal Frequency Binning."<<endl<<"2. Equal Width Binning."<<endl;
    cin>>choice;
    int nb;
    cout<<"Enter number of bins"<<endl;
    cin>>nb;
    if(choice == 1)
    {
        int n=arr.size();
        int freq=ceil((float)n/nb);
        vector<vector<int>>bins;
        for(int i=0;i<nb;i++)
        {
            vector<int>bin;
            for(int j=i*freq;j<(i+1)*freq;j++)
            {
                if(j>n)break;
                bin.push_back(arr[j]);
            }
            bins.push_back(bin);
        }
        ofstream f2("output.csv");
        for(int i=0;i<bins.size();i++)
        {
            f2<<"Bin "<<i+1<<",";
            for(int j=0;j<bins[i].size();j++)
            {
                f2<<bins[i][j]<<",";
            }
            f2<<endl;
        }
        f1.close();
        f2.close();
    }else{
        int minn=INT_MAX;
        int maxx=INT_MIN;
        for(int i=0;i<arr.size();i++)
        {
            minn=min(minn,arr[i]);
            maxx=max(maxx,arr[i]);
        }
        int width =(maxx-minn)/nb;
        vector<vector<int>>bins;
        vector<int>temp;
        for(int i=0;i<=nb;i++)
        {
            temp.push_back((minn)+(width*i));
        }
        for(int i=0;i<nb;i++)
        {
            vector<int>bin;
            for(int j=0;j<arr.size();j++)
            {
                if(arr[j]>=temp[i] && arr[j]<temp[i+1])
                {
                    bin.push_back(arr[j]);
                }
            }
            bins.push_back(bin);
        }
        ofstream f2("output.csv");
        for(int i=0;i<bins.size();i++)
        {
            f2<<"Bin "<<i+1<<",";
            for(int j=0;j<bins[i].size();j++)
            {
                f2<<bins[i][j]<<",";
            }
            f2<<endl;
        }
    }
return 0;
}