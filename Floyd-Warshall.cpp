// Initial template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function template for C++

class Solution
{
public:
    void shortestDistance(vector<vector<int>> &mat)
    {
        // Code here
        int n = mat.size();

        // jahan pe nhi pahoch sakte wahan ka distance hume sabse jayda karna padega na tab hi toh minimum nikal payege so that's why 1e9. INT_MAX kardoge toh agr kabhi INT_MAX + 1 kara toh vo negative bn jayega toh dikkat ho jati hai. INT_MAX bhi kar sakte hai isme. Is ques m jahan ni jaa sakte usko -1 kardiya hai.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] == -1)
                {
                    mat[i][j] = 1e9;
                }
            }
        }

        for (int via = 0; via < n; via++)
        {

            // this loop is for rows
            for (int i = 0; i < n; i++)
            {

                // this loop is for cols
                for (int j = 0; j < n; j++)
                {
                    // agr jiske through jane ki soch rahe ho rasta hi ni hai toh jaa hi ni paoge na toh pehle hi if se check karlo. mat[i][j] != 1e9 check karne ki need ni hai kyuki abhi ho sakta hai ki 1e9 ho par baad m kya pta kisi aur nodes ke through raasta mil jaye. 
                    if ((mat[i][via] != 1e9 && mat[via][j] != 1e9))
                    {
                        mat[i][j] = min(mat[i][j], mat[i][via] + mat[via][j]);
                    }
                }
            }
        }

        // This part is only to check whether the graph has negative cycle or not basically whether the edges weights are negative or not.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] < 0)
                {
                    cout << "Negative weights OR Negative cycle detected.";
                    return;
                }
            }
        }

        // ye bss question m aisa hai toh iss karke karna padd rha hai ki 1e9 ki jagah -1 kardiya.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] == 1e9)
                {
                    mat[i][j] = -1;
                }
            }
        }
    }
};

//{ Driver Code Starts.
int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int n;
        cin >> n;
        vector<vector<int>> matrix(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> matrix[i][j];
            }
        }
        Solution obj;
        obj.shortestDistance(matrix);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << "\n";
        }

        cout << "~"
             << "\n";
    }
    return 0;
}