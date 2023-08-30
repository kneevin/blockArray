#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

struct rangeNode {
    // if startPoint == endPoint or isLeaf -> leaf node
    int startPoint, endPoint, mid, value; // inclusive, [startPoint, endPoint] -> these indices have value
    rangeNode *left, *right;
    bool isLeaf;

    rangeNode(int start, int end_) {
        startPoint = start;
        endPoint = end_;
        mid = (start + end_) / 2;
        isLeaf = (startPoint == endPoint);
        value = -1;
    }

    rangeNode(int start, int end_, int value_) {
        startPoint = start;
        endPoint = end_;
        mid = (start + end_) / 2;
        value = value_;
        isLeaf = true;
    }

    void updateLeaf(int newValue) {
        isLeaf = true;
        value = newValue;
        left = right = NULL;
    }

    rangeNode* lowerBound(int point) {
        rangeNode* cur = left;
        while(left && left->contains(point)) { cur = cur->left; }
        return cur;
    }

    rangeNode* upperBound(int point) {
        rangeNode* cur = right;
        while(right && right->contains(point)) { cur = cur->right; }
        return cur;
    }

    rangeNode* splitOn(int idx) {
        assert(contains(idx) && isLeaf);
        rangeNode* leftNode = new rangeNode(startPoint, idx, value);
        startPoint = idx + 1;
        return leftNode;
    }

    bool isExactInterval(int newStartPoint, int newEndPoint) {
        return startPoint == newStartPoint && newEndPoint == endPoint;
    }

    bool containsInterval(int newStartPoint, int newEndPoint) {
        return startPoint <= newStartPoint && newEndPoint <= endPoint;
    }

    bool leftContainsInterval(int newStartPoint, int newEndPoint) {
        return left && left->containsInterval(newStartPoint, newEndPoint);
    }

    bool rightContainsInterval(int newStartPoint, int newEndPoint) {
        return right && right->containsInterval(newStartPoint, newEndPoint);
    }

    bool contains(int val) const {
        return startPoint <= val && val <= endPoint;
    }

    bool overlaps(rangeNode *other) const {
        return startPoint <= other->endPoint && other->startPoint <= endPoint;
    }

    bool is_leaf() {
        return !left && !right;
    }

    rangeNode* join(rangeNode* other, int new_value) {
        assert(overlaps(other));
        return new rangeNode(std::min(startPoint, other->startPoint),
                             std::max(endPoint, other->endPoint),
                             new_value);
    }

    void print() {
        std::cout << "[ " << startPoint << ", " << endPoint << "]: " << value;
        if(isLeaf) { std::cout << " (leaf)"; }
    }
};

class blockArray {
private:
    rangeNode *root;
    int n;
public:
    blockArray(std::vector<int>& arr) {
        n = arr.size();
        root = new rangeNode(0, n - 1);
        buildTree(arr, root, (n - 1)/2);
    }

    void update(int startPoint, int endPoint, int newValue) {
        assignRange(root, startPoint, endPoint, newValue);
    }

    void assignRange(rangeNode *curNode, int startPoint, int endPoint, int newValue) {
        // std::cout << startPoint << ": " << endPoint << '\n';
        if(!curNode || startPoint > endPoint) { return; }
        if(curNode->isExactInterval(startPoint, endPoint)) {
            curNode->updateLeaf(newValue);
            return;
        }
        
        int m = curNode->mid;
        if(!curNode->isLeaf) {
            assignRange(curNode->left, startPoint, m, newValue);
            assignRange(curNode->right, m + 1, endPoint, newValue);
        } else {
            rangeNode *newLeft = new rangeNode(curNode->startPoint, m, curNode->value);
            assignRange(newLeft, startPoint, m, newValue);
            
            rangeNode *newRight = new rangeNode(m + 1, curNode->endPoint, curNode->value);
            assignRange(newRight, m + 1, endPoint, newValue);

            curNode->isLeaf = false;
            curNode->left = newLeft;
            curNode->right = newRight;
        }


    }

    int getIndex(int i) {
        rangeNode *cur = root;
        while(!cur->isLeaf) {
            assert(cur->contains(i));
            if(cur->left && cur->left->contains(i)) { cur = cur->left; }
            else { cur = cur->right; }
        }
        return cur->value;
    }

    void buildTree(std::vector<int>& arr, rangeNode *curRange, int idx) {
        if(curRange->startPoint == curRange-> endPoint) {
            curRange->value = arr[idx];
            return;
        }
        int m = (curRange->startPoint + curRange->endPoint) / 2;
        rangeNode *leftRange = new rangeNode(curRange->startPoint, m);
        rangeNode *rightRange = new rangeNode(m + 1, curRange->endPoint);

        buildTree(arr, leftRange, m);
        buildTree(arr, rightRange, m + 1);

        curRange->left = leftRange;
        curRange->right = rightRange;
    }

    void printTree() {
        inorderPrint(root, false);
    }

    void printLeaves() {
        inorderPrint(root, true);
    }



    void inorderPrint(rangeNode *node, bool onlyLeafs) {
        if(node == NULL) { return; }
        inorderPrint(node->left, onlyLeafs);

        if(onlyLeafs) {
            if(node->isLeaf) { node->print(); std::cout << '\n'; }
        } else {
            node->print();
            std::cout << '\n';
        }
        
        

        inorderPrint(node->right, onlyLeafs);
    }

};

int main(){
    rangeNode *n1 = new rangeNode(0, 10, 3);
    rangeNode *n2 = new rangeNode(2, 3, 5);


    int int_temp, n; std::cin >> n;
    std::vector<int> arr; arr.reserve(n);
    while(n--) { std::cin >> int_temp; arr.push_back(int_temp); }

    blockArray obj = blockArray(arr);
    // obj.printTree();
    obj.update(0, arr.size() - 1, 10);
    obj.printLeaves();
    std::cout << '\n';

    n = arr.size();
    for(int i = 0; i < n; i++) {
        obj.update(i, i, i+10);
        obj.printTree();
        // obj.printLeaves();
        std::cout << '\n';
    }



    std::cout << obj.getIndex(1) << '\n';

    std::string str_temp;
    int lower, upper, new_val, idx;
    std::cin >> n;
    while(n--) {
        std::cin >> str_temp;
        if(str_temp == "GET") {
            std::cin >> lower >> upper >> new_val;
        } else { // == "UPDATE"
            std::cin >> idx;
        }

    }
}