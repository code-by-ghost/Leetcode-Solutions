/*
 * LeetCode Problem: Find the Minimum and Maximum Number of Nodes Between Critical Points
 *
 * Problem Statement:
 * A node in a linked list is a critical point if it is either:
 *  - A local maximum (greater than both neighbors), or
 *  - A local minimum (smaller than both neighbors).
 *
 * Return:
 * 1. The minimum distance between any two consecutive critical points.
 * 2. The maximum distance between the first and last critical points.
 *
 * If fewer than two critical points exist, return {-1, -1}.
 *
 * ------------------------------------------------------------
 * Intuition:
 * Critical points are the peaks and valleys of the linked list.
 * We traverse with three pointers (prev, cur, next) and track indices.
 * - First critical point → store index.
 * - Later critical points → update min distance and max distance.
 * - If fewer than two → return {-1, -1}.
 *
 * ------------------------------------------------------------
 * Approach:
 * 1. Traverse the list with three pointers.
 * 2. Track the index of each node.
 * 3. Detect critical points by comparing neighbors.
 * 4. Update min/max distances.
 * 5. Return results.
 *
 * ------------------------------------------------------------
 * Time Complexity: O(n)  (single pass through the list)
 * Space Complexity: O(1) (constant extra space)
 */

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> res = {-1, -1};
        if (!head || !head->next || !head->next->next) return res;

        ListNode* prev = head;
        ListNode* cur = head->next;
        ListNode* next = cur->next;

        int curInd = 1;
        int first = -1, prevInd = -1;
        int minDist = INT_MAX, maxDist = -1;

        while (next) {
            if ((cur->val > prev->val && cur->val > next->val) ||
                (cur->val < prev->val && cur->val < next->val)) {
                
                if (first == -1) {
                    first = curInd;
                } else {
                    minDist = min(minDist, curInd - prevInd);
                    maxDist = curInd - first;
                }
                prevInd = curInd;
            }
            prev = cur;
            cur = next;
            next = next->next;
            curInd++;
        }

        if (minDist == INT_MAX) return res;
        res[0] = minDist;
        res[1] = maxDist;
        return res;
    }
};

// Example usage (for local testing)
int main() {
    // Linked list: 1 -> 3 -> 2 -> 2 -> 3 -> 2 -> 2 -> 2 -> 7
    ListNode* head = new ListNode(1);
    head->next = new ListNode(3);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(3);
    head->next->next->next->next->next = new ListNode(2);
    head->next->next->next->next->next->next = new ListNode(2);
    head->next->next->next->next->next->next->next = new ListNode(2);
    head->next->next->next->next->next->next->next->next = new ListNode(7);

    Solution sol;
    vector<int> ans = sol.nodesBetweenCriticalPoints(head);
    cout << "Min Distance: " << ans[0] << ", Max Distance: " << ans[1] << endl;

    return 0;
}
