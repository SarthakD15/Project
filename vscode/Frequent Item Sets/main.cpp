// 2020BTEIT00059, Ankur Singh, DM LAB Journal.

#include <bits/stdc++.h>
using namespace std;

// Splliting the words into single characters inorder to get their count.
vector<string> splitIntoWords(string input) {
    vector<string> wordList;
    string word = "";
    int ind = 0;

    while(ind < input.size()) {
        if(isalnum(input[ind])) {
            word += input[ind];
        }
        else {
            if(!word.empty()) {
                wordList.push_back(word);
                word = "";
            }
        }
        ind++;
    }

    if(!word.empty()) {
        wordList.push_back(word);
    }

    return wordList;
}

// Concatenating the strings.
string concatenateWithoutIndex(vector<string> items, int excludedIndex) {
    string result;
    for(int i=0;i<items.size();i++) {
        if(i != excludedIndex) {
            result += items[i] + " ";
        }
    }

    // Remove trailing space
    if(!result.empty()) {
        result.pop_back();
    }

    return result;
}

set<string> copySet(set<string> original) {
    set<string> duplicate;
    for(auto itr:original) {
        duplicate.insert(itr);
    }

    return duplicate;
}

// Generating candidate itemsets for apriori.
set<string> generateCandidateItemsets(set<string> inputItemsets, int itemsetSize) {
    set<string> candidateItemsets;

    for(auto itr1 = inputItemsets.begin(); itr1 != inputItemsets.end(); itr1++) {
        auto itr2 = itr1;
        itr2++;

        for(; itr2 != inputItemsets.end(); itr2++) {
            // Split each itemset into individual items.
            vector<string> v1 = splitIntoWords(*itr1);
            vector<string> v2 = splitIntoWords(*itr2);

            bool allEqual = true;

            // Check if the first (itemsetSize - 1) items of the two itemsets are equal.
            for(int i=0; i<itemsetSize-1 and allEqual; i++) {
                if(v1[i] != v2[i]) {
                    allEqual = false;
                }
            }

            // Combine the last item from each itemset
            v1.push_back(v2[itemsetSize-1]);

            // Ensure the items are lexicographically ordered
            if(v1[v1.size()-1] < v1[v1.size()-2]) {
                swap(v1[v1.size()-1], v1[v1.size()-2]);
            }

            // Check if all subsets of the combined itemset are in the input set.
            for(int i=0;i<v1.size() and allEqual; i++) {
                string temp = concatenateWithoutIndex(v1, i);
                if(inputItemsets.find(temp) == inputItemsets.end()) {
                    allEqual = false;
                }
            }

            // If all conditions are met
            if(allEqual) {
                candidateItemsets.insert(concatenateWithoutIndex(v1, -1));
            }
        }
    }

    return candidateItemsets;
}

int main()
{
    ifstream file("input.csv");
    double minsup;
    vector<set<string>> datatable;
    set<string> products;
    map<string, int> freq;
    string line;

    if (!file.is_open())
    {
        perror("Error in opening file : ");
        return -1;
    }
    cout << "Frequency % :";
    cin >> minsup;

    while(getline(file, line)) {
        vector<string> arr = splitIntoWords(line);
        set<string> tmpset;
        for (int i = 0; i < arr.size(); i++)
            tmpset.insert(arr[i]);
        datatable.push_back(tmpset);
        for (set<string>::iterator it = tmpset.begin(); it != tmpset.end(); it++) {
            products.insert(*it);
            freq[*it]++;
        }
    }

    file.close();

    int minfre = minsup * datatable.size() / 100;

    queue<set<string>::iterator> q;
    for (set<string>::iterator it = products.begin(); it != products.end(); it++)
        if (freq[*it] < minfre)
            q.push(it);

    while (q.size() > 0)
    {
        products.erase(*q.front());
        q.pop();
    }
    int pass = 1;
    cout << "\nFrequent " << pass++ << " -item set : \n";
    for (set<string>::iterator it = products.begin(); it != products.end(); it++)
        cout << "{" << *it << "} " << (freq[*it]*100) / datatable.size() <<"%"<< endl;
    int i = 2;
    set<string> prev = copySet(products);
    while (i)
    {
        set<string> cur = generateCandidateItemsets(prev, i - 1);
        if (cur.size() < 1) {
            break;
        }
        for (set<string>::iterator it = cur.begin(); it != cur.end(); it++) {
            vector<string> arr = splitIntoWords(*it);
            int tot = 0;
            for (int j = 0; j < datatable.size(); j++)
            {
                bool pres = true;
                for (int k = 0; k < arr.size() && pres; k++)
                    if (datatable[j].find(arr[k]) == datatable[j].end())
                        pres = false;
                if (pres)
                    tot++;
            }
            if (tot >= minfre)
                freq[*it] += tot;
            else
                q.push(it);
        }
        while (q.size() > 0)
        {
            cur.erase(*q.front());
            q.pop();
        }

        if (cur.size() == 0)
            break;
        cout << "\n\nFrequent " << pass++ << " -item set : \n";
        for (set<string>::iterator it = cur.begin(); it != cur.end(); it++)
            cout << "{" << *it << "} " << (freq[*it]*100)/datatable.size() <<"%"<< endl;
        prev = copySet(cur);
        i++;
    }
    
    ofstream out_file("ferqitem_op.csv", ios::out);
    for (auto it = prev.begin(); it != prev.end(); it++)
    {
        out_file << "{" << *it << "}" << endl;
    }
    return 0;
}