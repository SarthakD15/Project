#include<bits/stdc++.h>
using namespace std;
double median(vector<int>arr)
{
    int n=arr.size();
    if(n%2!=0)
    {
        return arr[n/2];
    }else{
        return (arr[n/2] + arr[(n/2)-1]) / 2.0;
    }
}
int main()
{
    ifstream f1("input.csv");
    ofstream f2("output.csv");
    string s;
    vector<int>arr;
    getline(f1,s);
    while(getline(f1,s))
    {
        int temp = stoi(s);
        arr.push_back(temp);
    }
    int mini=INT_MAX;
    int maxi=INT_MIN;
    for(int i=0;i<arr.size();i++)
    {
        mini=min(mini,arr[i]);
        maxi=max(maxi,arr[i]);
    }
    int n=arr.size();
    sort(arr.begin(),arr.end());
    double med=median(arr);
    vector<int>first;
    for(int i=0;i<n/2;i++)
    {
        first.push_back(arr[i]);
    }
    vector<int>second;
    for(int i=n/2+1;i<n;i++)
    {
        second.push_back(arr[i]);
    }
    double q1=median(first);
    double q2=median(second);
    f2<<"Minimum :"<<","<<mini<<endl;
    f2<<"Maximum :"<<","<<maxi<<endl;
    f2<<"Medium :"<<","<<med<<endl;
    f2<<"Quartile1 :"<<","<<q1<<endl;
    f2<<"Quartile3 :"<<","<<q2<<endl;
    return 0;
} 
