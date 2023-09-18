#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <cassert>
#include <blockArray.h>
#include <queryRange.h>

blockArray processInput();
void processNextQuery(blockArray *obj);

#define testInput
// #if defined()
#if defined(testInput)
int main() {
    int n = 16;
    std::vector<int> arr(n);
    for(int i = 0; i < n; i++) { arr[i] = i + 1; }
    
    blockArray obj = blockArray(arr);
    obj.updateRange(65, 0, 9);
    for(int i = 0; i < n; i++) { std::cout << i << ": " << obj.get(i) << '\n'; }
}


#elif defined(usingQuery)
int main() {
    blockArray obj = processInput();
    // obj.bfsPrint();
    int nQueries; std::cin >> nQueries;
    while(nQueries--) {
        std::string query_t; std::cin >> query_t;
        if(query_t == "UPDATE") {
            int l, r, v;
            std::cin >> l >> r >> v;
            // std::cout << query_t << " [" << l << ", " << r << "]: " << v << '\n';
            // obj.bfsPrint();
            obj.updateRange(v, l, r);
            obj.bfsPrint();
        }
        if(query_t == "GET") {
            int i; std::cin >> i;
            int val = obj.get(i);
            // std::cout << query_t << '(' << i << "): " << val << std::endl;
        }
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

void processNextQuery(blockArray *obj) {
    std::string query_t; std::cin >> query_t;
    if(query_t == "UPDATE") {
        int l, r, v;
        std::cin >> l >> r >> v;
        std::cout << query_t << '\n';
    }
    if(query_t == "GET") {
        int i; std::cin >> i;

        std::cout << query_t << '(' << i << "): " << obj->get(i) << std::endl;
    }

}

blockArray processInput() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for(int i = 0; i < n; i++) { std::cin >> arr[i]; }

    return blockArray(arr);
}