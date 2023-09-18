#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <cassert>
#include <blockArray.h>
#include <queryRange.h>

blockArray processInput();

#define usingQuery
// #if defined()
#if defined(usingQuery)


int main() {
    blockArray obj = processInput();
    obj.bfsPrint();
}

#elif defined(includeBlockArray)
#include <blockArray.h>
int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for(int i = 0; i < n; i++) { std::cin >> arr[i]; std::cout << arr[i] << ' '; }
    blockArray obj = blockArray(arr);
    obj.bfsPrint();
}

#elif defined(includeRange)
#include <rangeNode.h>
int main() {
    rangeNode *obj = new rangeNode(0, 1);
    obj->print();
}


#elif defined(noInput)
int main() {
    int n = 8;
    // rangeNode *a = rangeNode(n);
    blockArray obj = blockArray(n);
    // a.print();
}

#endif

blockArray processInput() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for(int i = 0; i < n; i++) { std::cin >> arr[i]; }

    return blockArray(arr);
}