#include<bits/stdc++.h>
using namespace std;
int main()
{
    ifstream f1("input.csv");
    if(!f1.is_open())
    {
        cout<<"Error in opening"<<endl;
    }
    map<string,map<string,int>>rowcolmap;
    string row,col,s,count;
    int  val;
    map<string,int>rowmap;
    map<string,int>colmap;

    int i=0;
    while(getline(f1,s))
    {
        stringstream str(s);
        if(i==0)
        {
            i++;
            continue;
        }
        getline(str,row,',');
        getline(str,col,',');
        getline(str,count,',');
        val=stoi(count);

        rowcolmap[row][col]+=val;
        rowmap[row]+=val;
        colmap[col]+=val;
    }
    for(auto r:rowmap)
    {
        for(auto c:colmap)
        {
            cout<<r.first<<"-"<<c.first<<":";
            cout<<rowcolmap[r.first][c.first]<<endl;
        }
    }
    int colsum=0,rowsum=0;
    for(auto r:rowmap)
    {
        rowsum+= r.second;
    }
    for(auto c:colmap)
    {
        colsum= c.second;
    }
    cout<<"Row Sum :"<<rowsum<<endl;
    cout<<"Column Sum :"<<colsum<<endl;

    ofstream f2("Out.csv");
    f2 << "Column\\row , ,India ,, ,USA ,, ,Total,,, " <<endl;
    f2 << ",Count,t-weight,d-weight,Count,t-weight,d-weight,Count,t-weight,d-weight" << endl;
    for(auto r:rowmap)
    {
        row=r.first;
        f2<<row<<",";

        for(auto c:colmap)
        {
            col=c.first;
            f2<<rowcolmap[row][col]<<",";
            //t-weight
            f2<<((float)rowcolmap[row][col]/rowmap[row])*100<<"%"<<",";
            //dweight
            f2<<((float)rowcolmap[row][col]/colmap[col])*100<<"%"<<",";

        }
        f2<<rowmap[row]<<","<<((float)rowmap[row]/rowmap[row])*100<<"%,"<<((float)rowmap[row]/colsum)*100<<"%"<<endl;
    }
    f2<<"Total,";
    for(auto c:colmap)
    {
        col=c.first;
        f2<<colmap[col]<<",";
        f2<<((float)colmap[col]/colsum)*100<<"%,";
        f2<<((float)colmap[col]/colmap[col])*100<<"%,";
    }
    f2<<colsum<<","<<"100, 100"<<endl;
    return 0;
}