#include<bits/stdc++.h>
using namespace std;

int main() {
    // Reading Input.
    ifstream file1("input1.csv");
    ifstream file2("input2.csv");

    // Output File.
    ofstream out_file1("output1.csv");
    ofstream out_file2("output2.csv");

    string line;
    int choice;
    cout<<"Enter choice:"<<endl;
    cout<<"1. Min Max Normalization"<<endl<<"2. Z score Normalization"<<endl;
    cin>>choice;

    if(choice == 1) {
        if(!file1.is_open()) {
            perror("Couldn't open the file");
            return -1;
        }

        // Declaring header for output file.
        out_file1<<"Original Data"<<","<<"Normalized Data"<<endl;

        double old_min, old_max, new_min, new_max;

        int temp;
        getline(file1, line);
        temp = stoi(line);
        old_min = temp;
        old_max = temp;
        while(getline(file1, line)) {
            temp = stoi(line);
            if(temp > old_max) {
                old_max = temp;
            }
            else if(temp < old_min) {
                old_min = temp;
            }
        }

        cout<<"Enter new min:";
        cin>>new_min;
        cout<<"Enter new max:";
        cin>>new_max;

        file1.clear();
        file1.seekg(0, ios::beg);

        while(getline(file1, line)) {
            temp = stoi(line);
            double ans = (((temp - old_min) / (old_max - old_min)) * (new_max - new_min)) + new_min;
            out_file1<<temp<<","<<ans;
            out_file1<<endl;
        }

        out_file1.close();
        file1.close();
    }
    else {
        if(!file2.is_open()) {
            perror("Couldn't open the file");
            return -1;
        }

        // Declaring header for output file.
        out_file2<<"Original Data"<<","<<"Normalized Data"<<endl;

        int temp;
        double sum = 0, num_data = 0;
        while(getline(file2, line)) {
            temp = stoi(line);
            sum += temp;
            num_data++;
        }   

        double mean = sum/num_data;

        file2.clear();
        file2.seekg(0, ios::beg);

        double sum2 = 0;
        while(getline(file2, line)) {
            temp = stoi(line);
            sum2 += (temp-mean)*(temp-mean);
        }

        double s_dev = sqrt(sum2/num_data);

        file2.clear();
        file2.seekg(0, ios::beg);

        while(getline(file2, line)) {
            temp = stoi(line);
            double ans = ((temp-mean)/s_dev);
            out_file2<<temp<<","<<ans;
            out_file2<<endl;
        }
    }
    return 0;
}