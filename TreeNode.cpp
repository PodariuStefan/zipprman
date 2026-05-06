#include "TreeNode.h"

#include <iostream>
#include <ostream>

TreeNode::TreeNode() {
    this->data = Leaf();
    this->left = nullptr;
    this->right = nullptr;
}

TreeNode::TreeNode(const TreeNode& node) {
    this->data.symbol = node.data.symbol;
    this->data.frequency = node.data.frequency;
    this->left = node.left;
    this->right = node.right;
}

TreeNode::TreeNode(TreeNode *node1, TreeNode *node2, Leaf &data) {
    this->left = node1;
    this->right = node2;
    this->data.symbol = data.symbol;
    this->data.frequency = data.frequency;
    updateCount(0);
}

int TreeNode::NumOfNodes = 0;

Leaf TreeNode::getData() {
    return data;
};

// TreeNode::~TreeNode() {
//     std::cout<< "Se sterge adresa: " << this << ", cu frecventa: " <<std::endl;
//     this->data.showLeaf();
// }

void TreeNode::updateCount(bool mode) {
    // 0 -> add, 1 ->subtract
    if (!mode) {
        TreeNode::NumOfNodes++;
    } else {
        if (NumOfNodes <= 0) {
            NumOfNodes = 0;
        } else {
            TreeNode::NumOfNodes--;
        }
    }
}

TreeNode* TreeNode::getLeft() {
    return left;
}
TreeNode* TreeNode::getRight() {
    return right;
}

bool TreeNode::isLeaf() {
    if (this->left == nullptr && this->right == nullptr) {
        return true;
    } else {
        return false;
    }
}

int TreeNode::sumOfNodes(const TreeNode& node1, const TreeNode& node2) {
    return  node1.data.frequency + node2.data.frequency;
}
