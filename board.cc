#include "board.h"
#include "decorator.h"
#include "player.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "iblock.h"
#include "lblock.h"
#include "jblock.h"
#include "forceblock.h"
#include "player.h"
#include "blank.h"
#include <iostream>

// Default constructor
Board::Board() : picture{nullptr}, player{nullptr} {}

Board::Board(int rows, int cols, Decorator* picture) : rows{rows}, cols{cols}, picture{picture} {}

Board::~Board() { delete picture; }

char Board::getState(int x, int y) const {
    // Adding blind overlay
    if (player->getEffect() == Effect::BLIND) {
        if (x >= 2 && x <= 8 && y >= 5 && y <= 14) {
            return '?';
        }
    }
    return picture->charAt(x, y);
}

void Board::removeLayer(int row) { 
    // Remove tiles from row and block
    for (int c = 0; c < cols; ++c) {
        Decorator* curBlock = picture->blockAt(c, row);
        curBlock->removeTile(c, row);

        // If block is completely removed (all tiles gone), add to score
        if (curBlock->isEmpty()) {
            player->addScore((curBlock->getGeneratedLevel() + 1) * (curBlock->getGeneratedLevel() + 1));
        }
    }

    // Move above rows down by 1
    for (int r = row - 1; r >= 0; r--) {
        for (int c = 0; c < cols; c++) {
            Decorator* curBlock = picture->blockAt(c, r);
            if (curBlock) {
                curBlock->unconditionalMoveDown(r); 
            }
        }
    }
}

int Board::checkBoard() {
    int linesCleared = 0;
    for (int r = 0; r < rows + 3; r++) {
        bool isFull = true;
        // Check each tile in row
        for (int c = 0; c < cols; c++) {
            if (!picture->blockAt(c,r)) {
                isFull = false;
            }
        }
        
        if (isFull) { 
            removeLayer(r);
            --r;
            linesCleared++;
        }
    }

    // Add points if an entire block is cleared
    if(linesCleared > 0){
        player->addScore((linesCleared + player->getLevel()->getLevelNum()) *
                     (linesCleared + player->getLevel()->getLevelNum()));
    }
    
    return linesCleared;
}

int Board::getRows() const { return rows; }

int Board::getCols() const { return cols; }

bool Board::setBlock(char block) {
    if (block == 'O') {
        picture = new OBlock(picture, player->getLevel()->getLevelNum());
    } else if (block == 'T') {
        picture = new TBlock(picture, player->getLevel()->getLevelNum());
    } else if (block == 'I') {
        picture = new IBlock(picture, player->getLevel()->getLevelNum());
    } else if (block == 'J') {
        picture = new JBlock(picture, player->getLevel()->getLevelNum());
    } else if (block == 'L') {
        picture = new LBlock(picture, player->getLevel()->getLevelNum());
    } else if (block == 'S') {
        picture = new SBlock(picture, player->getLevel()->getLevelNum());
    } else if (block == 'Z') {
        picture = new ZBlock(picture, player->getLevel()->getLevelNum());
    } else if (block == '*') {
        // Give level -1 to not impact score when cleared
        picture = new ForceBlock(picture, -1);
    }
    if (picture->hasOverlap()) {
        return false;
    }
    return true;
}

void Board::replaceBlock(char block) {
    Decorator* nextPic = picture->getComponent();
    picture->setComponentNull();
    delete picture;
    picture = nextPic;
    setBlock(block);
}

bool Board::moveBlock(int rows, int cols) {
    if (rows == -1) {
        picture->moveLeft();
    } else if (rows == 1) {
        picture->moveRight();
    } else if (cols == 1) {
        picture->moveDown();
    }
    // Heavy effect upon horizontal movement only
    if (cols != 1 && player->getEffect() == Effect::HEAVY) {
        picture->moveDown();
        picture->moveDown();
        // Only return false if block is heavy
        if (!picture->canMoveDown()) {
            return false;
        }
    }
    return true;
}

void Board::rotateBlock(bool clockwise) {
    if (clockwise) {
        picture->rotateClockwise();
    } else {
        picture->rotateCounterClockwise();
    }
}

void Board::dropBlock() { picture->drop(); }

void Board::setNextBlock(char block) { nextBlock = block; }

int Board::getScore() const { return player->getScore(); }

int Board::getLevelNum() const { return player->getLevel()->getLevelNum(); }

int Board::getBlockLevel() const { return picture->getGeneratedLevel(); }

char Board::getNextBlock() const { return nextBlock; }

std::string Board::getPlayerName() const { return player->getName(); }

void Board::setPlayer(Player* p) { player = p; }
