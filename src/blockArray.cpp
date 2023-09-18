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
    queryRange* qr = new queryRange(newVal, newLeft, newRight);
    rangeNode *cur = root;
    updateHelper(cur, qr);
}

void blockArray::updateHelper(rangeNode* root, queryRange* qr) {
    if(root->equals(qr->getLeft(), qr->getRight())) {
        root->setAsLeaf(qr->getValue());
    }
    if(root->contains(qr->getLeft()) && root->contains(qr->getRight())) {

    }
    // rangeNode* nextNode = root->getContainingChild();
}

int blockArray::get(int i) {
    rangeNode *cur = root;
    while(cur && !cur->isLeaf()) {
        cur->print();
        cur = cur->getContainingChild(i);
    }
    cur->print();
    assert(cur);
    return cur->getRV();
}

void blockArray::bfsPrint() {
    root->printTree(false, true);
}
