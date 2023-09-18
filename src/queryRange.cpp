// #include <blockArray.h>
// #include <rangeNode.h>
#include <queryRange.h>
#include <cassert>

queryRange::queryRange(int newLeft, int newRight, int newValue) {
    // assert(newLeft <= newRight);
    l = newLeft; r = newRight; v = newValue; 
    mid = l + (r - l) / 2;
}

int queryRange::getValue() const { return v; }
int queryRange::getLeft() const { return l; }
int queryRange::getRight() const { return r; }