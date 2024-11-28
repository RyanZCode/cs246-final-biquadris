#include "oblock.h"

using namespace std;

OBlock::OBlock(Board *component, vector<pair<int, int>> coords, char symbol, int generatedLevel):
    Decorator{component, coords, symbol, generatedLevel} {}

void OBlock::rotateClockwise() {
    return;
}

void OBlock::rotateCounterClockwise() {
    return;
}

char OBlock::charAt(int x, int y) const {

    // Check if within block
    for (pair<int, int> p : coords) {
        if (p.first == x && p.second == y) {
            return symbol;
        }
    }

    // Else call next decorator's charAt()
    return component->getState(x, y);
}
