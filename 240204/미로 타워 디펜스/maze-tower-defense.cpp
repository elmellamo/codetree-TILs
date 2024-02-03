#include <iostream>
#include <memory.h>
#include <vector>
using namespace std;

struct attack
{
    int d, p;
};

int N, M;
int map[27][27];
vector<attack> store_attack;
vector<int> monster;
int ans;
int adx[4] = {0, 1, 0, -1};
int ady[4] = {1, 0, -1, 0};
int cdx[4] = {1, 0, -1, 0};
int cdy[4] = {0, 1, 0, -1};

int isArea(int x, int y)
{
    return -1 < x && x < N && -1 < y && y < N;
}

int isEmpty()
{
    int emptykey = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] > 0)
            {
                emptykey = 0;
                break;
            }
        }
        if (emptykey == 0)
        {
            break;
        }
    }

    return emptykey;
}

int destroyMap(int m)
{
    int cnt = 0;
    int x, y;
    x = N / 2;
    y = N / 2;
    int d = store_attack[m].d;
    for (int i = 0; i < store_attack[m].p; i++)
    {
        x = x + adx[d];
        y = y + ady[d];
        if (isArea(x, y) && map[x][y] > 0)
        {
            // cout << "destroy >> " << map[x][y] << "\n";
            ans += map[x][y];
            map[x][y] = 0;
            cnt++;
        }
        else
        {
            break;
        }
    }

    return cnt;
}
void printm()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

void goAroundMap(int howmany)
{
    int cnt = howmany;
    int x, y, d, repeat, gokey;
    x = (N / 2);
    y = (N / 2) - 1;
    d = 0;
    if (isArea(x, y) && (map[x][y] > 0 || (map[x][y] == 0 && cnt > 0)))
    {
        if (map[x][y] == 0 && cnt > 0)
        {
            cnt--;
        }
        else
        {
            // cout << map[x][y] << " ";
            monster.push_back(map[x][y]);
        }

        x = x + cdx[d];
        y = y + cdy[d];
        if (isArea(x, y) && (map[x][y] > 0 || (map[x][y] == 0 && cnt > 0)))
        {
            if (map[x][y] == 0 && cnt > 0)
            {
                cnt--;
            }
            // cout << map[x][y] << " ";
            monster.push_back(map[x][y]);

            repeat = 1;
            gokey = 1;

            while (isArea(x, y) && (map[x][y] > 0 || (map[x][y] == 0 && cnt > 0)) && gokey)
            {
                repeat++;
                d = (d + 1) % 4;
                for (int i = 0; i < repeat; i++)
                {
                    x = x + cdx[d];
                    y = y + cdy[d];
                    if (isArea(x, y))
                    {
                        if (map[x][y] > 0)
                        {
                            // cout << map[x][y] << " ";
                            monster.push_back(map[x][y]);
                        }
                        else if (map[x][y] == 0 && cnt > 0)
                        {
                            cnt--;
                        }
                    }
                    else
                    {
                        gokey = 0;
                        break;
                    }
                }

                if (gokey)
                {
                    d = (d + 1) % 4;
                    for (int i = 0; i < repeat; i++)
                    {
                        x = x + cdx[d];
                        y = y + cdy[d];
                        if (isArea(x, y))
                        {
                            if (map[x][y] > 0)
                            {
                                // cout << map[x][y] << " ";
                                monster.push_back(map[x][y]);
                            }
                            else if (map[x][y] == 0 && cnt > 0)
                            {
                                cnt--;
                            }
                        }
                        else
                        {
                            gokey = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
}

int removeMany()
{
    int gokey = 1;
    vector<int> tmp;
    int samecnt = 1;
    int st = monster[0];

    for (int i = 1; i < monster.size(); i++)
    {
        if (i == monster.size() - 1)
        {
            if (st == monster[i])
            {
                samecnt++;
                if (samecnt >= 4)
                {
                    // cout << "remove Many >>  samecnt" << samecnt << "   st " << st << " >>> " << samecnt * st << "\n";
                    ans += (samecnt * st);
                    gokey = 0;
                }
                else
                {
                    for (int tt = 0; tt < samecnt; tt++)
                    {
                        tmp.push_back(st);
                    }
                }
            }
            else
            {
                if (samecnt >= 4)
                {
                    // cout << "remove Many >>  samecnt" << samecnt << "   st " << st << " >>> " << samecnt * st << "\n";
                    ans += (samecnt * st);
                    gokey = 0;
                }
                else
                {
                    for (int tt = 0; tt < samecnt; tt++)
                    {
                        tmp.push_back(st);
                    }
                    tmp.push_back(monster[i]);
                }
            }
        }
        else
        {
            if (st == monster[i])
            {
                samecnt++;
            }
            else
            {
                if (samecnt >= 4)
                {
                    // cout << "remove Many >>  samecnt" << samecnt << "   st " << st << " >>> " << samecnt * st << "\n";
                    ans += (samecnt * st);
                    gokey = 0;
                }
                else
                {
                    for (int tt = 0; tt < samecnt; tt++)
                    {
                        tmp.push_back(st);
                    }
                }

                st = monster[i];
                samecnt = 1;
            }
        }
    }

    monster.clear();
    monster = tmp;

    return gokey;
}
void printmonster()
{
    cout << "MONSTER ~~~~~~\n";
    for (auto i : monster)
    {
        cout << i << " ";
    }
    cout << "\n";
}

void carveMap()
{
    memset(map, 0, sizeof(map));
    int x, y, d, repeat, gokey;
    int i = 0;
    x = (N / 2);
    y = (N / 2) - 1;
    d = 0;
    gokey = 1;
    repeat = 1;

    // cout << "map " << x << " , " << y << "  >> monster[" << i << "] " << monster[i] << "\n";
    map[x][y] = monster[i];
    i++;

    x = x + cdx[d];
    y = y + cdy[d];
    if (isArea(x, y) && i < monster.size())
    {
        // cout << "map " << x << " , " << y << "  >> monster[" << i << "] " << monster[i] << "\n";
        map[x][y] = monster[i];
        i++;
        while (isArea(x, y) && i < monster.size() && gokey)
        {
            repeat++;
            d = (d + 1) % 4;
            for (int repi = 0; repi < repeat; repi++)
            {
                x = x + cdx[d];
                y = y + cdy[d];
                if (isArea(x, y) && i < monster.size())
                {
                    // cout << "map " << x << " , " << y << "  >> monster[" << i << "] " << monster[i] << "\n";
                    map[x][y] = monster[i];
                    i++;
                }
                else
                {
                    gokey = 0;
                    break;
                }
            }

            if (gokey)
            {
                d = (d + 1) % 4;
                for (int repi = 0; repi < repeat; repi++)
                {
                    x = x + cdx[d];
                    y = y + cdy[d];
                    if (isArea(x, y) && i < monster.size())
                    {
                        // cout << "map " << x << " , " << y << "  >> monster[" << i << "] " << monster[i] << "\n";
                        map[x][y] = monster[i];
                        i++;
                    }
                    else
                    {
                        gokey = 0;
                        break;
                    }
                }
            }
        }
    }
}

void matchMonster()
{
    vector<int> tmp;
    int samecnt = 1;
    int st = monster[0];

    for (int i = 1; i < monster.size(); i++)
    {
        if (i == monster.size() - 1)
        {
            if (st == monster[i])
            {
                samecnt++;

                tmp.push_back(samecnt);
                tmp.push_back(st);
            }
            else
            {
                tmp.push_back(samecnt);
                tmp.push_back(st);

                tmp.push_back(1);
                tmp.push_back(monster[i]);
            }
        }
        else
        {
            if (st == monster[i])
            {
                samecnt++;
            }
            else
            {
                tmp.push_back(samecnt);
                tmp.push_back(st);

                st = monster[i];
                samecnt = 1;
            }
        }
    }

    monster.clear();
    monster = tmp;
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

    int dd, pp;
    for (int i = 0; i < M; i++)
    {
        cin >> dd >> pp;
        store_attack.push_back({dd, pp});
    }

    int howmanyDel = 0;
    int removemore = 0;
    for (int t = 0; t < M; t++)
    {
        if (!isEmpty())
        {
            monster.clear();
            howmanyDel = destroyMap(t);
            // printm();

            // cout << "GOARUOUND\n";
            goAroundMap(howmanyDel);
            // cout << "\n";
            // printmonster();
            if (!monster.empty())
            {
                removemore = removeMany();
                // printmonster();
                while (!removemore)
                {
                    removemore = removeMany();
                    // printmonster();
                }
            }
            if (!monster.empty())
            {
                matchMonster();
                // printmonster();
                carveMap();
                // printm();
            }
        }
    }

    cout << ans;
}