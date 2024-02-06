#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <memory.h>
using namespace std;
struct info
{
    int x, y;
};
struct baseinfo
{
    int x, y, cnt;
};
struct moveInfo
{
    int x, y, cnt;
    string dir;
};

bool infoCMP(info o, info O)
{
    if (o.x < O.x)
    {
        return true;
    }
    else if (o.x == O.x && o.y < O.y)
    {
        return true;
    }

    return false;
}

info market[37];
info ppl[37];
set<int> inmap_ppl;
int visited[17][17];
int map[17][17];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
int N, M;

int isArea(int x, int y)
{
    return 0 < x && x <= N && 0 < y && y <= N;
}

void goMove()
{
    int stx, sty;
    queue<moveInfo> q;

    int x, y, cnt, xx, yy, ans;
    string d, dd, finaldir;
    int finald;

    for (auto p : inmap_ppl)
    {
        memset(visited, 0, sizeof(visited));
        ans = -1;
        finaldir = "";

        for (int i = 0; i < 4; i++)
        {
            x = ppl[p].x + dx[i];
            y = ppl[p].y + dy[i];
            dd = "";
            if (isArea(x, y) && map[x][y] != -1 && !visited[x][y])
            {
                dd += 'a' + i;
                q.push({x, y, 1, dd});
                visited[x][y] = 1;
            }
        }

        while (!q.empty())
        {
            x = q.front().x;
            y = q.front().y;
            cnt = q.front().cnt;
            d = q.front().dir;

            q.pop();

            if (x == market[p].x && y == market[p].y)
            {
                if (ans == -1)
                {
                    ans = cnt;
                    finald = d[0] - 'a';
                    finaldir = d;
                }
                else
                {
                    if (ans < cnt)
                    {
                        break;
                    }
                    else if (ans == cnt)
                    {
                        if (finaldir > d)
                        {
                            finald = d[0] - 'a';
                            finaldir = d;
                        }
                    }
                }
            }

            for (int i = 0; i < 4; i++)
            {
                xx = x + dx[i];
                yy = y + dy[i];
                if (isArea(xx, yy) && map[xx][yy] != -1 && !visited[xx][yy])
                {
                    dd = d;
                    dd += 'a' + i;
                    q.push({xx, yy, cnt + 1, dd});
                    visited[xx][yy] = 1;
                }
            }
        }

        x = ppl[p].x + dx[finald];
        y = ppl[p].y + dy[finald];

        ppl[p].x = x;
        ppl[p].y = y;

        while (!q.empty())
        {
            q.pop();
        }
    }

    set<int> tmpppl;
    for (auto p : inmap_ppl)
    {
        if (ppl[p].x == market[p].x && ppl[p].y == market[p].y)
        {
            map[market[p].x][market[p].y] = -1;
        }
        else
        {
            tmpppl.insert(p);
        }
    }
    inmap_ppl.clear();
    inmap_ppl = tmpppl;
    tmpppl.clear();
}

void goBase(int num)
{
    inmap_ppl.insert(num);
    memset(visited, 0, sizeof(visited));
    int stx, sty;
    stx = market[num].x;
    sty = market[num].y;

    queue<baseinfo> q;
    q.push({stx, sty, 0});
    visited[stx][sty] = 1;

    int x, y, cnt, xx, yy, ans;
    ans = -1;
    vector<info> closeBase;
    while (!q.empty())
    {
        x = q.front().x;
        y = q.front().y;
        cnt = q.front().cnt;

        q.pop();

        if (map[x][y] == 1)
        {
            if (ans == -1)
            {
                ans = cnt;
                closeBase.push_back({x, y});
            }
            else
            {
                if (ans < cnt)
                {
                    break;
                }
                else if (ans == cnt)
                {
                    closeBase.push_back({x, y});
                }
            }
        }

        for (int i = 0; i < 4; i++)
        {
            xx = x + dx[i];
            yy = y + dy[i];
            if (isArea(xx, yy) && map[xx][yy] != -1 && !visited[xx][yy])
            {
                q.push({xx, yy, cnt + 1});
                visited[xx][yy] = 1;
            }
        }
    }

    sort(closeBase.begin(), closeBase.end(), infoCMP);
    map[closeBase[0].x][closeBase[0].y] = -1;
    ppl[num].x = closeBase[0].x;
    ppl[num].y = closeBase[0].y;

    closeBase.clear();
    while (!q.empty())
    {
        q.pop();
    }
}

int main()
{
    cin.tie(NULL);
    cin.sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> map[i][j];
        }
    }

    int a, b;
    for (int i = 1; i <= M; i++)
    {
        cin >> a >> b;

        market[i].x = a;
        market[i].y = b;
    }

    int t = 0;
    while (1)
    {
        t++;
        goMove();
        if (t <= M)
        {
            goBase(t);
        }

        if (inmap_ppl.empty())
        {
            cout << t;
            break;
        }
    }
}