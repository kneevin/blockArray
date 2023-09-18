#pragma once
#ifndef __QUERY_RANGE__
#define __QUERY_RANGE__

#include <blockArray.h>
#include <rangeNode.h>
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

    int getValue() const;
};

#endif