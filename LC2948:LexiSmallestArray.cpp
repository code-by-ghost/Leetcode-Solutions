```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>

using namespace std;

/*
    LeetCode 2948. Make Lexicographically Smallest Array by Swapping Elements

    Intuition:
    ----------
    Two values can be swapped if their difference is <= limit.

    After sorting the values:
    - Adjacent values with gap <= limit belong to the same group.
    - A gap > limit starts a new group.

    Since values inside a group are connected through valid swaps,
    they can be rearranged freely.

    To obtain the lexicographically smallest array:
    - For each position in the original array,
      find its group.
    - Place the smallest unused value from that group.

    Time Complexity:  O(n log n)
    Space Complexity: O(n)
*/

class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<int> vec = nums;
        sort(begin(vec), end(vec));

        int groupNum = 0;

        // value -> group id
        unordered_map<int, int> numToGroup;

        // group id -> sorted values in that group
        unordered_map<int, list<int>> groupToList;

        numToGroup[vec[0]] = groupNum;
        groupToList[groupNum].push_back(vec[0]);

        for (int i = 1; i < n; i++) {
            if (vec[i] - vec[i - 1] > limit) {
                groupNum++;
            }

            numToGroup[vec[i]] = groupNum;
            groupToList[groupNum].push_back(vec[i]);
        }

        vector<int> result(n);

        for (int i = 0; i < n; i++) {
            int group = numToGroup[nums[i]];

            result[i] = groupToList[group].front();
            groupToList[group].pop_front();
        }

        return result;
    }
};

int main() {
    Solution sol();

    vector<int> nums = {1, 7, 6, 18, 2, 1};
    int limit = 3;

    Solution solution;
    vector<int> result =
        solution.lexicographicallySmallestArray(nums, limit);

    cout << "Output: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i + 1 < result.size()) cout << ", ";
    }
    cout << "]\n";

    return 0;
}
```
