#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>
using namespace std;

struct delinfo
{
    int x, y, delans;
};
struct info
{
    int x, y;
};

bool compare(delinfo o, delinfo O)
{
    if (O.delans < o.delans)
    {
        return true;
    }
    else if (O.delans == o.delans && o.x < O.x)
    {
        return true;
    }
    else if (O.delans == o.delans && o.x == O.x && o.y < O.y)
    {
        return true;
    }

    return false;
}

int N, M, K, C, ans;
int map[27][27];
int growmap[27][27];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int ddx[4] = {-1, -1, 1, 1};
int ddy[4] = {-1, 1, -1, 1};

int isArea(int x, int y)
{
    return -1 < x && x < N && -1 < y && y < N;
}

void growTree()
{
    int xx, yy, tmp;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] > 0 && map[i][j] < 101)
            {
                tmp = 0;
                for (int d = 0; d < 4; d++)
                {
                    xx = i + dx[d];
                    yy = j + dy[d];

                    if (isArea(xx, yy) && map[xx][yy] > 0 && map[xx][yy] < 101)
                    {
                        tmp++;
                    }
                }
                map[i][j] += tmp;
            }
        }
    }
}

void childTree()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            growmap[i][j] = 0;
        }
    }

    int xx, yy, howmuch;
    vector<info> growtmp;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] > 0 && map[i][j] < 101)
            {
                growtmp.clear();
                howmuch = 0;
                for (int d = 0; d < 4; d++)
                {
                    xx = i + dx[d];
                    yy = j + dy[d];

                    if (isArea(xx, yy) && map[xx][yy] == 0)
                    {
                        growtmp.push_back({xx, yy});
                    }
                }
                if (!growtmp.empty())
                {
                    howmuch = map[i][j] / growtmp.size();
                    for (info i : growtmp)
                    {
                        growmap[i.x][i.y] += howmuch;
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (growmap[i][j] > 0)
            {
                map[i][j] += growmap[i][j];
            }
        }
    }
}

void delTree()
{
    int deltmp, xx, yy;
    vector<delinfo> delmax;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] < 101)
            {
                deltmp = 0;
                if (map[i][j] > 0)
                {
                    deltmp = map[i][j];
                }
                for (int d = 0; d < 4; d++)
                {
                    xx = i;
                    yy = j;
                    for (int k = 0; k < K; k++)
                    {
                        xx = xx + ddx[d];
                        yy = yy + ddy[d];
                        if (isArea(xx, yy) && map[xx][yy] >= 0 && map[xx][yy] < 101)
                        {
                            deltmp += map[xx][yy];
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                delmax.push_back({i, j, deltmp});
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] < 0)
            {
                map[i][j] += 1;
            }
        }
    }

    if (!delmax.empty())
    {
        sort(delmax.begin(), delmax.end(), compare);

        ans += delmax[0].delans;
        map[delmax[0].x][delmax[0].y] = -(C);
        
        for (int d = 0; d < 4; d++)
        {
            xx = delmax[0].x;
            yy = delmax[0].y;
            for (int k = 0; k < K; k++)
            {
                xx = xx + ddx[d];
                yy = yy + ddy[d];

                if (isArea(xx, yy) && map[xx][yy] >= 0 && map[xx][yy] < 101)
                {
                    map[xx][yy] = -(C);
                }
                else if (isArea(xx, yy) && map[xx][yy] < 0)
                {
                    map[xx][yy] += -(C);
                }
                else
                {
                    break;
                }
            }
        }

        delmax.clear();
    }
}

int main()
{
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    cin >> N >> M >> K >> C;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == -1)
            {
                map[i][j] = 101;
            }
        }
    }

    for (int i = 0; i < M; i++)
    {
        growTree();
        childTree();
        delTree();
    }
    cout << ans;
}