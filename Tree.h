//
// Created by stephen on 16.03.2026.
//

#ifndef ZIPPRMAN_TREE_H
#define ZIPPRMAN_TREE_H
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Leaf.h"
#include <algorithm>

/* DATA STRUCTURE USED FOR REPRESENTING A LETTER AND ITS FREQUENCY */

template <class key, class value>
class Vocabulary {
    std::vector<std::pair<key, value>> entry;
public:
    Vocabulary(key arg1, value arg2) {
        add(arg1, arg2);
    }

    Vocabulary() {
        ;
    }

    value& operator [](key& target) {
        int pos = search(target);
        if (pos != this->find_len()) {
            return *(&(this->entry[pos].second));
        } else {
            throw std::out_of_range("Target not found");
        }
    }

    key get_key(std::pair<key, value> pair) {
        return pair.first;
    }

    value get_value(std::pair<key, value> pair) {
        return pair.second;
    }

    std::vector<key>* get_keys() {
        auto keys = new std::vector<key>();
        for (std::pair<key, value> pair: entry) {
            keys->push_back(pair.first);
        }
        return keys;
    }

    std::vector<value>* get_values() {
        auto values = new std::vector<value>();
        for (std::pair<key, value> pair: entry) {
            values->push_back(pair.first);
        }
        return values;
    }

    void add(key arg1, value arg2) {
        entry.push_back(std::make_pair(arg1, arg2));
        //display_all();
    }

    void remove(key target) {
        auto index = std::find(entry.begin(), entry.end(), target);
        if (index != entry.end()) {
            entry.erase(index);
        }
    }

    int find_len() {
        return entry.size();
    }

    void display(std::pair<key, value> pair) {
        std::cout << '{' << pair.first << ',' << pair.second << '}' << std::endl;
    }

    void display_all() {
        for (std::pair<key, value> pair: entry) {
            display(pair);
            std::cout << std::endl;
        }
    }

    static bool compare(value a, value b) {
        return a < b;
    }

    void qsort(int l, int r, bool (*cmp)(value a, value b)) {
        if (l < r) {
            int pivot = partition(l, r, cmp);
            qsort(l, pivot - 1, cmp);
            qsort(pivot + 1, r, cmp);
        }
    }

    int partition(int l, int r, bool (*cmp)(value a, value b)) {
        value pivot_value = this->entry[r].second;
        int i = l, j = r - 1;
        while (i <= j) {
            if (!cmp(this->entry[i].second, pivot_value)) {
                if (cmp(this->entry[j].second, pivot_value)) {
                    std::swap(this->entry[i], this->entry[j]);
                    i++;
                    j--;
                } else {
                    j--;
                }
            } else {
                i++;
            }
        }

        std::swap(this->entry[i], this->entry[r]);

        return i;
    }

    int search(key &target) {
        int index = 0;
        std::vector<std::pair<key, value>> current_keys;
        for (std::pair<key, value> pair: entry) {
            current_keys.push_back(pair);
        }
        for (std::pair<key, value> pair: current_keys) {
            if (target == pair.first) {
                return index;
            }
            index++;
        }
        return this->find_len();
    }
};

class Tree {
    Leaf* root;
public:
    Vocabulary<char, int>* find_alphabet(const std::string&);
    /* vector containing key, value pairs where key is alphabet and key
     * is frequency */
    Tree(const std::string&);
};


#endif //ZIPPRMAN_TREE_H