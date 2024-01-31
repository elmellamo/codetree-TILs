#include <iostream>
#include <memory.h>
#include <vector>
using namespace std;
/*
여기서 쓰이진 않았지만 vector를 정렬할 때는
sort(v.begin(), v.end(), compare);
이렇게 하고, 소문자가 앞에 온다.
#include <algorithm>

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
*/

struct delinfo
{
    int x, y, delans;
};
struct info
{
    int x, y;
};

int N, M, K, C, ans;
int map[27][27];
int visited[27][27];
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
            if (map[i][j] > 0)
            {
                tmp = 0;
                for (int d = 0; d < 4; d++)
                {
                    xx = i + dx[d];
                    yy = j + dy[d];

                    if (isArea(xx, yy) && map[xx][yy] > 0)
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
            if (map[i][j] > 0)
            {
                growtmp.clear();
                howmuch = 0;
                for (int d = 0; d < 4; d++)
                {
                    xx = i + dx[d];
                    yy = j + dy[d];

                    if (isArea(xx, yy) && map[xx][yy] == 0 && visited[xx][yy] == 0)
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
    delinfo delmax;
    delmax.delans = 0;
    delmax.x = 0;
    delmax.y = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] > 0)
            {
                deltmp = map[i][j];

                for (int d = 0; d < 4; d++)
                {
                    xx = i;
                    yy = j;
                    for (int k = 0; k < K; k++)
                    {
                        xx = xx + ddx[d];
                        yy = yy + ddy[d];
                        if (isArea(xx, yy) && map[xx][yy] > 0)
                        {
                            deltmp += map[xx][yy];
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                if (deltmp > delmax.delans)
                {
                    delmax.delans = deltmp;
                    delmax.x = i;
                    delmax.y = j;
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (visited[i][j] > 0)
            {
                visited[i][j] -= 1;
            }
        }
    }

    if (delmax.delans != 0)
    {
        ans += map[delmax.x][delmax.y];
        map[delmax.x][delmax.y] = -(C);

        for (int d = 0; d < 4; d++)
        {
            xx = delmax.x;
            yy = delmax.y;
            for (int k = 0; k < K; k++)
            {
                xx = xx + ddx[d];
                yy = yy + ddy[d];

                if (isArea(xx, yy))
                {
                    if (map[xx][yy] > 0)
                    {
                        ans += map[xx][yy];
                        map[xx][yy] = 0;
                        visited[xx][yy] = C;
                    }
                    else if (map[xx][yy] == 0)
                    {
                        map[xx][yy] = 0;
                        visited[xx][yy] = C;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
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