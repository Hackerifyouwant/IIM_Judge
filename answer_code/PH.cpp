#include<iostream>

using namespace std;

int main(){
    int price, pay;
    int coin[4] = {50, 10, 5, 1};
    int cnt[4] = {};
    cin >> price >> pay;
    int num = pay - price;
    for(int i = 0; i < 4; i++){
        cnt[i] = num / coin[i];
        num %= coin[i];
    }
    for(int i = 3; i >= 0; i--){
        cout << coin[i] << " " << cnt[i] << endl;
    }
    

    return 0;
}