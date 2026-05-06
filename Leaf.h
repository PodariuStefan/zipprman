#ifndef ZIPPRMAN_LEAF_H
#define ZIPPRMAN_LEAF_H

class Leaf {
    char symbol;
    int frequency;
public:
    Leaf(const char&, const int&);
    Leaf();
    void showLeaf();

    friend class Tree;
    friend class TreeNode;
};

#endif //ZIPPRMAN_LEAF_H