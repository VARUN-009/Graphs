class Solution
{
public:
    int ladderLength(string beginWord, string endWord,
                     vector<string> &wordList)
    {

        int sz = wordList.size();
        int steps = 1;

        // Taken unordered set as it will reduce TC as compared to a vector and
        // also as compared to a set. set takes O(n) and unordered takes O(1)
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<string> q;
        q.push(beginWord);
        while (!q.empty())
        {

            int n = q.size();
            for (int i = 0; i < n; i++)
            {
                auto word = q.front();
                q.pop();

                if (word == endWord)
                {
                    return steps;
                }

                // jo word liya hai usko hta do as uski need ni hai ab warna
                // repeat ho jayegi cheeje
                st.erase(word);

                // ab bss ek ek karke uss word ke indexes m jao and sabme a to z
                // laga ke dekho agr aisa word bana jo mera hai set m means ki
                // possible word hai m jaa sakta hu isme.
                for (int k = 0; k < word.size(); k++)
                {
                    // string str = word;
                    char ch = word[k];
                    for (char j = 'a'; j <= 'z'; j++)
                    {
                        word[k] = j;
                        if (st.find(word) != st.end())
                        {
                            q.push(word);
                        }
                    }

                    // aage jane se pehle, pehle wale ko same karna hai toh
                    // that's why
                    word[k] = ch;
                }
            }

            // steps lene padege and queue ke andar alg se loop as 1 step m m ek
            // index change kar sakta hu toh jitne possible bane unko lelo and
            // then unko daaldo queue m so that you can traverse in every
            // possible word.
            steps++;
        }

        return 0;
    }
};

/*
TC - O(N * n*26 * 1) N becasue jitne possible words hai utne hi jayege na queue m
faltu jayega hi ni mera and uss word ka size * 26 SC - O(N) + O(N) -- logn if using set
Unordered Set (Hash Table):

Insertion: O(1) average, O(n) worst.

Search: O(1) average, O(n) worst.

Deletion: O(1) average, O(n) worst.

Ordered Set (Balanced BST/Skip List):

Insertion: O(log n).

Search: O(log n).

Deletion: O(log n). 
*/
