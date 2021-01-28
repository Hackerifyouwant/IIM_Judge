#include<iostream>
#include<stdlib.h>

using namespace std;

struct pos{
    int x;
    int y;
};

int n, min = 1e9;
int Map[10][10];
int way[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int vis[10][10] = {};
bool flag = 0;


void DFS(pos S, pos E){
    vis[S.x][S.y] = 1;
    if(S.x == E.x && S.y == E.y)flag = 1;
    for(int i = 0; i < 4; i++){
        int nx = S.x + way[i][0];
        int ny = S.y + way[i][1];
        if((nx >= 0 && nx < n && ny >= 0 && ny < n) && Map[nx][ny] == 0 && vis[nx][ny] == 0){
            pos tmp;
            tmp.x = nx;
            tmp.y = ny;
            DFS(tmp, E);
        }
    }
}


int main(){
    pos start, end;
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> Map[i][j]; 
        }
    }
    
    cin >> start.x >> start.y >> end.x >> end.y;
    DFS(start, end);
    if(flag == 1){
        cout << "Exist" << endl;
    }else{
        cout << "None" << endl;
    }
    
    return 0;
}