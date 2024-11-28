#ifndef OBLOCK_H
#define OBLOCK_H

#include "decorator.h"

class OBlock: public Decorator {
  public:
    OBlock(Board *component, 
           int generatedLevel,
           std::vector<std::pair<int, int>> coords = {{0, 2}, {1, 2}, {0, 3}, {1, 3}},
           char symbol = 'O');
    void rotateClockwise() override;
    void rotateCounterClockwise() override;
    char charAt(int x, int y) const override;
};

#endif
