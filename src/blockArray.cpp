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

void blockArray::queryRange(int newVal, int newLeft, int newRight) {
    int mid = rangeNode::calculateMid(newLeft, newRight);
    rangeNode *cur = root;

}

void blockArray::_queryRange(rangeNode* root, int newLeft, int newRight) {
    if(root->equals(newLeft, newRight)) {}
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
