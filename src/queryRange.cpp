#include <blockArray.h>
#include <rangeNode.h>
#include <queryRange.h>

queryRange::queryRange(int newLeft, int newRight, int newValue) {
    l = newLeft; r = newRight; v = newValue; 
    mid = rangeNode::calculateMid(l, r);
}

int queryRange::getValue() const { return r; }