#include "test_base.h"

/**
 * \name: Sliding Puzzle [Hard]
 */

// On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by 0.
// A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

// The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

// Given the puzzle board board, return the least number of moves required so that the state of the board is solved.
// If it is impossible for the state of the board to be solved, return -1.

// Example 1:
// -------------------
// |  1  |  2  |  3  |
// -------------------
// |  4  |     |  5  |
// -------------------
// Input: board = [[1,2,3],[4,0,5]]
// Output: 1
// Explanation: Swap the 0 and the 5 in one move.

// Example 2:
// -------------------
// |  1  |  2  |  3  |
// -------------------
// |  5  |  4  |     |
// -------------------
// Input: board = [[1,2,3],[5,4,0]]
// Output: -1
// Explanation: No number of moves will make the board solved.

// Example 3:
// -------------------
// |  4  |  1  |  2  |
// -------------------
// |  5  |     |  3  |
// -------------------
// Input: board = [[4,1,2],[5,0,3]]
// Output: 5
// Explanation: 5 is the smallest number of moves that solves the board.
// An example path:
// After move 0: [[4,1,2],[5,0,3]]
// After move 1: [[4,1,2],[0,5,3]]
// After move 2: [[0,1,2],[4,5,3]]
// After move 3: [[1,0,2],[4,5,3]]
// After move 4: [[1,2,0],[4,5,3]]
// After move 5: [[1,2,3],[4,5,0]]

// Constraints:
// board.length == 2
// board[i].length == 3
// 0 <= board[i][j] <= 5
// Each value board[i][j] is unique.

class Solution_0773
{
public:
    int slidingPuzzle(vector<vector<int>> &board)
    {
        std::string target = "123450";
        std::string start = "";
        for (auto &row : board)
            for (int val : row)
                start += to_string(val);

        std::unordered_set<std::string> visited;
        std::queue<pair<std::string, int>> q;
        q.push({start, 0});
        visited.insert(start);

        std::vector<std::vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty())
        {
            auto [curr, moves] = q.front();
            q.pop();

            if (curr == target)
                return moves;

            int zeroPos = curr.find('0');
            int x = zeroPos / 3;
            int y = zeroPos % 3;
            for (auto &dir : dirs)
            {
                int newX = x + dir[0], newY = y + dir[1];
                if (newX >= 0 && newX < 2 && newY >= 0 && newY < 3)
                {
                    std::string next = curr;
                    std::swap(next[x * 3 + y], next[newX * 3 + newY]);
                    if (!visited.count(next))
                    {
                        visited.insert(next);
                        q.push({next, moves + 1});
                    }
                }
            }
        }
        return -1;
    }
};

void leet_test_0773();