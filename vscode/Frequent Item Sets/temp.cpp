#include<bits/stdc++.h>
using namespace std;

set<string> copySet(set<string> curr) {
    set<string> ans;
    for(auto itr:curr) {
        ans.insert(itr);
    }

    return ans;
}

set<string> generateCandidate(set<string> prev, int size) {

    set<string> candidateSet;
    for(auto itr = prev.begin(); itr != prev.end(); itr++) {
        auto itr2 = itr;
        itr2++;
        for(; itr2 != prev.end(); itr2++) {
            string str1 = *itr;
            string str2 = *itr2;

            bool allEqual = true;
            for(int i=0;i<size-1 and allEqual;i++) {
                if(str1[i] != str2[i]) {
                    allEqual = false;
                }
            }

            str1.push_back(str2[str2.size()-1]);

            sort(str1.begin(), str1.end());

            if(allEqual) {
                candidateSet.insert(str1);
            }
        }
    }

    return candidateSet;
}

int main() {

    ifstream file("input.csv");
    vector<set<string>> datatable;
    set<string> products;
    map<string, int> freq;
    int count = 0;

    string line, data;
    while(getline(file, line)) {
        stringstream str(line);
        set<string> temp;

        while(getline(str, data, ',')) {
            freq[data]++;
            products.insert(data);
            temp.insert(data);
        }
        datatable.push_back(temp);
        count++;
    }

    double support;
    cout<<"ENter Support:"<<endl;
    cin>>support;

    double min_freq = ceil(((double)support*count)/100);

    queue<string> q;
    for(auto itr:products) {
        if(freq[itr] < min_freq) {
            q.push(itr);
        }
    }

    while(!q.empty()) {
        products.erase(q.front());
        q.pop();
    }

    set<string> prev = copySet(products);

    for(auto itr:products) {
        cout<<itr<<" "<<(freq[itr]*100)/count<<endl;
    }

    int i=1;
    while(i) {
        set<string> curr = generateCandidate(prev, i);

        if(curr.size() == 0) break;

        for(auto itr:curr) {
            int total = 0;
            string str = itr;
            for(int i=0;i<datatable.size();i++) {
                bool present = true;
                for(int j=0;j<str.length();j++) {
                    string ch = "";
                    ch += str[j];
                    if(datatable[i].find(ch) == datatable[i].end()) {
                        present = false;
                        break;
                    }
                }

                if(present) {
                    total++;
                }
            }

            if(total >= min_freq) {
                freq[itr] = total;
            }
            else {
                q.push(itr);
            }
        }

        while(!q.empty()) {
            curr.erase(q.front());
            q.pop();
        }

        if(curr.size() == 0) {
            break;
        }

        cout<<"Frequent Itemsets:"<<endl;
        for(auto itr:curr) {
            cout<<itr<<" -> "<<(freq[itr]*100)/count<<endl;
        }
        cout<<endl;

        prev = curr;
        i++;
    }

    return 0;
}