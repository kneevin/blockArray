#pragma once
#ifndef __RANGE_NODE__
#define __RANGE_NODE__


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
    int calculateMid(int l, int r);
    rangeNode* splitToIndex(std::vector<int>& arr, int l, int r);
};

#endif