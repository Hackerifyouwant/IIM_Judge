#include<iostream>
#include<queue>
#include<stdlib.h>

using namespace std;

struct pos{
    int x;
    int y;
};

queue<pos> Q;

int main(){
    int n, min = 1e9;
    pos start, end;
    int Map[10][10] = {};
    int way[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int vis[10][10] = {};
    int pace[10][10] = {};
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> Map[i][j];
        }
    }
    
    
    cin >> start.x >> start.y >> end.x >> end.y;
    Q.push(start);
    vis[start.x][start.y] = 1;
    pace[start.x][start.y] = 0;
    while(!Q.empty()){
        pos FT = Q.front();
        Q.pop();
        for(int i = 0; i < 4; i++){
            int nx = FT.x + way[i][0];
            int ny = FT.y + way[i][1];
            if((nx >= 0 && nx < n && ny >= 0 && ny < n) && vis[nx][ny] == 0 && Map[nx][ny] == 0){
                pos tmp;
                tmp.x = nx;
                tmp.y = ny;
                Q.push(tmp);
                vis[tmp.x][tmp.y] = 1;
                if(pace[nx][ny] > pace[FT.x][FT.y] + 1 || pace[nx][ny] == 0){
                    pace[nx][ny] = pace[FT.x][FT.y] + 1;
                }
            }
        }
    }
    cout << pace[end.x][end.y] << endl;
    return 0;
}