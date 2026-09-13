/*
    LeetCode 835. Image Overlap

    Approach:
    ----------
    Try every possible translation (rowOffset, colOffset) of img2.

    For a fixed translation:
      1. Map each cell (i, j) of img1 to (i + rowOffset, j + colOffset) in img2.
      2. Ignore mapped positions that fall outside the grid.
      3. Count positions where both images contain 1.
      4. Keep the maximum overlap.

    Complexity:
    -----------
    There are (2n - 1)^2 = O(n^2) possible translations.
    Each translation checks O(n^2) cells.

    Time:  O(n^4)
    Space: O(1) extra space (besides the input matrices)

    Note:
    -----
    The problem allows translating an image, which means shifting the entire
    image by the same row/column offset. There is no rotation or flipping.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Count the overlapping 1s for one fixed translation.
    int countOverlaps(const vector<vector<int>>& img1,
                      const vector<vector<int>>& img2,
                      int rowOffset,
                      int colOffset) {
        int n = img1.size();
        int count = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {

                // Corresponding position in img2 after applying the offset.
                int im2_i = i + rowOffset;
                int im2_j = j + colOffset;

                // The translated position is outside the matrix.
                if (im2_i < 0 || im2_j < 0 ||
                    im2_i >= n || im2_j >= n) {
                    continue;
                }

                // Count only positions where both images have a 1.
                if (img1[i][j] == 1 && img2[im2_i][im2_j] == 1) {
                    ++count;
                }
            }
        }

        return count;
    }

public:
    int largestOverlap(vector<vector<int>>& img1,
                       vector<vector<int>>& img2) {
        int n = img1.size();
        int maxOverlap = 0;

        // Try every possible row translation.
        for (int rowOffset = -n + 1; rowOffset < n; ++rowOffset) {

            // Try every possible column translation.
            for (int colOffset = -n + 1; colOffset < n; ++colOffset) {

                // Count overlap for this translation.
                int currentOverlap =
                    countOverlaps(img1, img2, rowOffset, colOffset);

                // Keep the best overlap found so far.
                maxOverlap = max(maxOverlap, currentOverlap);
            }
        }

        return maxOverlap;
    }
};

// ------------------------------------------------------------
// Example usage
// ------------------------------------------------------------
// LeetCode does not require a main() function.
// This main() is included only for local testing.
//
// int main() {
//     Solution sol;
//
//     vector<vector<int>> img1 = {
//         {1, 1, 0},
//         {0, 1, 0},
//         {0, 1, 0}
//     };
//
//     vector<vector<int>> img2 = {
//         {0, 0, 1},
//         {0, 1, 1},
//         {0, 0, 1}
//     };
//
//     cout << sol.largestOverlap(img1, img2) << '\n';
//
//     return 0;
// }
