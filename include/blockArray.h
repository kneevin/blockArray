#pragma once
#ifndef __BLOCK_ARRAY__
#define __BLOCK_ARRAY__

#include <queryRange.h>
#include <rangeNode.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <cassert>

class blockArray {
private:
    int size;
    rangeNode *root;

public:
    blockArray(std::vector<int>& arr);
    void bfsPrint();

    void updateRange(int newVal, int newLeft, int newRight);
    void updateHelper(rangeNode* root, queryRange* qr);
    int get(int i);
};

#endif