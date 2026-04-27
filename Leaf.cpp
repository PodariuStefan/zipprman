#include "Leaf.h"

Leaf::Leaf() {
    value = 0;
    pred = nullptr;
}

Leaf::Leaf(int sum_value, Leaf* pred_leaf) {
    value = sum_value;
    pred = pred_leaf;
}
