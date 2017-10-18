#include<iostream>
#include<queue>
#include <cstring>

using namespace std;


struct state{
    int x, y, xb, yb;
    state(int x, int y, int xb, int yb) :x(x), y(y), xb(xb), yb(yb){}
};

class Solution{
public:
    Solution();
    void initial();
    int bfs();
private:
    char mp[10][10];
    int n, m;
    int sx,sy,bx,by,ex,ey;
    int a[4], b[4];
    int visited[10][10][10][10];
};

Solution::Solution(){
    a[0] = 0, a[1] = 0, a[2] = 1, a[3] = -1;
    b[0] = 1, b[1] = -1, b[2] = 0, b[3] = 0;
    memset(visited, 0, sizeof(visited));
}

void Solution::initial(){
    cin >> n >> m;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cin >> mp[i][j];
            if (mp[i][j] == 'O'){ bx = i, by = j; }
            else if (mp[i][j] == 'S')sx = i, sy = j;
            else if (mp[i][j] == 'E')ex = i, ey = j;
        }
    }
}

int Solution::bfs(){
    visited[sx][sy][bx][by] = 1;
    state s(sx,sy,bx,by);
    queue<state> que;
    que.push(s);
    while (que.size()){
        state front = que.front();
        que.pop();
        if (front.xb == ex && front.yb == ey) return visited[front.x][front.y][front.xb][front.yb] - 1;
        for (int i = 0; i < 4; ++i){
            int nx = front.x + a[i], ny = front.y + b[i];
            if (nx<0 || ny<0 || mp[nx][ny] == '#' || nx >= n || ny >= m)continue;
            if (nx == front.xb && ny == front.yb){
                if (nx + a[i]<0 || ny + b[i]<0 || mp[nx + a[i]][ny + b[i]] == '#' || nx + a[i] >= n || ny + b[i] >= m)continue;
                if (visited[nx][ny][nx + a[i]][ny + b[i]]) continue;
                visited[nx][ny][nx + a[i]][ny + b[i]] = visited[front.x][front.y][front.xb][front.yb] + 1;
                que.push(state(nx,ny,nx+a[i],ny+b[i]));
            }else{
                if (visited[nx][ny][front.xb][front.yb]) continue;
                visited[nx][ny][front.xb][front.yb] = visited[front.x][front.y][front.xb][front.yb] + 1;
                que.push(state(nx, ny, front.xb, front.yb));
            }
        }
    }
    return -1;
}

int main()
{
    Solution obj;
    obj.initial();
    cout << obj.bfs() << endl;
    return 0;
}