/*
    LeetCode 3414. Maximum Score of Non-overlapping Intervals

    Approach:
    ----------
    1. Store each interval's original index.
    2. Sort intervals by start time.
    3. For every interval, use binary search to find the first interval
       whose start is strictly greater than the current interval's end.
       This gives nextIdx[i].
    4. Use DP with state (i, k):
         - i = current interval
         - k = number of intervals we can still choose
       At every state, we either:
         - Skip the current interval.
         - Take it and jump to nextIdx[i].
    5. When two choices have the same score, choose the
       lexicographically smaller list of original indices.

    Why start > end?
    -----------------
    Intervals sharing a boundary are considered overlapping.
    Therefore, after [l, r], the next interval must satisfy:

        next.start > r

    Complexity:
    -----------
    Sorting:                         O(n log n)
    Binary search for every interval: O(n log n)
    DP:                              O(n * 4)
    Since each stored index list has size at most 4, comparing/sorting it
    is O(1) in practice.

    Overall time:  O(n log n)
    Space:         O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    struct Node {
        long long score = 0;   // Maximum score for this state.
        vector<int> idxs;      // Original indices chosen for this state.
    };

    int n;
    vector<int> nextIdx;

    /*
        Find the first interval whose start is strictly greater than 'end'.

        Because intervals are sorted by start time, binary search can be used.

        Example:
            current end = 5
            starts = [1, 4, 6, 8]

            next interval = index 2 (start = 6)
    */
    int findNext(const vector<vector<int>>& intervals, int end) {
        int low = 0;
        int high = n - 1;
        int result = n;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (intervals[mid][0] > end) {
                result = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return result;
    }

    /*
        Top-down DP with memoization.

        solve(i, k):
            Best answer using intervals from i onward
            with at most k selections remaining.
    */
    Node solve(const vector<vector<int>>& intervals, int i, int k,
               vector<vector<Node>>& memo,
               vector<vector<bool>>& seen) {
        // No intervals left or no selections remaining.
        if (k == 0 || i >= n) {
            return Node();
        }

        // Return cached result if this state was already computed.
        if (seen[i][k]) {
            return memo[i][k];
        }

        // Option 1: Skip the current interval.
        Node skip = solve(intervals, i + 1, k, memo, seen);

        // Option 2: Take the current interval.
        Node take = solve(intervals, nextIdx[i], k - 1, memo, seen);

        take.score += intervals[i][2];

        // Add the original interval index.
        take.idxs.push_back(intervals[i][3]);

        // Keep indices sorted because the answer must be
        // compared lexicographically.
        sort(take.idxs.begin(), take.idxs.end());

        Node result;

        if (skip.score > take.score) {
            result = skip;
        } else if (take.score > skip.score) {
            result = take;
        } else {
            // Same score -> lexicographically smaller index list wins.
            result = (skip.idxs < take.idxs) ? skip : take;
        }

        seen[i][k] = true;
        return memo[i][k] = result;
    }

    /*
        Bottom-up DP (tabulation).

        This mirrors the recursive recurrence, but computes the states
        iteratively from the end of the interval list toward the beginning.
    */
    Node solveTab(const vector<vector<int>>& intervals, int K) {
        // t[i][k] = best answer starting from i with k picks remaining.
        //
        // i = n is a valid base state:
        // there are no intervals left, so the score is 0 and the list is empty.
        vector<vector<Node>> dp(n + 1, vector<Node>(K + 1));

        for (int i = n - 1; i >= 0; --i) {
            for (int k = 1; k <= K; ++k) {

                // Option 1: skip interval i.
                Node skip = dp[i + 1][k];

                // Option 2: take interval i and jump to the next
                // non-overlapping interval.
                Node take = dp[nextIdx[i]][k - 1];

                take.score += intervals[i][2];
                take.idxs.push_back(intervals[i][3]);

                // At most 4 indices are stored, so sorting is effectively O(1).
                sort(take.idxs.begin(), take.idxs.end());

                // Compare by score first, then lexicographically.
                if (skip.score > take.score) {
                    dp[i][k] = skip;
                } else if (take.score > skip.score) {
                    dp[i][k] = take;
                } else {
                    dp[i][k] = (skip.idxs < take.idxs) ? skip : take;
                }
            }
        }

        return dp[0][K];
    }

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        n = intervals.size();

        // Append the original index to every interval:
        // [start, end, weight, originalIndex]
        for (int i = 0; i < n; ++i) {
            intervals[i].push_back(i);
        }

        // Sort by start time (and then by the remaining fields if needed).
        sort(intervals.begin(), intervals.end());

        // Precompute the next compatible interval for every interval.
        nextIdx.resize(n);

        for (int i = 0; i < n; ++i) {
            nextIdx[i] = findNext(intervals, intervals[i][1]);
        }

        constexpr int K = 4;

        /*
            Final solution: bottom-up DP.

            Each dp state stores:
                - maximum achievable score
                - lexicographically smallest chosen index list
        */
        return solveTab(intervals, K).idxs;
    }
};

/*
    Optional local test:

    int main() {
        Solution sol;

        vector<vector<int>> intervals = {
            {1, 3, 2},
            {4, 5, 2},
            {1, 5, 5},
            {6, 9, 3},
            {6, 7, 1},
            {8, 9, 1}
        };

        vector<int> ans = sol.maximumWeight(intervals);

        for (int idx : ans) {
            cout << idx << ' ';
        }
        cout << '\n';

        // Expected: 2 3
    }
*/
