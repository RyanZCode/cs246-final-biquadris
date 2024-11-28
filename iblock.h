#ifndef IBLOCK_H
#define IBLOCK_H

#include "decorator.h"

class IBlock: public Decorator {
  public:
    IBlock(Board *component, 
           std::vector<std::pair<int, int>> coords = {{0, 3}, {1, 3}, {2, 3}, {3, 3}}, 
           char symbol = 'I', 
           int generatedLevel);
    void rotateClockwise() override;
    void rotateCounterClockwise() override;
    char charAt(int x, int y) const override;
};

#endif
