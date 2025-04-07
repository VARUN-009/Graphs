#include <bits/stdc++.h>
using namespace std;

// Constants
const int MOD = 1e9 + 7;
#define ios                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0);

// Utils
#define int long long
#define vi vector<int>
#define vii vector<vector<int>>
#define vip vector<pair<int, int>>
#define pii pair<int, int>
#define len(x) (x).size()
#define pb push_back
#define all(n) n.begin(), n.end()
#define rall(n) n.rbegin(), n.rend()
#define stoi stoll

// Control Flow
#define loop(i, a, b) for (int i = a; i < (b); i++)
#define rloop(i, b, a) for (int i = (b); i >= a; i--)
#define trav(a, x) for (auto &a : x)

// Helper Functions
bool odd(int num) { return ((num & 1) == 1); }
bool even(int num) { return ((num & 1) == 0); }
int __lcm(int a, int b) { return (a * b) / __gcd(a, b); }

void vishu()
{
}

int32_t main()
{
    int n, m;
    cin >> n >> m;

    // vii vec(n+1, vi(n+1));
    int adj[n + 1][n + 1] = {0};

    // TC - O(m)
    loop(i, 0, m)
    {
        int u, v;
        cin >> u >> v;

        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    // Adjacency matrix
    loop(i, 0, n + 1)
    {
        loop(j, 0, n + 1)
        {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

/*

Weighted hoga toh 1 mark karne ki jagah bss uska weight likh dege and jo nhi hai usme -1 kardege ya 0 kyuki weight nhi hoga toh 1 leke chlege...
*/