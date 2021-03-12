#include "Table.h"

Table::Table(int row, int col) {
    hiddenTiles = new int[row * col];
    currentTiles = new int[row * col];
    this->row = row;
    this->col = col;
    currentFlag = 0;
    bombCount = 0;

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) {

            currentTiles[i * col + j] = 11;

        }

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) {

            hiddenTiles[i * col + j] = 0;

        }

}

bool Table::check(int n) {
    for (int i = 0; i < row*col; i++) {
        if (n == hiddenTiles[i]) return true;
    }
    return false;
}

void Table::createBombs(int bombCount, int exclude) {
    this->bombCount = bombCount;
    srand(time(0));
    for (int i = 0; i < bombCount;) {
        int random = rand() % (row * col);
        if (check(random) || random == exclude) continue;
        if (std::count(bomb.begin(), bomb.end(), random)) continue;
        bomb.push_back(random);
        hiddenTiles[random] = 10;
        i++;
    }
    std::sort(bomb.begin(), bomb.end());
}

void Table::openEmpty(int x, int y, int from_x, int from_y) {

    std::cout << "Opened (" << x << "," << y << ")" << std::endl;
    currentTiles[y * col + x] = hiddenTiles[y * col + x];

    if (hiddenTiles[y * col + x] != 10 && hiddenTiles[y * col + x] != 0) return;

    if (hiddenTiles[y * col + x - 1] != 10
        && currentTiles[y * col + x - 1] == 11
        && x > 0
        && x-1 != from_x) openEmpty(x-1, y, x,y);

    if (hiddenTiles[y * col + x + 1] != 10
        && currentTiles[y * col + x + 1] == 11
        && x < col-1
        && x+1 != from_x) openEmpty(x+1, y, x, y);

    if (hiddenTiles[(y - 1) * col + x] != 10
        && currentTiles[(y - 1) * col + x] == 11
        && y > 0
        && y-1 != from_y) openEmpty(x, (y - 1), x, y);

    if (hiddenTiles[(y + 1) * col + x] != 10
        && currentTiles[(y + 1) * col + x] == 11
        && y < col-1
        && y+1 != from_y) openEmpty(x, (y + 1), x, y);

    if (hiddenTiles[(y + 1)* col + x - 1] != 10
        && currentTiles[(y + 1) * col + x - 1] == 11
        && x > 0
        && y + 1 != from_y
        && x - 1 != from_x) openEmpty(x - 1, y + 1, x, y);

    if (hiddenTiles[(y - 1) * col + x - 1] != 10
        && currentTiles[(y - 1) * col + x - 1] == 11
        && x > 0
        && y - 1 != from_y
        && x - 1 != from_x) openEmpty(x - 1, y - 1, x, y);

    if (hiddenTiles[(y - 1) * col + x + 1] != 10
        && currentTiles[(y - 1) * col + x + 1] == 11
        && x < col - 1
        && y - 1 != from_y
        && x + 1 != from_x) openEmpty(x + 1, y - 1, x, y);

    if (hiddenTiles[(y + 1) * col + x + 1] != 10
        && currentTiles[(y + 1) * col + x + 1] == 11
        && x < col - 1
        && y + 1 != from_y
        && x + 1 != from_x) openEmpty(x + 1, y + 1, x, y);
}

int Table::open(int x, int y) {
    if (x < 0 || x > col || y < 0 || y > row) return 2;
    if (hiddenTiles[y * col + x] == 10) {
        return 0;
    }
    if (hiddenTiles[y * col + x] == 0) {
        openEmpty(x, y);
        return 1;
    }
    currentTiles[y * col + x] = hiddenTiles[y * col + x];
    return 1;
}

void Table::fillNumberTiles() {
    for (int y = 0; y < row; y++)
        for (int x = 0; x < col; x++) {
            int n = 0;
            if (hiddenTiles[y * col + x] == 10) continue;
            if (hiddenTiles[y * col + x - 1] == 10 && x > 0) n++;
            if (hiddenTiles[y * col + x + 1] == 10 && x != col - 1) n++;
            if (y != 0) {
                if (hiddenTiles[(y - 1) * col + x] == 10) n++;
                if (hiddenTiles[(y - 1) * col + x - 1] == 10 && x > 0) n++;
                if (hiddenTiles[(y - 1) * col + x + 1] == 10 && x != col - 1) n++;
            }
            if (hiddenTiles[(y + 1) * col + x] == 10) n++;
            if (hiddenTiles[(y + 1) * col + x - 1] == 10 && x > 0) n++;
            if (hiddenTiles[(y + 1) * col + x + 1] == 10 && x != col - 1) n++;
            hiddenTiles[y * col + x] = n;

        }
}

void Table::print() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << hiddenTiles[i * col + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << currentTiles[i * col + j] << " ";
        }
        std::cout << std::endl;
    }
}

void Table::flag(int x, int y) {

    if (y > col - 1 || x > row - 1) return;
    int loc = y * col + x;
    std::vector<int>::iterator pos = std::find(flagged.begin(), flagged.end(), loc);
    if (pos != flagged.end()) {
        flagged.erase(pos);
        currentTiles[loc] = 11;
        currentFlag--;
    }
    else {
        if (currentFlag == bombCount) return;
        if (currentTiles[loc] == 11) {
            flagged.push_back(loc);
            currentTiles[loc] = 12;
            currentFlag++;
        }
    }
    std::sort(flagged.begin(), flagged.end());

    //DEBUG

    for (int i : bomb) {
        //std::cout << i << " ";
    }
    //std::cout << std::endl;

    for (int j : flagged) {
        //std::cout << j << " ";
    }
    //std::cout << std::endl;
    //std::cout << currentFlag << std::endl;
}
Table::~Table() {
    delete[] hiddenTiles;
    delete[] currentTiles;
}


