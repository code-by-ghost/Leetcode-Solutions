// Leetcode Problem 1872: Daily Leetcode Problem for 24-08-2026

class Solution {
private:
    int solve(int ind, int n, vector<int> &prefixSum, vector<int> &dp){
        // if i is the last stone, we can return prefixSum[ind] as this is what would be added back
        if(ind==n-1) return prefixSum[ind];

        // If already computed, return
        if(dp[ind]!=-1) return dp[ind];

        // Take till the current index and pass to opponent
        int take = prefixSum[ind] - solve(ind+1, n, prefixSum, dp);
        // Skip to take till a later index
        int notTake = solve(ind+1, n, prefixSum, dp);

        // Maximize own score to maximize score or minimize opponent's score.
        return dp[ind] = max(take, notTake);
    }

    // Convert the memo into Tabulation (Bottom Up DP)
    int solveTab(int n, vector<int> &prefixSum){
        
        // dp vector
        vector<int> dp(n, -1);

        // if i is the last stone, we can store prefixSum[ind] as this is what would be added back
        dp[n-1] = prefixSum[n-1];

        // Reverse the recursive call to construct from the bottom
        for(int ind=n-2; ind>=1; ind--){
            // Take till the current index and pass to opponent
            int take = prefixSum[ind] - dp[ind+1];
            // Skip to take till a later index
            int notTake = dp[ind+1];
            // Maximize own score to maximize score or minimize opponent's score.
            dp[ind] = max(take, notTake);
        }
        // Return the first choice we made in the recursive soln
        return dp[1];        
    }

    // Space optimize the tabulation
    int solveTabOpt(int n, vector<int> &prefixSum){

        // We only care about the next/opponents move to construct our score
        int next = prefixSum[n-1];

        // Reverse the recursive call to construct from the bottom
        for(int ind=n-2; ind>=1; ind--){
            // Take till the current index and subtract the opponent's score
            int take = prefixSum[ind] - next;
            // Skip to take till a later index
            int notTake = next;
            // Maximize own score to maximize score or minimize opponent's score.
            next = max(take, notTake);
        }
        // Return the first choice made
        return next;        
    }

public:
    int stoneGameVIII(vector<int>& stones) {
        // Get the number of stones
        int n = stones.size();
        // dp vector for memoization
        // vector<int> dp(n, -1);
        // As the problem statement states the player takes x numbers from the front
        // and adds back the sum till x, it signifies something as a prefix sum
        // For eg: [-1, 2, -3, 4, -5], if Alice picks x=3, sum=(-1+2-3)=-2 and we add -2 back
        // and so on. So it is just the prefix sum at work
        vector<int> prefixSum(n, 0);
        prefixSum[0] = stones[0];
        for(int i=1; i<n; i++){
            prefixSum[i] += stones[i] + prefixSum[i-1];
        }
        // Call the recursive function with ind 1 as x>1
        return solveTabOpt(n, prefixSum);
    }
};
