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

int allDel()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (copymap[i][j] == 0 && visited[i][j] == 0)
            {
                return 0;
            }
        }
    }

    return 1;
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
    int x, y, xx, yy, cnt;
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < M; i++)
    {
        x = hospital[pickhospital[i]].x;
        y = hospital[pickhospital[i]].y;

        for (int d = 0; d < 4; d++)
        {
            xx = x + dx[d];
            yy = y + dy[d];

            if (isArea(xx, yy) && copymap[xx][yy] == 0 && visited[xx][yy] == 0)
            {
                visited[xx][yy] = 1;
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

            if (isArea(xx, yy) && copymap[xx][yy] == 0 && visited[xx][yy] == 0)
            {
                q.push({xx, yy, cnt + 1});
                visited[xx][yy] = cnt + 1;
            }
        }
    }

    if (allDel())
    {
        if (ans == -1)
        {
            ans = cnt;
        }
        else
        {
            ans = ans < cnt ? ans : cnt;
        }
    }
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
void solve(int pos, int depth)
{
    if (depth == M)
    {
        copyMap();
        BFS();
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
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> orimap[i][j];
            if (orimap[i][j] == 2)
            {
                hospital.push_back({i, j});
            }
        }
    }

    solve(-1, 0);
    cout << ans;
}