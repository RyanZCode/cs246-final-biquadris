#include "sblock.h"

using namespace std;


SBlock::SBlock(Board *component, int generatedLevel, vector<pair<int, int>> coords, char symbol):
    Decorator{component, generatedLevel, coords, symbol} {}

void SBlock::rotateClockwise() {
    vector<pair<int, int>> newCoords = coords;
    pair<int, int> newBottomLeft = bottomLeft;

    transpose(newCoords, newBottomLeft);
    
    // Set new bottom left anchor and reverse cols
    if (state == RotationState::Default) {
        newBottomLeft.first -= 1;
        newBottomLeft.second += 2;

        // Change state
        state = RotationState::Rotated90;   
    } else {
        newBottomLeft.first -= 2;
        newBottomLeft.second += 1;

        // Change state
        state = RotationState::Default; 
    }

    reposition(newCoords, newBottomLeft);

    if (isValid(newCoords)) {
        coords = newCoords;
    }
}

void SBlock::rotateCounterClockwise() {
    for (int i = 0; i < 3; ++i) {
        rotateClockwise();
    }
}

