#pragma once
#ifndef __QUERY_RANGE__
#define __QUERY_RANGE__

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <cassert>

class queryRange {
private:
    int l, r, v, mid;
public:
    queryRange(int newLeft, int newRight, int newValue);

    std::pair<queryRange*, queryRange*> splitOnIndex(int i);
    std::pair<queryRange*, queryRange*> splitOnMiddle();

    int getValue() const;
    int getLeft() const;
    int getRight() const;
    void print() const;
};

#endif