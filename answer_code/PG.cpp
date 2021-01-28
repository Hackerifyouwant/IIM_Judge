#include<iostream>

using namespace std;

int main(){
    int n, arr[105];
    int max = -1e9;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        if(arr[i] > max)max = arr[i];
    }
    cout << max << endl;
    
    return 0;
}