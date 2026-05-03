#ifndef ZIPPRMAN_TREENODE_H
#define ZIPPRMAN_TREENODE_H

#include "Leaf.h"

class TreeNode {
    TreeNode* left;
    TreeNode* right;
    Leaf data;
public:
    TreeNode();
    TreeNode(TreeNode*, TreeNode*, Leaf&);
    TreeNode(const TreeNode& node);
    TreeNode* getLeft();
    TreeNode* getRight();
    bool isLeaf();
    static int sumOfNodes(const TreeNode&, const TreeNode&);


    friend class Tree;
};


#endif //ZIPPRMAN_TREENODE_H