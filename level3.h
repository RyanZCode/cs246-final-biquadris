#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"
#include <vector>
#include <utility>
#include <string>

class Level3 : public Level {
    std::vector<std::pair<char, int>> blockWeights;
    int totalWeight;
    bool random;
    ifstream input;
  public:
    Level3();
    char nextBlock() override;
    void setRandom(bool randBool);
    void setSequenceFile(std::string filename)
};

#endif
