// 2020BTEIT00059, Ankur Singh, DM LAB Journal.

#include<bits/stdc++.h>
using namespace std;

int main() {
    // Opening a file to get input.
    ifstream file("input.csv");

    if(!file.is_open()) {
        perror("Couldn't Open file");
        return -1;
    }

    string line, word;
    string col, row, count;
    int val;

    map<string, map<string, int>> rowcolMap;
    map<string, int> colMap;
    map<string, int> rowMap;

    int i=0;

    while(getline(file, line)) {
        stringstream str(line);
        if(i == 0) {
            i++;
            continue;
        }

        getline(str, row, ',');
        getline(str, col, ',');
        getline(str, count, ',');
        val = stoi(count);

        rowcolMap[row][col] += val;
        rowMap[row] += val;
        colMap[col] += val;
    }

    for(auto r:rowMap) {;
        for(auto c:colMap) {
            cout<<r.first<<"-"<<c.first<<":";
            cout<<rowcolMap[r.first][c.first]<<endl;
        }
    }

    for(auto r:rowMap) {
        cout<<r.first<<"->"<<r.second<<endl;
    }
    for(auto c:colMap) {
        cout<<c.first<<"->"<<c.second<<endl;
    }

    int colSum = 0, rowSum = 0;
    for(auto c:colMap) {
        colSum += c.second;
    }
    cout<<"colSum: "<<colSum<<endl;

    for(auto r:rowMap) {
        rowSum += r.second;
    }
    cout<<"rowSum:" <<rowSum<<endl;
    
    // Create a file to write output.
    ofstream out_file("output.csv");

    out_file << "Column\\row , ,India ,, ,USA ,, ,Total,,, " <<endl;
    out_file << ",Count,t-weight,d-weight,Count,t-weight,d-weight,Count,t-weight,d-weight" << endl;

    for(auto r:rowMap) {
        row = r.first;
        out_file<<row<<",";
        
        // 1st iteration Hollywood t-weight, d-weight 2nd iteration Tollywood t-weight, d-weight.
        for(auto c:colMap) {
            col = c.first;

            out_file<<rowcolMap[row][col]<<",";
            // t-weight.
            out_file<<((float)rowcolMap[row][col] / rowMap[row]) * 100<<"%,";
            // d-weight.
            out_file<<((float)rowcolMap[row][col] / colMap[col]) * 100<<"%,";
        }
        // Total t-weight, d-weight.
        out_file<<rowMap[row]<<","<<((float)rowMap[row]/rowMap[row])*100<<"%,"<<((float)rowMap[row]/(colSum))*100<<"%"<<endl;
    }
    out_file<<"Total ,";

    for(auto c:colMap) {
        col = c.first;

        out_file<<colMap[col]<<",";
        out_file<<((float)colMap[col]/colSum)*100<<"%,";
        out_file<<((float)colMap[col]/colMap[col])*100<<"%,";
    }

    out_file<<colSum<<","<<"100%, 100%"<<endl;

    out_file.close();

    return 0;
}