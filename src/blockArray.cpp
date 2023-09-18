#include <blockArray.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>

blockArray::blockArray(std::vector<int>& arr) {
    size = arr.size();
    root = new rangeNode(arr);
}

void blockArray::bfsPrint() {
    root->printTree(false, true);
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