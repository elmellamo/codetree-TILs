#include <iostream>
#include <queue>
#include <set>
using namespace std;

int N, M, ST;
set<int> v[1007];
int visited[1007];
int dfsvisited[1007];

void DFS(int pos)
{
    dfsvisited[pos] = 1;
    cout << pos << " ";

    for (auto i : v[pos])
    {
        if (!dfsvisited[i])
        {
            DFS(i);
        }
    }
}

void BFS()
{
    int x;
    queue<int> q;
    q.push(ST);
    visited[ST] = 1;

    while (!q.empty())
    {
        x = q.front();
        q.pop();
        cout << x << " ";

        for (auto i : v[x])
        {
            if (!visited[i])
            {
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    cin.sync_with_stdio(false);

    cin >> N >> M >> ST;
    int a, b;
    for (int i = 0; i < M; i++)
    {
        cin >> a >> b;
        v[a].insert(b);
        v[b].insert(a);
    }

    DFS(ST);
    cout << "\n";
    BFS();
}