#include<iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    int x;
    for(int i = 0; i < n; i++){
        cin >> x;
        if(0 < x && x < 10)cout << "C" << endl;
        else if(10 <= x && x < 60) cout << "B" << endl;
        else cout << "A" << endl;
    }


    return 0;
}