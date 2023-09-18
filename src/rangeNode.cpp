#include <queryRange.h>
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

// need to resize if imperfect
std::pair<rangeNode*, rangeNode*> rangeNode::splitOnRange(queryRange *qr) {
    assert(!equals(qr));
    if(!contains(qr)) {
        if(left->equals(qr)) {
            return {new rangeNode(qr->getValue(), qr->getLeft(), mid), nullptr};
        }
        if(right->equals(qr)) {
            return {nullptr, new rangeNode(qr->getValue(), mid + 1, qr->getRight())};
        }
    }
    return {nullptr, nullptr};
}

rangeNode* rangeNode::getContainingChild(int i) {
    if(leftContains(i)) { return left; }
    else if(rightContains(i)) { return right; }
    else { return nullptr; }
}

void rangeNode::setLeft(rangeNode *leftChild) { left = leftChild; }
void rangeNode::setRight(rangeNode *rightChild) { right = rightChild; }
void rangeNode::setValue(int value) { v = value; }
void rangeNode::setAsLeaf(int value) {
    setValue(v);
    left = nullptr; right = nullptr;
}

bool rangeNode::equals(int l, int r) { return lv == l && rv == r; }
bool rangeNode::contains(int v) const { return lv <= v &&  v <= rv; }
bool rangeNode::leftContains(int v) const {return left && left->contains(v); }
bool rangeNode::rightContains(int v) const {return right && right->contains(v); }

bool rangeNode::equals(rangeNode *rng) { return lv == rng->getLV() && rv == rng->getRV(); }
bool rangeNode::contains(rangeNode *rng) const { return contains(rng->getLV()) && contains(rng->getRV()); }
bool rangeNode::leftContains(rangeNode *rng) const { return left->contains(rng); }
bool rangeNode::rightContains(rangeNode *rng) const { return right->contains(rng); }

bool rangeNode::equals(queryRange *qr) { return lv == qr->getLeft() && rv == qr->getRight(); }
bool rangeNode::contains(queryRange *qr) const { return contains(qr->getLeft()) && contains(qr->getRight()); }
bool rangeNode::leftContains(queryRange *qr) const { return left->contains(qr); }
bool rangeNode::rightContains(queryRange *qr) const { return right->contains(qr); }


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
