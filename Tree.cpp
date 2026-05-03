#include "Tree.h"
#include "TreeNode.h"
#include <iterator>
#include <limits.h>

Vocabulary<char, int>* Tree::find_alphabet(const std::string& message) {
    std::stringstream ss(message);
    char ch;
    auto* alphabet = new Vocabulary<char, int> ();

    while (ss.get(ch)) {
        if (alphabet->search(ch) == alphabet->find_len()) {
            alphabet->add(ch, 1);
        } else {
            (*alphabet)[ch].second++;
        }
    }
    return alphabet;
}

Tree::Tree(const std::string& path) {
    std::ifstream file(path);
    std::vector<TreeNode> all_nodes; // used for reading the binary representation of the tree compression
    const std::string message = std::string(std::istreambuf_iterator<char>(file),
                                            std::istreambuf_iterator<char>());
    auto alphabet = find_alphabet(message);

    alphabet->qsort(0, alphabet->find_len() - 1, Vocabulary<char,int>::compare);
    for (auto frequency : (*alphabet).entry) {
        Leaf* new_leaf = new Leaf(frequency.first, frequency.second);
        auto node = TreeNode(nullptr, nullptr, *new_leaf);
        all_nodes.push_back(node);
    }
    free(alphabet);

    while (true) {
        if (all_nodes.size() == 1) {
            root = &all_nodes[0];
            break;
        }
        std::cout << all_nodes.size() << " nodes found" << std::endl << std::endl;
        TreeNode* lowest;
        TreeNode* second_lowest;
        int lowest_index = lowest_node(all_nodes);
        lowest = extract_node(all_nodes, lowest_index);
        int second_lowest_index = lowest_node(all_nodes);
        second_lowest = extract_node(all_nodes, lowest_index);
        std::cout << all_nodes.size() << " nodes found" << std::endl << std::endl;


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

        std::cout << "First: " << lowest << " Second: " << second_lowest << std::endl << std::endl;
        for (auto node : all_nodes) {
            node.data.showLeaf();
        }
        std::cout << all_nodes.size() << " nodes found" << std::endl << std::endl;
    }
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

