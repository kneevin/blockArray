#include <queryRange.h>
#include <blockArray.h>
#include <rangeNode.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <deque>

blockArray::blockArray(std::vector<int>& arr) {
    size = arr.size();
    root = new rangeNode(arr);
}

void blockArray::updateRange(int newVal, int newLeft, int newRight) {
    queryRange *qr = new queryRange(newLeft, newRight, newVal);
    rangeNode *cur = root;
    updateHelper(cur, qr);
}

void blockArray::updateHelper(rangeNode* root, queryRange* qr) {
    if(!root || !qr) { return; }
    if(root->equals(qr)) { root->setAsLeaf(qr->getValue()); return; }

    rangeNode* cur = findSmallestRange(qr);
    if(cur->equals(qr)) { updateHelper(cur, qr); return; }
    else if(cur->isLeaf()){
        cur->splitToChildren();
        updateHelper(cur, qr);
        return;
    }

    queryRange *lqr = nullptr, *rqr = nullptr;

    if(cur->leftContains(qr->getLeft())) {
        queryRange* lqr = new queryRange(qr->getLeft(), cur->getMid(), qr->getValue());
        updateHelper(cur->getLeft(), lqr);
    }
    
    if(cur->rightContains(qr->getRight())) {
        queryRange* rqr = new queryRange(cur->getMid() + 1, qr->getRight(), qr->getValue());
        updateHelper(cur->getRight(), rqr);
    }   
}

// finds first range node that contains both values
rangeNode* blockArray::findSmallestRange(int l, int r) {
    rangeNode *cur = root;
    while(cur && cur->contains(l) && cur->contains(r)) {
        if(cur->rightContains(l)) { cur = cur->getRight(); }
        else if(cur->leftContains(r)) { cur = cur->getLeft(); }
        else { break; }
    }
    return cur;
}

rangeNode* blockArray::findSmallestRange(queryRange* qr) {
    return findSmallestRange(qr->getLeft(), qr->getRight());
}

int blockArray::get(int i) {
    rangeNode *cur = root;
    while(cur && !cur->isLeaf()) { cur = cur->getContainingChild(i); }
    assert(cur);
    return cur->getRV();
}

void blockArray::bfsPrint() {
    root->printTree(false, true);
}
