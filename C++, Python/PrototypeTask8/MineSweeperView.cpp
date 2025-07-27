#include "MineSweeperView.h"

#include <utility>
#include "Console.h"

MineSweeperView::MineSweeperView(MineSweeper mineSweeperModel): _mineSweeperModel(std::move(mineSweeperModel)) {
    InitConsole("game");
}

void MineSweeperView::DrawMineSweeper() {
    vector<vector<CELL_INFO>> cellInfo = _mineSweeperModel.GetCellInfo();
    vector<vector<int>> mineField = _mineSweeperModel.GetMinefield();
    for (int row = 0; row < cellInfo.size(); ++row) {
        for (int col = 0; col < cellInfo[0].size(); ++col) {
            switch (cellInfo[row][col]) {
                case CLOSED:
                    break;
                case OPEN:
                    ColorPrint(col, row, B_D_BLUE, "t");
                    break;
                case FLAG:
                    break;
            }
        }
    }
}

string MineSweeperView::OpenCellCase(int cellData) {
    switch (cellData) {
        case MineSweeper::MINE:
            return MINE;
        case 0:
            return ZERO;
        default:
            return to_string(cellData);
    }
}
