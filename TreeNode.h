#ifndef ZIPPRMAN_TREENODE_H
#define ZIPPRMAN_TREENODE_H

#include "Leaf.h"

class TreeNode {
    TreeNode* left;
    TreeNode* right;
    Leaf data;
public:
    static int NumOfNodes;
    TreeNode();
    TreeNode(TreeNode*, TreeNode*, Leaf&);
    TreeNode(const TreeNode& node);
    //~TreeNode();
    TreeNode* getLeft();
    TreeNode* getRight();
    Leaf getData();
    bool isLeaf();
    static int sumOfNodes(const TreeNode&, const TreeNode&);
    static void updateCount(bool);


    friend class Tree;
};


#endif //ZIPPRMAN_TREENODE_H