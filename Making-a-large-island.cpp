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
    int largestIsland(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        DisjointSet ds(n * m);
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        // visited lene ki need nhi hai tumne jo pehle se le rakha hai vo phirse
        // join karoge toh phir direct hi return ho jayega kyuki ultimate parent
        // same hi niklega bss grid ka vo cell 0 nhi hona chahiye and uske
        // adjacent 1 hone chahiye
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < m; col++)
            {
                if (grid[row][col] == 0)
                    continue;
                int cell = row * n + col;
                for (int k = 0; k < 4; k++)
                {
                    int adjrow = row + dx[k];
                    int adjcol = col + dy[k];
                    if (isValid(adjrow, adjcol, n, m) &&
                        grid[adjrow][adjcol] == 1)
                    {
                        // connect kardo bss ek hi component m
                        int node = adjrow * n + adjcol;
                        ds.unionBySize(cell, node);
                    }
                }
            }
        }

        int ans = INT_MIN;
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < m; col++)
            {
                if (grid[row][col] == 1)
                    continue;
                int cell = row * n + col;
                set<int> components;
                for (int k = 0; k < 4; k++)
                {
                    int nrow = row + dx[k];
                    int ncol = col + dy[k];

                    // set lena padega kyuki same cell phir se count kar sakte
                    // ho jiska parent ek hi hai toh set m dalo ki 1 bss 1 hi
                    // baar count ho
                    if (isValid(nrow, ncol, n, m) && grid[nrow][ncol] == 1)
                    {
                        int ult = ds.findUltimateParent(nrow * n + ncol);
                        components.insert(ult);
                    }
                }

                int sum = 0;
                for (auto ele : components)
                {
                    sum += ds.size[ele];
                }

                ans = max(ans, sum + 1);
            }
        }

        // agr mere pass saare hi 1 hai means no 0 toh m saare ke saare 1 le
        // sakta hu toh n*m.
        return ans == INT_MIN ? n * m : ans;
    }
};

/*
TC - O(n*m*4) DSU O(1) + O(n*m*4*logn) but set taken logn to insert and we can also take unordered set to make it O(1) so all around O(n*m) 
SC - O(n) + O(n)
*/