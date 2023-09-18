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
    rangeNode(std::vector<int>& arr) {
        int n = arr.size();
        v = n; lv = 0; rv = n - 1; mid = (lv + rv) / 2;
        left = splitToIndex(arr, lv, mid);
        right = splitToIndex(arr, mid + 1, rv);
    }
    
    rangeNode* splitToIndex(std::vector<int>& arr, int l, int r) {
        if(l == r) { return new rangeNode(arr[l], l, r); }
        int newMid = (l + r) / 2;
        rangeNode* root = new rangeNode(l, r);
        root->setLeft(splitToIndex(arr, l, newMid));
        root->setRight(splitToIndex(arr, newMid + 1, r));
        return root;
    }

    rangeNode(int value, int leftValue, int rightValue) {
        v = value;
        lv = leftValue;
        rv = rightValue;
        mid = (lv + rv) / 2;
    }

    rangeNode(int leftValue, int rightValue) {
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

    rangeNode* getLeft() const { return left; }
    rangeNode* getRight() const { return right; }
    int getLV() const { return lv; }
    int getRV() const { return rv; }
    int getMid() const { return mid; }

    void splitChildren() {
        left = new rangeNode(v, lv, mid);
        right = new rangeNode(v, mid + 1, rv);
    }

    void printTree(bool onlyLeaves = false) {
        inorderPrint(this, onlyLeaves);
    }

    void inorderPrint(rangeNode *node, bool onlyLeaves) {
        if(!node) { return; }
        inorderPrint(node->getLeft(), onlyLeaves);
        if(onlyLeaves) {
            if(node->isLeaf()) { node->print(); }
        } else {
            node->print();
        }
        inorderPrint(node->getRight(), onlyLeaves);
    }

    void print(bool newLine = true) {
        std::cout << '[' << lv << ", " << rv << "]: " << v << " (" << (isLeaf() ? "leaf" : "not a leaf") << ")";
        if(newLine) { std::cout << '\n'; }
    }
};

class blockArray {
private:
    int size;
    rangeNode *root;

public:
    blockArray(std::vector<int>& arr) {
        size = arr.size();
        root = new rangeNode(arr);
        root->printTree(true);
    }

    void inorderPrint(rangeNode* node) {
        if(!node) { return; }
        // inorderPrint(root->getLeft());
        node->print();
        // inorderPrint(root->getRight());
    }

    void print() {
        inorderPrint(root);
    }


};

#define withInput
#if defined(withInput)
int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for(int i = 0; i < n; i++) { std::cin >> arr[i]; }
    blockArray obj = blockArray(arr);
}

#elif defined(noInput)
int main() {
    int n = 8;
    // rangeNode *a = rangeNode(n);
    blockArray obj = blockArray(n);
    // a.print();
}



#endif