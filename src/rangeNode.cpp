#include <rangeNode.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <cassert>

rangeNode::rangeNode(std::vector<int>& arr) {
    int n = arr.size();
    v = n; lv = 0; rv = n - 1; mid = calculateMid(lv, rv);
    left = splitToIndex(arr, lv, mid);
    right = splitToIndex(arr, mid + 1, rv);
}

rangeNode* rangeNode::splitToIndex(std::vector<int>& arr, int l, int r) {
    if(l == r) { return new rangeNode(arr[l], l, r); }

    int newMid = calculateMid(l, r);
    rangeNode* root = new rangeNode(l, r);
    root->setLeft(splitToIndex(arr, l, newMid));
    root->setRight(splitToIndex(arr, newMid + 1, r));

    return root;
}

rangeNode::rangeNode(int value, int leftValue, int rightValue) {
    assert(leftValue <= rightValue);
    v = value;
    lv = leftValue;
    rv = rightValue;
    mid = calculateMid(lv, rv);
}

rangeNode::rangeNode(int leftValue, int rightValue) 
    : rangeNode(-1, leftValue, rightValue) {}

int rangeNode::calculateMid(int l, int r) { return l + (r - l) / 2; }

void rangeNode::setLeft(rangeNode *leftChild) { left = leftChild; }
void rangeNode::setRight(rangeNode *rightChild) { right = rightChild; }
void rangeNode::setValue(int value) { v = value; }

bool rangeNode::contains(int v) const { return lv <= v &&  v < rv; }
bool rangeNode::leftContains(int v) const {return left->contains(v); }
bool rangeNode::rightContains(int v) const {return right->contains(v); }

bool rangeNode::contains(rangeNode *rng) const { return lv <= rng->getLV() && rng->getRV() <= rv; }
bool rangeNode::leftContains(rangeNode *rng) const { return left->contains(rng); }
bool rangeNode::rightContains(rangeNode *rng) const { return right->contains(rng); }

bool rangeNode::isLeaf() const { return !left && !right; }
int rangeNode::getValue() const {
    assert(isLeaf());
    return v;
}

rangeNode* rangeNode::getLeft() const { return left; }
rangeNode* rangeNode::getRight() const { return right; }
int rangeNode::getLV() const { return lv; }
int rangeNode::getRV() const { return rv; }
int rangeNode::getMid() const { return mid; }

void rangeNode::printTree(bool onlyLeaves, bool bfs) {
    if(bfs) { bfsPrint(this); }
    else { inorderPrint(this, onlyLeaves); }
}

void rangeNode::print(bool newLine) {
    std::cout << '[' << lv << ", " << rv << "]: " << v << " (" << (isLeaf() ? "leaf" : "not a leaf") << ")";
    if(newLine) { std::cout << '\n'; }
}
