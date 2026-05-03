#include "TreeNode.h"

TreeNode::TreeNode() {
    this->data = Leaf();
    this->left = nullptr;
    this->right = nullptr;
}

TreeNode::TreeNode(const TreeNode& node) {
    this->data.letter = node.data.letter;
    this->data.frequency = node.data.frequency;
    this->left = node.left;
    this->right = node.right;
}

TreeNode::TreeNode(TreeNode *node1, TreeNode *node2, Leaf &data) {
    this->left = node1;
    this->right = node2;
    this->data.letter = data.letter;
    this->data.frequency = data.frequency;
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
