#include "Leaf.h"
#include <iostream>

Leaf::Leaf() {
    symbol = 0;
    frequency = 0;
}

Leaf::Leaf(const char& letter, const int& frequency) {
    this->symbol = letter;
    this->frequency = frequency;
}

void Leaf::showLeaf() {
    std::cout << "{" << this->symbol << ", " << this->frequency << "}" << std::endl;
}