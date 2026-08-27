/**
 * LeetCode 3720. Lexicographically Smallest Permutation Greater Than Target
 * 
 * Problem:
 * You are given two strings s and target, both of length n, consisting of lowercase English letters.
 * Return the lexicographically smallest permutation of s that is strictly greater than target.
 * If no permutation of s is strictly greater, return an empty string.
 * 
 * Approach:
 * - Count the frequency of each character in s.
 * - Use backtracking (DFS) to build the answer character by character.
 * - At each position i:
 *   - Try all available characters in lexicographic order.
 *   - If we haven’t yet exceeded target, skip characters smaller than target[i].
 *   - Once we place a character greater than target[i], mark `greater = true`.
 * - Stop when we reach the end of target and have constructed a valid permutation.
 * - The first valid permutation we find will be the lexicographically smallest.
 * 
 * Complexity:
 * - Worst case exponential due to backtracking, but bounded by n! permutations.
 * - Works fine for typical constraints since n ≤ 8 (based on problem statement).
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    string res = "";

    // Recursive helper
    bool solve(string& cur, vector<int>& count, string& target, int i, bool greater) {
        // Base case: constructed full string
        if (i == target.length()) {
            if (greater) {
                res = cur; // store result
                return true;
            }
            return false;
        }

        // Try all characters from 'a' to 'z'
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (count[ch - 'a'] == 0) continue; // skip if not available

            // If we haven't exceeded target yet, skip chars smaller than target[i]
            if (!greater && ch < target[i]) continue;

            // Choose character
            cur.push_back(ch);
            count[ch - 'a']--;

            // Update "greater" flag
            bool isGreater = greater || (ch > target[i]);

            // Recurse
            if (solve(cur, count, target, i + 1, isGreater))
                return true; // stop at first valid solution

            // Backtrack
            cur.pop_back();
            count[ch - 'a']++;
        }
        return false;
    }

public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> count(26, 0);
        for (char ch : s) count[ch - 'a']++;

        string cur = "";
        solve(cur, count, target, 0, false);

        return res;
    }
};

// Example usage
int main() {
    Solution sol;
    string s = "abc", target = "bba";
    cout << sol.lexGreaterPermutation(s, target) << endl; // Output: "bca"

    s = "leet", target = "code";
    cout << sol.lexGreaterPermutation(s, target) << endl; // Output: "eelt"

    s = "baba", target = "bbaa";
    cout << sol.lexGreaterPermutation(s, target) << endl; // Output: ""
}
