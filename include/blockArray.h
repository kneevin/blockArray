#pragma once
#ifndef __BLOCK_ARRAY__
#define __BLOCK_ARRAY__

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

    void queryRange(int newVal, int newLeft, int newRight);
    int get(int i);
};

#endif