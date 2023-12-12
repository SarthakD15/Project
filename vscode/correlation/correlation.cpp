#include<bits/stdc++.h>
using namespace std;

double mean(vector<double> arr) {
    double sum = 0;
    for(int i=0;i<arr.size();i++) {
        sum += arr[i];
    }

    return sum/arr.size();
}

double numerator(vector<double> arr1, vector<double> arr2) {
    double mean1 = mean(arr1);
    double mean2 = mean(arr2);

    cout<<mean1<<" "<<mean2<<endl;

    double ans = 0;

    cout<<"x-x` and y-y`"<<endl;
    for(int i=0;i<arr1.size();i++) {
        ans += ((arr1[i]-mean1)*(arr2[i]-mean2));
        cout<<arr1[i]-mean1<<" "<<arr2[i]-mean2<<endl;
    }

    return ans;
}

double denominator(vector<double> arr) {
    double mean1 = mean(arr);

    double ans = 0;
    cout<<"Standard Deviation"<<endl;
    for(int i=0;i<arr.size();i++) {
        ans += ((arr[i]-mean1)*(arr[i]-mean1));
        cout<<((arr[i]-mean1)*(arr[i]-mean1))<<endl;
    }

    return ans;
}

int main() {

    ifstream file("input.csv");
    if(!file.is_open()) {
        perror("Couldn't open the file");
    }

    int i=0;
    string line, data;
    
    vector<double> arr1;
    vector<double> arr2;

    while(getline(file, line)) {
        if(i == 0) {
            i++;
            continue;
        }

        stringstream str(line);

        getline(str, data, ',');
        arr1.push_back(stod(data));

        getline(str, data, ',');
        arr2.push_back(stod(data));
    }

    double covar = numerator(arr1, arr2);
    double s1 = denominator(arr1);
    double s2 = denominator(arr2);

    double ans = (covar/sqrt(s1*s2));

    cout<<ans<<endl;

    if(ans > 0) {
        cout<<"Data is Positively Correlated"<<endl;
    }
    else if(ans < 0) {
        cout<<"Data is Negatively Correlated"<<endl;
    }
    else {
        cout<<"Data is not linearly related"<<endl;
    }
    return 0;
}