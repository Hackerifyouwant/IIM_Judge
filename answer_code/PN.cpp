#include<iostream>
#include<vector>

using namespace std;


int main(){
    int n, m, cnt;
    cin >> n >> m >> cnt;
    vector< vector <int > > martix(n, vector<int>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> martix[i][j];
        }
    }
    cnt %= 4;
    for(int s = 0; s < cnt; s++){
        vector< vector<int> >new_martix(m, vector<int>(n));
        for(int i = m - 1, k = 0; i >= 0 && k < m; i--, k++){
            for(int j = 0; j < n; j++){
                new_martix[k][j] = martix[j][i];
            }
        }
        swap(n , m);
        martix = new_martix;
    }

    for(auto c : martix){
        for(auto g : c){
            cout << g << " ";
        }
        cout << endl;
    }
    return 0;
}