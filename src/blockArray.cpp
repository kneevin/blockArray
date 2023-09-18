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