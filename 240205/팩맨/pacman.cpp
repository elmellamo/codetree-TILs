#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct
{
    int fird, secd, third, cnt;
} monsterinfo;

bool cmp(monsterinfo o, monsterinfo O)
{
    if (O.cnt < o.cnt)
    {
        return true;
    }
    else if (O.cnt == o.cnt && o.fird < O.fird)
    {
        return true;
    }
    else if (O.cnt == o.cnt && o.fird == O.fird && o.secd < O.secd)
    {
        return true;
    }
    else if (O.cnt == o.cnt && o.fird == O.fird && o.secd == O.secd && o.third < O.third)
    {
        return true;
    }

    return false;
}
vector<int> monster[5][5];
vector<int> baby[5][5];
int packx, packy;
int map[5][5];

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int mx[4] = {-1, 0, 1, 0};
int my[4] = {0, -1, 0, 1};

int isArea(int x, int y)
{
    return 0 < x && x < 5 && 0 < y && y < 5;
}

int isMonster(int x, int y)
{
    return x == packx && y == packy;
}

void tryBorn()
{
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (!monster[i][j].empty())
            {
                for (auto mon : monster[i][j])
                {
                    baby[i][j].push_back(mon);
                }
            }
        }
    }
}

void moveMonster()
{
    vector<int> tmp[5][5];
    int x, y, d;

    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (!monster[i][j].empty())
            {
                for (auto mon : monster[i][j])
                {
                    d = mon;
                    for (int dd = 0; dd < 8; dd++)
                    {
                        x = i + dx[d];
                        y = j + dy[d];

                        if (isArea(x, y) && !isMonster(x, y) && map[x][y] == 0)
                        {
                            tmp[x][y].push_back(d);
                            break;
                        }
                        d = (d + 1) % 8;
                    }
                }
            }
            monster[i][j].clear();
        }
    }

    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (!tmp[i][j].empty())
            {
                monster[i][j] = tmp[i][j];
                tmp[i][j].clear();
            }
        }
    }
}

void packMove()
{
    int firx, firy, secx, secy, thirx, thiry, fircnt, seccnt, thircnt;
    vector<monsterinfo> info;

    for (int i = 0; i < 4; i++)
    {
        firx = packx + mx[i];
        firy = packy + my[i];

        if (isArea(firx, firy))
        {
            fircnt = monster[firx][firy].size();
            for (int j = 0; j < 4; j++)
            {
                secx = firx + mx[j];
                secy = firy + my[j];

                if (isArea(secx, secy))
                {
                    seccnt = monster[secx][secy].size();
                    for (int k = 0; k < 4; k++)
                    {
                        thirx = secx + mx[k];
                        thiry = secy + my[k];
                        if (isArea(thirx, thiry))
                        {
                            thircnt = monster[thirx][thiry].size();
                            info.push_back({i, j, k, fircnt + seccnt + thircnt});
                        }
                    }
                }
            }
        }
    }

    sort(info.begin(), info.end(), cmp);
    packx = packx + mx[info[0].fird];
    packy = packy + my[info[0].fird];
    if (!monster[packx][packy].empty())
    {
        map[packx][packy] = -3;
        monster[packx][packy].clear();
    }
    packx = packx + mx[info[0].secd];
    packy = packy + my[info[0].secd];
    if (!monster[packx][packy].empty())
    {
        map[packx][packy] = -3;
        monster[packx][packy].clear();
    }
    packx = packx + mx[info[0].third];
    packy = packy + my[info[0].third];
    if (!monster[packx][packy].empty())
    {
        map[packx][packy] = -3;
        monster[packx][packy].clear();
    }
}

void vanishDead()
{
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (map[i][j] < 0)
            {
                map[i][j]++;
            }
        }
    }
}

void doneBorn()
{
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (!baby[i][j].empty())
            {
                for (auto b : baby[i][j])
                {
                    monster[i][j].push_back(b);
                }
                baby[i][j].clear();
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    cin.sync_with_stdio(false);

    int M, T, tmpx, tmpy, tmpd;
    cin >> M >> T;
    cin >> packx >> packy;
    for (int i = 0; i < M; i++)
    {
        cin >> tmpx >> tmpy >> tmpd;
        monster[tmpx][tmpy].push_back(tmpd - 1);
    }

    for (int t = 0; t < T; t++)
    {
        tryBorn();
        moveMonster();
        packMove();
        vanishDead();
        doneBorn();
    }

    int ans = 0;
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            ans += monster[i][j].size();
        }
    }
    cout << ans;
}