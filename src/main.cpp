#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <cassert>
#include <blockArray.h>
#include <queryRange.h>

blockArray processInput();
void processNextQuery(blockArray& obj);

#define usingQuery
// #if defined()
#if defined(usingQuery)


int main() {
    blockArray obj = processInput();
    // obj.bfsPrint();
    int nQueries; std::cin >> nQueries;
    while(nQueries--) {
        processNextQuery(obj);
    }
    
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

void processNextQuery(blockArray& obj) {
    std::string query_t;
    std::cin >> query_t;

    if(query_t == "UPDATE") {
        int l, r, v;
        std::cin >> l >> r >> v;
    } else if(query_t == "GET") {
        int i; std::cin >> i;
        std::cout << obj.get(i) << '\n';
    }

}

blockArray processInput() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for(int i = 0; i < n; i++) { std::cin >> arr[i]; }

    return blockArray(arr);
}