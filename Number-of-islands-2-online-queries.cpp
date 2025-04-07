class DisjointSet
{
public:
    vector<int> size;
    vector<int> parent;
    vector<int> rank;

    DisjointSet(int n)
    {
        size.resize(n + 1, 1);
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int findUltimateParent(int node)
    {
        // base case
        if (parent[node] == node)
        {
            return node;
        }

        // recursive case
        return parent[node] = findUltimateParent(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        int ultimate_parent_u = findUltimateParent(u);
        int ultimate_parent_v = findUltimateParent(v);

        if (ultimate_parent_u == ultimate_parent_v)
        {
            return;
        }

        if (rank[ultimate_parent_u] > rank[ultimate_parent_v])
        {
            parent[ultimate_parent_v] = ultimate_parent_u;
        }
        else if (rank[ultimate_parent_v] > rank[ultimate_parent_u])
        {
            parent[ultimate_parent_u] = ultimate_parent_v;
        }

        else
        {
            parent[ultimate_parent_v] = ultimate_parent_u;
            rank[ultimate_parent_u]++;
        }
    }

    void unionBySize(int u, int v)
    {
        int ult_par_u = findUltimateParent(u);
        int ult_par_v = findUltimateParent(v);

        if (ult_par_u == ult_par_v)
        {
            return;
        }
        else if (size[ult_par_u] > size[ult_par_v])
        {
            parent[ult_par_v] = ult_par_u;
            size[ult_par_u] += size[ult_par_v];
        }
        else
        {
            parent[ult_par_u] = ult_par_v;
            size[ult_par_v] += size[ult_par_u];
        }
    }
};

class Solution
{
private:
    bool isValid(int i, int j, int n, int m)
    {
        return i >= 0 && i < n && j >= 0 && j < m;
    }

public:
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators)
    {
        // n*m jiss se ki m har cell ka as a node consider karke usko DSU m node ki tarah connect karlu using Row*m + col toh meri nodes bn jayegi kyuki cell ko m DSU m directly ni add kar sakta
        DisjointSet ds(n * m);
        int vis[n][m]; 
        // always use memset as  = {0} bss pehli hi bucket ko 0 kardega baaki ki ni
        memset(vis, 0, sizeof(vis));
        vector<int> ans;
        int count = 0;
        for (auto &op : operators)
        {
            int row = op[0];
            int col = op[1];

            // already visited hai kaam ho chuka hai toh current count dalo ans m and aage badho
            if (vis[row][col] == 1)
            {
                ans.push_back(count);
                continue;
            }
            count++;
            vis[row][col] = 1;
            int dx[] = {-1, 0, 1, 0};
            int dy[] = {0, 1, 0, -1};

            for (int i = 0; i < 4; i++)
            {
                int adjRow = row + dx[i];
                int adjCol = col + dy[i];

                // m har cell ko ek node number bna rha hu by the formula nodeRow = i * row + col toh iss se meri nodes 0 to n*m-1 tak rahegi...toh current cell ko m aas pass walo se check karunga ki connected hai ya ni via DSU, toh node will have a number by this formula.
                if (isValid(adjRow, adjCol, n, m))
                {
                    // agr 1 hai means ki vo visited hai pehle se toh current cell and neighbour cell agr mere connected hai dono means m inko connect kar sakta hu toh ek hi kardeta hu na join
                    if (vis[adjRow][adjCol] == 1)
                    {
                        // check karo ki DSU m ye aur adj node connected toh nhi hai na
                        int node = row * m + col;
                        int adjNode = adjRow * m + adjCol;
                        if (ds.findUltimateParent(adjNode) != ds.findUltimateParent(node))
                        {
                            count--;
                            ds.unionBySize(adjNode, node);
                        }
                    }
                }
            }

            ans.push_back(count);
        }

        return ans;
    }
};


#include <bits/stdc++.h>
using namespace std;

int main()
{

    return 0;
}

/*
Whenever you are connecting, DSU as dynamic graph is there.

*/