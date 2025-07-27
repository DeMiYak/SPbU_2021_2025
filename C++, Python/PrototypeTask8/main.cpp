#include <iostream>
#include <vector>
#include "MineSweeperView.h"
#include "MineSweeper.h"

void printMS(std::vector<std::vector<int>> table) {
    for (auto& i : table) {
        for (auto& j : i) {
            if (j == MineSweeper::MINE) {
                cout << "* ";
            }
            else cout << j << " ";
        }
        cout << endl;
    }
}

int main() {
    MineSweeper mf(8, 8, 20);

    printMS(mf.GetMinefield());
    cout << endl;

    mf.CreateMinefield(12, 30, 180);
    printMS(mf.GetMinefield());

    MineSweeperView mine_sweeper_view(mf);
    mine_sweeper_view.DrawMineSweeper();

    return 0;
}