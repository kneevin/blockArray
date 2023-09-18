#include <iostream>
#include <vector>
#include <algorithm>
#include<deque>
#include <string>
#include <cassert>

class rangeNode {
private:
    int v, lv, rv, mid; // range = [lv, rv]
    rangeNode *left, *right;
public:
    rangeNode(std::vector<int>& arr) {
        int n = arr.size();
        v = n; lv = 0; rv = n - 1; mid = calculateMid(lv, rv);
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
        assert(leftValue <= rightValue);
        v = value;
        lv = leftValue;
        rv = rightValue;
        mid = calculateMid(lv, rv);
    }

    rangeNode(int leftValue, int rightValue) 
        : rangeNode(-1, leftValue, rightValue) {}

    int calculateMid(int l, int r) { return l + (r - l) / 2; }

    void setLeft(rangeNode *leftChild) { left = leftChild; }
    void setRight(rangeNode *rightChild) { right = rightChild; }
    void setValue(int value) { v = value; }

    bool contains(int v) const { return lv <= v &&  v < rv; }
    bool leftContains(int v) const {return left->contains(v); }
    bool rightContains(int v) const {return right->contains(v); }

    bool contains(rangeNode *rng) const { return lv <= rng->getLV() && rng->getRV() <= rv; }
    bool leftContains(rangeNode *rng) const { return left->contains(rng); }
    bool rightContains(rangeNode *rng) const { return right->contains(rng); }

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

    void printTree(bool onlyLeaves = false, bool bfs = false) {
        if(bfs) { bfsPrint(this); }
        else { inorderPrint(this, onlyLeaves); }
    }

    static void inorderPrint(rangeNode *node, bool onlyLeaves) {
        if(!node) { return; }
        inorderPrint(node->getLeft(), onlyLeaves);
        if(onlyLeaves) {
            if(node->isLeaf()) { node->print(); }
        } else {
            node->print();
        }
        inorderPrint(node->getRight(), onlyLeaves);
    }

    static void bfsPrint(rangeNode *root) {
        std::deque<rangeNode*> q;
        int lvl = 0;
        q.push_back(root);
        while(!q.empty()) {
            std::deque<rangeNode*> new_q;
            std::cout << "Level " << lvl++ << '\n';
            while(!q.empty()) {
                rangeNode *cur = q.back(); q.pop_back();
                cur->print();
                if(cur->getLeft()) { new_q.push_back(cur->getLeft()); }
                if(cur->getRight()) { new_q.push_back(cur->getRight()); }
                
            }
            q = new_q;
            std::cout << '\n';
        }
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
    }

    void bfsPrint() {
        root->printTree(false, true);
    }
};

#define withInput
#if defined(withInput)
int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for(int i = 0; i < n; i++) { std::cin >> arr[i]; std::cout << arr[i] << ' '; }
    blockArray obj = blockArray(arr);
    obj.bfsPrint();
}

#elif defined(noInput)
int main() {
    int n = 8;
    // rangeNode *a = rangeNode(n);
    blockArray obj = blockArray(n);
    // a.print();
}



#endif