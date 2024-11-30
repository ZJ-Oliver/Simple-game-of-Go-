#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int BOARD_SIZE = 9; // 使用9x9的简化围棋棋盘
char board[BOARD_SIZE][BOARD_SIZE];

// 初始化棋盘
void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = '.';
}

// 打印棋盘
void printBoard() {
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i)
        std::cout << i << " ";
    std::cout << "\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; ++j)
            std::cout << board[i][j] << " ";
        std::cout << "\n";
    }
}

// 检查落子是否合法
bool isValidMove(int x, int y) {
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && board[x][y] == '.');
}

// 简单AI逻辑（根据难度选择策略）
void aiMove(int level) {
    int x, y;
    if (level == 1) { // 初学者AI：随机落子
        do {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        } while (!isValidMove(x, y));
    } else if (level == 5) { // 中级AI：随机但有概率考虑对手
        do {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        } while (!isValidMove(x, y));
        // （可扩展：实现简单防守策略）
    } else if (level == 3) { // 3段：增加占据中心的策略
        for (x = 3; x < 6; ++x) {
            for (y = 3; y < 6; ++y) {
                if (isValidMove(x, y)) {
                    board[x][y] = 'O';
                    return;
                }
            }
        }
        aiMove(5);
        return;
    } else if (level == 9) { // 高段位AI：占据关键点位
        for (x = 2; x < 7; ++x) {
            for (y = 2; y < 7; ++y) {
                if (isValidMove(x, y)) {
                    board[x][y] = 'O';
                    return;
                }
            }
        }
        aiMove(3);
        return;
    }
    board[x][y] = 'O'; // AI落子
}

// 主程序
int main() {
    srand(time(0)); // 初始化随机数种子
    int aiLevel;
    std::cout << "选择AI实力等级：\n1. 1级\n2. 5级\n3. 3段\n4. 9段\n";
    std::cin >> aiLevel;

    int levelMap[] = {1, 5, 3, 9};
    aiLevel = levelMap[aiLevel - 1];

    initializeBoard();
    printBoard();

    while (true) {
        int x, y;
        std::cout << "请输入您的落子位置（x y）：";
        std::cin >> x >> y;
        if (!isValidMove(x, y)) {
            std::cout << "非法落子，请重新输入！\n";
            continue;
        }
        board[x][y] = 'X'; // 用户落子

        printBoard();

        // 简单判断游戏结束条件（示例代码中未包含完整胜负判断）
        aiMove(aiLevel); // AI落子
        std::cout << "AI落子：\n";
        printBoard();
    }

    return 0;
}

