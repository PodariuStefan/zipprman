#include "Leaf.h"
#include <iostream>

Leaf::Leaf() {
    letter = 0;
    frequency = 0;
}

Leaf::Leaf(const char& letter, const int& frequency) {
    this->letter = letter;
    this->frequency = frequency;
}

void Leaf::showLeaf() {
    std::cout << "{" << this->letter << ", " << this->frequency << "}" << std::endl;
}