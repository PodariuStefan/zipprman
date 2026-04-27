#include "Tree.h"
#include <iterator>

Vocabulary<char, int>* Tree::find_alphabet(const std::string& message) {
    std::stringstream ss(message);
    char ch;
    auto* alphabet = new Vocabulary<char, int>();

    while (ss.get(ch)) {
        if (alphabet->search(ch) == alphabet->find_len()) {
            alphabet->add(ch, 1);
        } else {
            (*alphabet)[ch]++;
        }
    }
    return alphabet;
}

Tree::Tree(const std::string& path) {
    std::ifstream file(path);
    const std::string message = std::string(std::istreambuf_iterator<char>(file),
                                            std::istreambuf_iterator<char>());
    auto alphabet = find_alphabet(message);
    alphabet->qsort(0, alphabet->find_len() - 1, Vocabulary<char,int>::compare);
    alphabet->display_all();
    free(alphabet);
}

