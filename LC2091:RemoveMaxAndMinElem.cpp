```cpp
/*
    LeetCode 2091 - Removing Minimum and Maximum From Array

    Intuition:
    We can delete elements only from the front or the back.
    Therefore, there are only 3 possible strategies:

    1. Remove both minimum and maximum from the front.
    2. Remove both minimum and maximum from the back.
    3. Remove one from the front and the other from the back.

    Find the indices of the minimum and maximum elements,
    calculate the cost of all 3 strategies, and return the minimum.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        // Indices of minimum and maximum elements
        int mnInd = 0;
        int mxInd = 0;

        // Find minimum and maximum indices in one pass
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[mnInd])
                mnInd = i;

            if (nums[i] > nums[mxInd])
                mxInd = i;
        }

        // Strategy 1: Remove both from the front
        int front = max(mnInd, mxInd) + 1;

        // Strategy 2: Remove both from the back
        int back = n - min(mnInd, mxInd);

        // Strategy 3: Remove one from front and one from back
        int mix = min(mnInd, mxInd) + 1
                + (n - max(mnInd, mxInd));

        // Take the minimum of all three strategies
        return min({front, back, mix});
    }
};

int main() {
    Solution sol;

    vector<int> nums = {2, 10, 7, 5, 4, 1, 8, 6};

    cout << "Minimum deletions: "
         << sol.minimumDeletions(nums) << '\n';

    return 0;
}
```
