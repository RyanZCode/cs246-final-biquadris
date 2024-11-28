#ifndef JBLOCK_H
#define JBLOCK_H

#include "decorator.h"

class JBlock: public Decorator {
  public:
    JBlock(Board *component, 
           std::vector<std::pair<int, int>> coords = {{0, 2}, {0, 3}, {1, 3}, {2, 3}}, 
           char symbol = 'J', 
           int generatedLevel);
    void rotateClockwise() override;
    void rotateCounterClockwise() override;
    char charAt(int x, int y) const override;
};

#endif
