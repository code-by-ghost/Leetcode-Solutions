/*
    LeetCode 3903 - Smallest Stable Index I

    Problem:
    --------
    For each index i, define:

        instability = max(nums[0..i]) - min(nums[i..n-1])

    An index is stable if:

        instability <= k

    Return the smallest stable index, or -1 if none exists.

    Approach:
    ---------
    1. Precompute the minimum value for every suffix.
       minSuffix[i] = min(nums[i..n-1])

    2. Scan from left to right while maintaining the maximum
       value seen so far:

       maxPrefix = max(nums[0..i])

    3. At each index:
       
       maxPrefix - minSuffix[i] <= k

       If true, return i immediately because we are scanning
       from left to right and therefore found the smallest one.

    Complexity:
    -----------
    Time  : O(n)
    Space : O(n)
*/

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        // minSuffix[i] stores the minimum element
        // in the range [i, n - 1].
        vector<int> minSuffix(n);

        int minElem = INT_MAX;

        // Build suffix minimums from right to left.
        for (int i = n - 1; i >= 0; --i) {
            minElem = min(minElem, nums[i]);
            minSuffix[i] = minElem;
        }

        // Keep track of the maximum element
        // in the current prefix [0, i].
        int maxPrefix = INT_MIN;

        // Scan from left to right.
        for (int i = 0; i < n; ++i) {
            maxPrefix = max(maxPrefix, nums[i]);

            // Check the instability score.
            if (maxPrefix - minSuffix[i] <= k) {
                // Since we scan left to right,
                // this is the smallest stable index.
                return i;
            }
        }

        // No stable index exists.
        return -1;
    }
};

int main() {
    Solution solution;

    vector<int> nums1 = {5, 0, 1, 4};
    int k1 = 3;

    vector<int> nums2 = {3, 2, 1};
    int k2 = 1;

    vector<int> nums3 = {0};
    int k3 = 0;

    cout << "Example 1: "
         << solution.firstStableIndex(nums1, k1) << '\n'; // 3

    cout << "Example 2: "
         << solution.firstStableIndex(nums2, k2) << '\n'; // -1

    cout << "Example 3: "
         << solution.firstStableIndex(nums3, k3) << '\n'; // 0

    return 0;
}
