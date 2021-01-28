#include<iostream>

using namespace std;

int main(){
    int x, n;
    double sum = 0;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> x;
        sum += x;   
    }
    sum /= n;
    cout << sum << endl;
    
    return 0;
}