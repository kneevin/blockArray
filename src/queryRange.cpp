// #include <blockArray.h>
// #include <rangeNode.h>
#include <queryRange.h>
#include <cassert>

queryRange::queryRange(int newLeft, int newRight, int newValue) {
    assert(newLeft <= newRight);
    l = newLeft; r = newRight; v = newValue; 
    mid = l + (r - l) / 2;
}

std::pair<queryRange*, queryRange*> queryRange::splitOnIndex(int i) {
    assert((l <= i && i <= r) || (l == r));
    return {new queryRange(l, i, v), new queryRange(i + 1, r, v)};
}

std::pair<queryRange*, queryRange*> queryRange::splitOnMiddle() {
    return splitOnIndex(mid);
}

int queryRange::getValue() const { return v; }
int queryRange::getLeft() const { return l; }
int queryRange::getRight() const { return r; }

void queryRange::print() const {
    std::cout << "UPDATE [" << l << ", " << r << "]: " << v << '\n';
}