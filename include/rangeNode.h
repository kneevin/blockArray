#pragma once
#ifndef __RANGE_NODE__
#define __RANGE_NODE__

#include <queryRange.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <cassert>

class rangeNode {
private:
    int v, lv, rv, mid;
    rangeNode *left, *right;
public:
    rangeNode(std::vector<int>& arr);
    
    rangeNode* splitToIndex(std::vector<int>& arr, int l, int r);
    rangeNode(int value, int leftValue, int rightValue);
    rangeNode(int leftValue, int rightValue);

    // rangeNode* getSubset(queryRange *qr);
    std::pair<rangeNode*, rangeNode*> splitOnRange(queryRange *qr);
    rangeNode* getContainingChild(int i);

    void setLeft(rangeNode *leftChild);
    void setRight(rangeNode *rightChild);
    void setValue(int value);
    void setAsLeaf(int value);

    bool equals(int l, int r);
    bool contains(int v) const;
    bool leftContains(int v) const;
    bool rightContains(int v) const;

    bool equals(rangeNode *rng);    
    bool contains(rangeNode *rng) const;
    bool leftContains(rangeNode *rng) const;
    bool rightContains(rangeNode *rng) const;

    bool equals(queryRange *qr);
    bool contains(queryRange *qr) const;
    bool leftContains(queryRange *qr) const;
    bool rightContains(queryRange *qr) const;

    bool isLeaf() const;
    int getValue() const;

    rangeNode* getLeft() const;
    rangeNode* getRight() const;
    int getLV() const;
    int getRV() const;
    int getMid() const;

    // int calculateMid(int l, int r);
    void printTree(bool onlyLeaves = false, bool bfs = false);
    void print(bool newLine = true);

    static int calculateMid(int l, int r) { return l + (r - l) / 2; }

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
};

#endif