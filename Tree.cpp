#include "Tree.h"

#include <bitset>

#include "TreeNode.h"
#include <iterator>
#include <limits.h>

Vocabulary<char, int>* Tree::find_alphabet(const std::vector<char>& binary_buffer) {
    auto* alphabet = new Vocabulary<char, int> ();
    for (int i = 0; i < binary_buffer.size(); i++) {
        char byte = binary_buffer[i];
        if (alphabet->search(byte) == alphabet->find_len()) {
            alphabet->add(byte, 1);
        } else {
            (*alphabet)[byte].second++;
        }
    }
    return alphabet;
}

Tree::Tree(const std::string& path) {
    std::unordered_map<unsigned char, std::string> freq_map;
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    auto filesize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> binbuf(filesize);
    file.read(binbuf.data(), filesize);
    file.close();

    std::vector<TreeNode> all_nodes; // used for reading the binary representation of the tree compression

    auto alphabet = find_alphabet(binbuf);

    alphabet->qsort(0, alphabet->find_len() - 1, Vocabulary<char,int>::compare);
    for (auto frequency : (*alphabet).entry) {
        Leaf* new_leaf = new Leaf(frequency.first, frequency.second);
        auto node = TreeNode(nullptr, nullptr, *new_leaf);
        all_nodes.push_back(node);
    }
    delete alphabet;

    while (true) {
        if (all_nodes.size() == 1) {
            auto rootNode = new TreeNode(all_nodes[0].left, all_nodes[0].right, all_nodes[0].data);
            TreeNode::NumOfNodes--;
            root = rootNode;
            break;
        }
        //std::cout << all_nodes.size() << " nodes found" << std::endl << std::endl;
        TreeNode* lowest;
        TreeNode* second_lowest;
        int lowest_index = lowest_node(all_nodes);
        //std::cout << lowest_index << std::endl;
        lowest = extract_node(all_nodes, lowest_index);
        //std::cout << "First lowest extracted" << std::endl;
        int second_lowest_index = lowest_node(all_nodes);
        second_lowest = extract_node(all_nodes, second_lowest_index);
        //std::cout << "Second lowest extracted" << std::endl;
        //std::cout << all_nodes.size() << " nodes found" << std::endl << std::endl;


        int sum = TreeNode::sumOfNodes(*lowest, *second_lowest);
        if (lowest_index < second_lowest_index) {
            auto* new_leaf = new Leaf('-', sum);
            auto new_node = new TreeNode(lowest, second_lowest, *new_leaf);
            all_nodes.push_back(*new_node);
        } else {
            auto* new_leaf = new Leaf('-', sum);
            auto new_node = new TreeNode(second_lowest, lowest, *new_leaf);
            all_nodes.push_back(*new_node);
        }

        //std::cout << "First: " << lowest << " Second: " << second_lowest << std::endl << std::endl;

        //std::cout << all_nodes.size() << " nodes found" << std::endl << std::endl;
    }

    //std::cout << TreeNode::NumOfNodes << " nodes found" << std::endl << std::endl;

    // for (int i = 0; i < marked.size(); i++) {
    //     marked[i] = false;
    // }

    std::string encoding;
}

int Tree::lowest_node(std::vector<TreeNode>& nodes) {
    int index = 0;
    int lowest_node_value = INT_MAX;

    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].data.frequency < lowest_node_value) {
            lowest_node_value = nodes[i].data.frequency;
            index = i;
        }
    }

    return index;
}

TreeNode* Tree::extract_node(std::vector<TreeNode>& nodes, int index) {
    if (nodes.empty()) {
        return nullptr;
    }
    auto* copy = new TreeNode(nodes[index]);
    nodes.erase(nodes.begin() + index);
    return copy;
}

void Tree::dfs(TreeNode *node, std::string& encoding, std::unordered_map<unsigned char, std::string>& freq_map) {
    TreeNode* current_node = node;
    if (current_node == nullptr) {
        return;
    }
    if (current_node->isLeaf()) {
        freq_map.insert({current_node->data.symbol, encoding}); // return to a mapping the encoding and the symbol
        encoding.pop_back(); //removes the last bit from encoding when traversing back the tree
        return;
    }
    TreeNode* neighbors[2];
    neighbors[0] = current_node->getLeft();
    neighbors[1] = current_node->getRight();
    current_node->getData();
    for (int i = 0; i < 2; i++) {
            if (i == 0) {
                encoding += "0";
            } else {
                encoding += "1";
            }
            dfs(neighbors[i], encoding, freq_map);
    }
    if (!encoding.empty()) {
        encoding.pop_back();
    }
}

TreeNode* Tree::getRoot() {
    return this->root;
}