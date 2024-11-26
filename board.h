#ifndef BOARD_H
#define BOARD_H
#include "decorator.h"

class Board {
    int rows, cols;
    Decorator* picture;
  public:
    Board(int rows = 15, int cols = 11, Decorator* picture);
    char getState(int x, int y) const override;
    void removeLayer();
    void checkBoard();
    void getRows() const;
    void getCols() const;

};

#endif
