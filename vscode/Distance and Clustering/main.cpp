#include<bits/stdc++.h>
using namespace std;

int k;

struct Point {
    double x, y;
    int cluster;
};

double distance(Point a, Point b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

void clustering(vector<Point> &arr, vector<Point> &clust_center) {
    cout<<endl;
    for(int i=0;i<arr.size();i++) {
        double min_dist = distance(arr[i], clust_center[0]);
        int nearestCluster = 0;
    
        for(int j=0;j<k;j++) {
            double dist = distance(arr[i], clust_center[j]);
            cout<<dist<<" ";
            if(dist < min_dist) {
                min_dist = dist;
                nearestCluster = j;
            }
        }
        cout<<endl;

        arr[i].cluster = nearestCluster;
    }
}

void updateclust_center(vector<Point> &arr, vector<Point> &clust_center) {
    map<int, int> clust;
    vector<Point> centroidSum(k, {0.0, 0.0, 0});

    for(int i=0;i<arr.size();i++) {
        int cluster = arr[i].cluster;
        // counting number of points in particular cluster.
        clust[cluster]++;
        centroidSum[cluster].x += arr[i].x;
        centroidSum[cluster].y += arr[i].y;
    }

    for(int i=0;i<k;i++) {
        if(clust.find(i) != clust.end()) {
            clust_center[i].x = centroidSum[i].x / clust[i];
            clust_center[i].y = centroidSum[i].y / clust[i];
        }
    }
}


int main() {
    ifstream file("input.csv");
    string line, point, x, y;
    vector<Point> arr;

    cout<<"Enter number of clusters:";
    cin>>k;

    // Skipping headers.
    getline(file, line);
    while(getline(file, line)) {
        stringstream str(line);

        getline(str, point, ',');
        getline(str, x, ',');
        getline(str, y, ',');

        Point p;
        p.x = stod(x);
        p.y = stod(y);

        arr.push_back(p);
    }

    random_device rand;
    mt19937 gen(rand());
    uniform_int_distribution<>dis(1, arr.size());

    vector<Point> cluster_center(k);

    for(int i=0;i<k;i++) {
        int r = dis(gen);
        cluster_center[i] = arr[r];
    }

    for(int i=0;i<k;i++) {
        cout<<cluster_center[i].x<<" "<<cluster_center[i].y
<<endl;    
    }

    for(int i=0;i<10;i++) {
        clustering(arr, cluster_center);
        updateclust_center(arr, cluster_center);

        cout<<endl<<"Output After "<<i+1<<" iteration"<<endl;
    }

    ofstream out_file("output.csv");

    out_file<<"x"<<","<<"y"<<","<<"Cluster"<<endl;
    for(auto itr:arr){
        out_file<<itr.x<<","<<itr.y<<","<<itr.cluster+1<<endl;
    }
    return 0;
}