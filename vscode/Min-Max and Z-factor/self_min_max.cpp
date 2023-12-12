# include<bits/stdc++.h>
using namespace std;
int main()
{
    ifstream f1("input1.csv");
    ifstream fe1("input1.csv");
    ifstream f2("input2.csv");
    ifstream fe2("input2.csv");
    ifstream fe3("input2.csv");
    ofstream fo1("output1.csv");
    ofstream fo2("output2.csv");
    cout<<"1. MIn_Max Normalization"<<endl<<"2. Z Score Normalization"<<endl;
    string l;
    int choise=0;
    cin>>choise;
    if(choise == 1)
    {
       if(!f1.is_open())
       {
        cout<<"File cant open"<<endl;
       }
       double oldmin, oldmax,newmin,newmax;
       int temp;
       fo1<<"Original data"<<","<<"Normalize Data"<<endl;
       getline(f1,l);
       temp=stoi(l);
       oldmax=temp;
       oldmin=temp;
       while(getline(f1,l))
       {
        temp=stoi(l);
        if(temp>oldmax)
        {
            oldmax=temp;
        } 
        if(temp<oldmin){
            oldmin=temp;
        }
       }
        cout<<"Enter New Min and New Max"<<endl;
        cin>>newmin>>newmax;
        while(getline(fe1,l))
        {
            temp=stoi(l);
            double ans=((((temp-oldmin)/(oldmax-oldmin))*(newmax-newmin))+newmin);
            fo1<<temp<<","<<ans;
            fo1<<endl;
        }
        fo1.close();
        f1.close();
        fe1.close();
    }else{
        int sum1=0,count;
        string s;
        while(getline(f2,s))
        {
            int temp=stoi(s);
            sum1+=temp;
            count++;
        }
        double mean=sum1/count;
        double sum2=0;
        while(getline(fe2,s))
        {
            int temp=stoi(s);
            sum2+=(temp-mean)*(temp-mean);
        }
        double sd=sqrt(sum2/count);
        while(getline(fe3,s))
        {
            int temp=stoi(s);
            double ans=((temp-mean)/sd);
            fo2<<temp<<","<<ans;
            fo2<<endl;
        }
    }
    return 0;
} 