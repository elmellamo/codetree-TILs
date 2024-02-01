#include <iostream>
#include <deque>
#include <memory.h>
using namespace std;

struct dp
{
    int d, p;
};
struct fertilizer
{
    int x, y;
};

int N, M, dd, pp;
int map[17][17];
int visited[17][17];
int dx[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dy[9] = {0, 1, 1, 0, -1, -1, -1, 0, 1};
int ddx[4] = {-1, -1, 1, 1};
int ddy[4] = {-1, 1, 1, -1};
dp dpinfo[107];
deque<fertilizer> fert;

int isArea(int x, int y)
{
    return -1 < x && x < N && -1 < y && y < N;
}

void moveFert(int d, int p)
{
    int x, y;
    int orisize = fert.size();
    for (int i = 0; i < orisize; i++)
    {
        x = fert[0].x;
        y = fert[0].y;
        for (int P = 0; P < p; P++)
        {
            x += dx[d];
            y += dy[d];

            if (x == N)
            {
                x = 0;
            }
            if (y == N)
            {
                y = 0;
            }
            if (x == -1)
            {
                x = N - 1;
            }
            if (y == -1)
            {
                y = N - 1;
            }
        }
        fert.pop_front();
        fert.push_back({x, y});
    }
}

void growOne()
{
    for (auto i : fert)
    {
        map[i.x][i.y]++;
    }
}

void influenceGrow()
{
    int x, y, cnt;
    for (auto i : fert)
    {
        cnt = 0;
        for (int d = 0; d < 4; d++)
        {
            x = i.x + ddx[d];
            y = i.y + ddy[d];

            if (isArea(x, y) && map[x][y] > 0)
            {
                cnt++;
            }
        }
        map[i.x][i.y] += cnt;
        visited[i.x][i.y] = 1;
    }
}

void cutBuy()
{
    fert.clear();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] > 1 && !visited[i][j])
            {
                fert.push_back({i, j});
                map[i][j] -= 2;
            }
        }
    }
}

void solve(int d, int p)
{
    memset(visited, 0, sizeof(visited));
    moveFert(d, p);
    growOne();
    influenceGrow();
    cutBuy();
}

int howmuch()
{
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            ans += map[i][j];
        }
    }

    return ans;
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
            cin >> map[i][j];
        }
    }
    for (int m = 0; m < M; m++)
    {
        cin >> dd >> pp;
        dpinfo[m].d = dd;
        dpinfo[m].p = pp;
    }

    fert.push_back({N - 1, 0});
    fert.push_back({N - 1, 1});
    fert.push_back({N - 2, 0});
    fert.push_back({N - 2, 1});

    for (int m = 0; m < M; m++)
    {
        solve(dpinfo[m].d, dpinfo[m].p);
    }

    cout << howmuch();
}