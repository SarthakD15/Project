#include<bits/stdc++.h>
using namespace std;

int main() {
    ifstream file("input.csv");

    string line, word;
    string rain, temp, status, work, inc_weight;

    map<string, int> class1;
    map<string, map<string, int>> class2;

    if(!file.is_open()) {
        perror("Couldn't open the file:");
        return -1;
    }

    int i=0;
    string subClass;

    while(getline(file, line)) {
        stringstream str(line);
        getline(str, rain, ',');
        getline(str, temp, ',');
        getline(str, status, ',');
        getline(str, work, ',');
        getline(str, inc_weight, ',');

        int column;
        if(i == 0) {
            i++;
            cout<<"Enter sub class column:";
            cin>>column;
            continue;
        }

        if(column == 1) {
            subClass = rain;
        }
        else if(column == 2) {
            subClass = temp;
        }
        else if(column == 3) {
            subClass = status;
        }
        else if(column == 4) {
            subClass = work;
        }

        class1[inc_weight]++;
        class2[subClass][inc_weight]++;
    }

    double pos = class1["Yes"], neg = class1["No"];
    double total = pos+neg;

    double class1_entropy = -((pos/total) * log2(pos/total) + (neg/total) * log2(neg/total));
    cout<<"Class1 Entropy:"<<class1_entropy<<endl;

    double class2_entropy = 0;
    for(auto itr:class2) {
        string d_class = itr.first;
        double pos = class2[d_class]["Yes"], neg = class2[d_class]["No"];

        double total = pos+neg;

        class2_entropy += -((pos+neg)/total) * ((pos/total) * log2(pos/total) + (neg/total) * log2(neg/total));
    }

    cout<<"Class2 Entropy:"<<class2_entropy<<endl;
    cout<<"Info Gain:"<<class1_entropy-class2_entropy<<endl;

    return 0;
}