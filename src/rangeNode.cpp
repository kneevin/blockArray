#include <rangeNode.h>

rangeNode::rangeNode(std::vector<int>& arr) {
    int n = arr.size();
    v = n; lv = 0; rv = n - 1; mid = calculateMid(lv, rv);
    left = splitToIndex(arr, lv, mid);
    right = splitToIndex(arr, mid + 1, rv);
}

rangeNode* rangeNode::splitToIndex(std::vector<int>& arr, int l, int r) {
    return nullptr;
}

int rangeNode::calculateMid(int l, int r) {
    return 0;
}