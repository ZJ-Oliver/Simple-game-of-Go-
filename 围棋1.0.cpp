#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int BOARD_SIZE = 9; // ʹ��9x9�ļ�Χ������
char board[BOARD_SIZE][BOARD_SIZE];

// ��ʼ������
void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = '.';
}

// ��ӡ����
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

// ��������Ƿ�Ϸ�
bool isValidMove(int x, int y) {
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && board[x][y] == '.');
}

// ��AI�߼��������Ѷ�ѡ����ԣ�
void aiMove(int level) {
    int x, y;
    if (level == 1) { // ��ѧ��AI���������
        do {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        } while (!isValidMove(x, y));
    } else if (level == 5) { // �м�AI��������и��ʿ��Ƕ���
        do {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        } while (!isValidMove(x, y));
        // ������չ��ʵ�ּ򵥷��ز��ԣ�
    } else if (level == 3) { // 3�Σ�����ռ�����ĵĲ���
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
    } else if (level == 9) { // �߶�λAI��ռ�ݹؼ���λ
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
    board[x][y] = 'O'; // AI����
}

// ������
int main() {
    srand(time(0)); // ��ʼ�����������
    int aiLevel;
    std::cout << "ѡ��AIʵ���ȼ���\n1. 1��\n2. 5��\n3. 3��\n4. 9��\n";
    std::cin >> aiLevel;

    int levelMap[] = {1, 5, 3, 9};
    aiLevel = levelMap[aiLevel - 1];

    initializeBoard();
    printBoard();

    while (true) {
        int x, y;
        std::cout << "��������������λ�ã�x y����";
        std::cin >> x >> y;
        if (!isValidMove(x, y)) {
            std::cout << "�Ƿ����ӣ����������룡\n";
            continue;
        }
        board[x][y] = 'X'; // �û�����

        printBoard();

        // ���ж���Ϸ����������ʾ��������δ��������ʤ���жϣ�
        aiMove(aiLevel); // AI����
        std::cout << "AI���ӣ�\n";
        printBoard();
    }

    return 0;
}

