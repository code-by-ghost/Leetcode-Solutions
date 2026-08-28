#include <bits/stdc++.h>
using namespace std;

/*
 * Problem: Lexicographically Smallest Palindromic Permutation Greater Than Target
 *
 * Approach:
 * 1. Count character frequencies in `s`.
 * 2. Check if a palindrome can be formed:
 *    - At most one character can have an odd frequency (this becomes the middle).
 * 3. Build only the first half of the palindrome using recursion/backtracking.
 *    - At each step, decide whether the current prefix is already lexicographically
 *      greater than the target prefix.
 * 4. Once half is built, mirror it to form the full palindrome (plus middle if needed).
 * 5. Return the first valid palindrome that is strictly greater than `target`.
 */

class Solution {
private:
    char mid = '#';       // Middle character if odd frequency exists
    string res = "";      // Result string
    int half = 0;         // Half length of palindrome

    // Recursive helper to build the first half of palindrome
    bool solve(string &cur, vector<int> &hash, string &target, int ind, bool greater) {
        // Base case: half constructed
        if (cur.size() == half) {
            string rev = cur;
            reverse(rev.begin(), rev.end());

            string temp = cur;
            if (mid != '#') temp += mid; // Add middle if exists
            temp += rev;                 // Add mirrored second half

            // Check lexicographic condition
            if (temp > target) {
                res = temp;
                return true;
            }
            return false;
        }

        // Try all characters 'a' to 'z'
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (hash[ch - 'a'] == 0) continue; // Skip if not available

            // If not greater yet, skip chars smaller than target[ind]
            if (!greater && ch < target[ind]) continue;

            // Choose character
            cur.push_back(ch);
            hash[ch - 'a']--;

            // Update "greater" flag
            bool isGreater = greater || (ch > target[ind]);

            // Recurse
            if (solve(cur, hash, target, ind + 1, isGreater))
                return true;

            // Backtrack
            cur.pop_back();
            hash[ch - 'a']++;
        }

        return false;
    }

public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> hash(26, 0);

        // Count frequencies
        for (char c : s) hash[c - 'a']++;

        // Find odd frequency count
        int oddCount = 0;
        for (int i = 0; i < 26; i++) {
            if (hash[i] % 2) {
                mid = i + 'a';
                oddCount++;
            }
        }

        // More than one odd → no palindrome possible
        if (oddCount > 1) return "";

        // Halve frequencies for first half construction
        for (int i = 0; i < 26; i++) hash[i] /= 2;
        half = n / 2;

        // Start recursion
        string cur;
        solve(cur, hash, target, 0, false);

        return res;
    }
};

// Example usage
int main() {
    Solution sol;
    cout << sol.lexPalindromicPermutation("baba", "abba") << endl; // Output: "baab"
    cout << sol.lexPalindromicPermutation("baba", "bbaa") << endl; // Output: ""
    cout << sol.lexPalindromicPermutation("abc", "abb") << endl;   // Output: ""
    cout << sol.lexPalindromicPermutation("aac", "abb") << endl;   // Output: "aca"
    return 0;
}
