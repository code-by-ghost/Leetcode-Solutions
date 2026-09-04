/*
 * LeetCode 3568 - Minimum Moves to Clean the Classroom
 *
 * Approach:
 *   BFS + Bitmasking + State Tracking
 *
 * State:
 *   (row, col, energy, mask)
 *
 * Why do we need all four values?
 *   - row, col      -> current position
 *   - energy        -> how far we can continue before needing a reset
 *   - mask          -> which litter cells have already been collected
 *
 * Bitmask:
 *   Every litter cell gets a unique bit index.
 *   If bit i is 1, litter i has been collected.
 *
 *   goalMask = (1 << litterCount) - 1
 *
 * BFS:
 *   Every move costs exactly 1 step, so BFS explores states in
 *   increasing order of moves. The first state that collects all
 *   litter therefore gives the minimum number of moves.
 *
 * Energy rules:
 *   - Every move costs 1 energy.
 *   - Entering 'R' immediately restores energy to maxEnergy.
 *   - If energy becomes 0 on a non-'R' cell, no further move is possible.
 *   - 'X' cells cannot be entered.
 *
 * Time:
 *   O(m * n * E * 2^L)
 *
 * Space:
 *   O(m * n * E * 2^L)
 *
 * where:
 *   m, n = grid dimensions
 *   E    = maximum energy
 *   L    = number of litter cells
 */

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    struct State {
        int row;
        int col;
        int energy;
        int mask;
    };

    int minMoves(vector<string>& classroom, int maxEnergy) {
        const int m = static_cast<int>(classroom.size());
        const int n = static_cast<int>(classroom[0].size());

        // litterId[r][c] stores the bit index assigned to litter at (r, c).
        // -1 means this cell is not a litter cell.
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        int startRow = -1;
        int startCol = -1;
        int litterCount = 0;

        // Find the start and assign a unique bit to each litter cell.
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (classroom[r][c] == 'S') {
                    startRow = r;
                    startCol = c;
                } else if (classroom[r][c] == 'L') {
                    litterId[r][c] = litterCount++;
                }
            }
        }

        // No litter means we are already done.
        if (litterCount == 0) {
            return 0;
        }

        // Example:
        //   litterCount = 3
        //   goalMask = 111 (binary) = 7
        const int goalMask = (1 << litterCount) - 1;

        // visited[row][col][energy][mask]
        //
        // vector<bool> is used to keep this potentially large structure
        // memory-efficient.
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    maxEnergy + 1,
                    vector<bool>(1 << litterCount, false)
                )
            )
        );

        queue<State> q;

        // Student starts at S with full energy and no litter collected.
        q.push({startRow, startCol, maxEnergy, 0});
        visited[startRow][startCol][maxEnergy][0] = true;

        // BFS level = number of moves taken so far.
        int moves = 0;

        // Up, down, left, right.
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            const int levelSize = static_cast<int>(q.size());

            // Process all states that are exactly 'moves' steps away.
            for (int i = 0; i < levelSize; ++i) {
                State cur = q.front();
                q.pop();

                // The first time we reach this condition, BFS guarantees
                // that 'moves' is the minimum number of moves.
                if (cur.mask == goalMask) {
                    return moves;
                }

                // With 0 energy, we cannot make another move.
                // If we had just entered R, energy would already have been
                // reset to maxEnergy, so this state cannot be on R.
                if (cur.energy == 0) {
                    continue;
                }

                for (int dir = 0; dir < 4; ++dir) {
                    const int nextRow = cur.row + dr[dir];
                    const int nextCol = cur.col + dc[dir];

                    // Outside the grid.
                    if (nextRow < 0 || nextRow >= m ||
                        nextCol < 0 || nextCol >= n) {
                        continue;
                    }

                    // Obstacles are impassable.
                    const char cell = classroom[nextRow][nextCol];
                    if (cell == 'X') {
                        continue;
                    }

                    // A normal move costs one energy.
                    int nextEnergy = cur.energy - 1;
                    int nextMask = cur.mask;

                    // Reset area: entering R restores energy immediately.
                    if (cell == 'R') {
                        nextEnergy = maxEnergy;
                    }
                    // Litter: entering L collects it.
                    else if (cell == 'L') {
                        const int bit = litterId[nextRow][nextCol];
                        nextMask |= (1 << bit);
                    }

                    // The same (position, energy, mask) state never needs
                    // to be processed twice.
                    if (!visited[nextRow][nextCol][nextEnergy][nextMask]) {
                        visited[nextRow][nextCol][nextEnergy][nextMask] = true;
                        q.push({
                            nextRow,
                            nextCol,
                            nextEnergy,
                            nextMask
                        });
                    }
                }
            }

            ++moves;
        }

        // BFS exhausted all reachable states without collecting all litter.
        return -1;
    }
};

int main() {
    Solution solution;

    vector<string> classroom = {
        "LS",
        "RL"
    };

    int energy = 4;

    cout << "Minimum moves: "
         << solution.minMoves(classroom, energy)
         << '\n';

    return 0;
}
