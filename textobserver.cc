#include "textobserver.h"
#include "board.h"

TextObserver::TextObserver(Board* b1, Board* b2, int w, int h, std::ostream& o) 
: Observer(b1, b2, w, h), out(o) {
    s1->attach(this);
    s2->attach(this);
}

void TextObserver::update(){
    out << "Level: " << s1->getLevel() << "\t\t" << "Level: " << s2->getLevel() << std::endl;
    out << "Score: " << s1->getScore() << "\t\t" << "Score: " << s2->getScore() << std::endl;

    out << "-------------\t\t-------------" << std::endl;

    //updates state of each coord 
    for(int r = 0; r < height; r++){
        out << '|';
        for(int c = 0; c < width; c++){
            out << s1->getState(r, c);
        }
        out << '|' << "\t\t" << '|';
        for (int c = 0; c < width; c++) {
            out << s2->getState(r, c);
        }
        out << '|' << std::endl;
    } 

    out << "-------------\t\t-------------" << std::endl;

    // Next Block
    out << "Next Block: " << "\t\t" << "Next Block:" << std::endl;

    char nextBlock1 = s1->getNextBlock();
    char nextBlock2 = s2->getNextBlock();
    auto it1 = blockShapes.find(nextBlock1);
    auto it2 = blockShapes.find(nextBlock2);

    for (int i = 0; i < 4; i++) { 
        if (it1 != blockShapes.end() && i < it1->second.size()) {
            out << it1->second[i] << "\t";
        } else {
            out << "   "; 
        }

       out << "\t\t";

        if (it2 != blockShapes.end() && i < it2->second.size()) {
            out << it2->second[i];
        } else {
            out << "   ";
        }

        out << std::endl;
    }
}