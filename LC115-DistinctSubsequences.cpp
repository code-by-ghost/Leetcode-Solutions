// Given two strings s and t, return the number of distinct subsequences of s which equals t.
//The test cases are generated so that the answer fits on a 32-bit signed integer.
class Solution {
private:

    // Step 1: Recursive Solution
    int solve(int i, int j, string& s, string& t){
        // If j == t.size(), all chars of t have been matched
        if(j==t.size()) return 1;
        // If i==s.size(), all chars of s have been exhausted, we cannot form
        if(i==s.size()) return 0;

        // If the current char is matching, we can either pick it or not pick it;
        if(s[i]==t[j])
            return solve(i+1, j+1, s, t) + solve(i+1, j, s, t);
        else // Not matching, we cannot pick it
            return solve(i+1, j, s, t);
    }

    // Step 2: Memoization Solution -> Try to remove the overlapping recursion calls
    int solveDP(int i, int j, string& s, string& t, vector<vector<int>>& dp){
        // If j == t.size(), all chars of t have been matched
        if(j==t.size()) return 1;
        // If i==s.size(), all chars of s have been exhausted, we cannot form
        if(i==s.size()) return 0;

        // If this state has already been seen, return the stored state
        if(dp[i][j]!=-1) return dp[i][j];

        // If the current char is matching, we can either pick it or not pick it;
        if(s[i]==t[j])
            // Store the current state
            return dp[i][j] = solveDP(i+1, j+1, s, t, dp) + solveDP(i+1, j, s, t, dp);
        else // Not matching, we cannot pick it
            // Store the current state
            return dp[i][j] = solveDP(i+1, j, s, t, dp);
    }

    // Step 3: Tabulation (Bottom-Up DP) -> Remove the recursion stack space
    int solveTab(string& s, string& t){
        int m = s.size();
        int n = t.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        
        // Set the base case: All chars of t has been matched
        for(int i=0; i<m+1; i++)
            dp[i][n] = 1;

        // Reverse the recursive loop to start from the bottom
        for(int i=m-1; i>=0; i--){
            for(int j=n-1; j>=0; j--){
                // If the current char is matching, we can either pick it or not pick it;
                if(s[i]==t[j]){
                    // Use the prev computed state to simulate the recursive function call
                    // To prevent overflow error in C++
                    long long tmp = (long long)dp[i+1][j+1] + (long long)dp[i+1][j];
                    dp[i][j] = (int)tmp;
                }
                else
                    dp[i][j] = dp[i+1][j];
            }
        }

        // Return the index with which we made the function call in recursive
        return dp[0][0];
    }

    // Step 4: Space Optimize Tabulation -> Take down space from O(n*n) to O(n)
    int solveTabOpt(string& s, string& t){
        int m = s.size();
        int n = t.size();
        // The vector stores the next state (j+1)
        vector<int> next(n+1, 0);
        // All chars of t were matched
        next[n] = 1;
        
        // Reverse the recursive loop to start from the bottom
        for(int i=m-1; i>=0; i--){
            // Vector to store the current state represented by dp[i]
            vector<int> cur(n+1, 0);
            // All chars of t are matched
            cur[n] = 1;
            for(int j=n-1; j>=0; j--){
                // If the current char is matching, we can either pick it or not pick it;
                if(s[i]==t[j]){
                    // To prevent overflow error in C++
                    long long tmp = (long long)next[j] + (long long)next[j+1];
                    cur[j] = (int)tmp;
                }
                else{
                    cur[j] = next[j];
                }
            }
            // Rollover the current state to the next state to compute further
            next = cur;
        }

        // Return the index we started the recursive call with
        return next[0];
    }

    // Step 5: Space Optimize Tabulation -> Single array DP
    int solveTabOptSingle(string& s, string& t){
        int m = s.size();
        int n = t.size();
        // The vector stores the next state (j+1)
        vector<int> next(n+1, 0);
        // All chars of t were matched
        next[n] = 1;
        
        // Reverse the recursive loop to start from the bottom
        for(int i=m-1; i>=0; i--){
            // Ensures the previous state isn't overwritten
            for(int j=0; j<=n-1; j++){
                // If the current char is matching, we can either pick it or not pick it;
                if(s[i]==t[j]){
                    // To prevent overflow error in C++
                    long long tmp = (long long)next[j] + (long long)next[j+1];
                    next[j] = (int)tmp;
                }
            }
        }

        // Return the index we started the recursive call with
        return next[0];
    }
        
public:
    int numDistinct(string s, string t) {
        // vector<vector<int>> dp(s.size(), vector<int>(t.size(), -1));
        // return solveDP(0, 0, s, t, dp);
        return solveTabOptSingle(s, t);
    }
};
