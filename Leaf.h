#ifndef ZIPPRMAN_LEAF_H
#define ZIPPRMAN_LEAF_H

class Leaf {
    int value;
    Leaf* pred;
public:
    Leaf(int, Leaf*);
    Leaf();
};

#endif //ZIPPRMAN_LEAF_H