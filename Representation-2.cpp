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

    // vec naam hai array ka and usme n+1 buckets hai and har bucket ek vector hai int ka n+1 kyuki 0 based ni hai nodes ke number 1 based hai
    // int arr[10] means 10 bucket hai sabme integer value stored
    // Adjacency list
    vi adj[n + 1];

    loop(i, 0, m)
    {
        int u, v;
        cin >> u >> v;

        adj[u].pb(v);

        // if directed hai toh iss line ki jarorat ni hai and SC O(e) and in case of undirected SC O(2*e)
        adj[v].pb(u);
    }

    loop(i, 1, n + 1)
    {
        cout << i << "-> ";
        loop(j, 0, adj[i].size())
        {
            cout << adj[i][j] << ", ";
        }
        cout << endl;
    }
    return 0;
}
/*
5 6
1 2
1 3
2 4
3 4
3 5
4 5


weighted hoga toh isme pair lelege vector<pair<int,int>> {node, weight}
*/
