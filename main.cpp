#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

class rangeNode {
private:
    int v, lv, rv, mid; // range = [lv, rv]
    rangeNode *left, *right;
public:
    rangeNode(int value, int leftValue, int rightValue) {
        v = value;
        lv = leftValue;
        rv = rightValue;
        mid = (lv + rv) / 2;
    }

    void setLeft(rangeNode *leftChild) { left = leftChild; }
    void setRight(rangeNode *rightChild) { right = rightChild; }
    void setValue(int value) { v = value; }

    bool contains(int v) const { return lv <= v &&  v < rv; }
    bool contains(rangeNode *rng) const {
        return lv <= rng->getLV() && rng->getRV() <= rv;
    }

    bool isLeaf() const { return !left && !right; }
    int getValue() const {
        assert(isLeaf());
        return v;
    }

    int getLV() const { return lv; }
    int getRV() const { return rv; }
    int getMid() const { return mid; }

    rangeNode* rearrangeChildren(rangeNode *queryRange) {

    }
};

class blockArray {
private:
    int n;

public:

};


int main() {
    std::cout << "hey" << '\n';
    rangeNode a = rangeNode(2, 1, 3);
    std::cout << a.isLeaf();
}