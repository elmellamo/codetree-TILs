#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
using namespace std;

struct info
{
    int x, y;
};
struct qinfo
{
    int x, y, cnt;
};

queue<qinfo> q;
int N, M;
int orimap[57][57];
int copymap[57][57];
int visited[57][57];
int pickhospital[11];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int ans = -1;
vector<info> hospital;

int isArea(int x, int y)
{
    return -1 < x && x < N && -1 < y && y < N;
}

void printm()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << visited[i][j] << " ";
        }
        cout << "\n";
    }
}
int allDel()
{
    int maxcnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (copymap[i][j] == 0 && visited[i][j] == 0)
            {
                return 0;
            }

            if (copymap[i][j] == 0 && visited[i][j] > 0)
            {
                maxcnt = maxcnt > visited[i][j] ? maxcnt : visited[i][j];
            }
        }
    }

    return maxcnt;
}

void copyMap()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            copymap[i][j] = orimap[i][j];
        }
    }
}
void BFS()
{
    int x, y, xx, yy, cnt, tmp;
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < M; i++)
    {
        x = hospital[pickhospital[i]].x;
        y = hospital[pickhospital[i]].y;

        // cout << "x y" << x << "  " << y << "\n";
        for (int d = 0; d < 4; d++)
        {
            xx = x + dx[d];
            yy = y + dy[d];

            if (isArea(xx, yy) && copymap[xx][yy] != 1 && visited[xx][yy] == 0)
            {
                visited[xx][yy] = 1;
                // cout << "xx yy  " << xx << "  " << yy << "\n";
                q.push({xx, yy, 1});
            }
        }
    }

    while (!q.empty())
    {
        x = q.front().x;
        y = q.front().y;
        cnt = q.front().cnt;

        q.pop();

        for (int d = 0; d < 4; d++)
        {
            xx = x + dx[d];
            yy = y + dy[d];

            if (isArea(xx, yy) && copymap[xx][yy] != 1 && visited[xx][yy] == 0)
            {
                q.push({xx, yy, cnt + 1});
                visited[xx][yy] = cnt + 1;
                // cout << "xx yy  " << xx << "  " << yy << "\n";
            }
        }
    }

    int tmpans;
    tmpans = allDel();
    if (tmpans > 0)
    {
        // cout << "tmpans >>> " << tmpans << "\n";
        if (ans == -1)
        {
            ans = tmpans;
        }
        else
        {
            ans = ans < tmpans ? ans : tmpans;
        }
    }
}

void solve(int pos, int depth)
{
    if (depth == M)
    {
        copyMap();
        BFS();
        // printm();
        // cout << "\n";
        return;
    }
    for (int next = pos + 1; next < hospital.size(); next++)
    {
        pickhospital[depth] = next;
        solve(next, depth + 1);
    }
}

int main()
{
    cin.tie(NULL);
    cin.sync_with_stdio(false);

    cin >> N >> M;

    int bacteria = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> orimap[i][j];
            if (orimap[i][j] == 2)
            {
                hospital.push_back({i, j});
            }
            else if (orimap[i][j] == 0)
            {
                bacteria = 1;
            }
        }
    }

    if (allDel())
    {
        cout << "0";
    }
    else if (bacteria == 0)
    {
        cout << "0";
    }
    else
    {

        solve(-1, 0);
        cout << ans;
    }
}