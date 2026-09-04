/*
    LeetCode 3876 - Uniform Parity Array II

    Idea:
    -----
    The key observation is that the minimum element can never be changed.

    Why?
    Negative values are not allowed, so for:
        nums[i] - nums[j]

    we must have:
        nums[i] >= nums[j]

    Therefore, the minimum element cannot be reduced using another element.

    Cases:
    ------
    1. Minimum element is odd:
       - Keep the minimum as odd.
       - Subtract the odd minimum from every even element.
       - Even - Odd = Odd.
       - Hence, all elements can become odd.
       - Answer = true.

    2. Minimum element is even:
       - Subtracting an even number does not change parity.
       - Therefore, any odd element will remain odd.
       - If an odd element exists, making everything even is impossible.
       - If all elements are even, the array is already uniform.
       - Answer = false if any odd exists, otherwise true.

    Complexity:
    -----------
    Time:  O(n)
    Space: O(1)
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        // Find the minimum element.
        int minm = *min_element(nums1.begin(), nums1.end());

        // If the minimum is odd, we can make every element odd.
        if (minm % 2 == 1) {
            return true;
        }

        // Minimum is even.
        // Any odd element cannot be converted to even.
        for (int num : nums1) {
            if (num % 2 == 1) {
                return false;
            }
        }

        // All elements are even already.
        return true;
    }
};

int main() {
    Solution solution;

    vector<int> nums1 = {3, 6, 8, 10};
    vector<int> nums2 = {2, 5, 8};
    vector<int> nums3 = {2, 4, 8, 10};

    cout << boolalpha;

    cout << "Example 1: "
         << solution.uniformArray(nums1) << '\n'; // true

    cout << "Example 2: "
         << solution.uniformArray(nums2) << '\n'; // false

    cout << "Example 3: "
         << solution.uniformArray(nums3) << '\n'; // true

    return 0;
}
