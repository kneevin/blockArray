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
        std::cout << startPoint << ": " << endPoint << '\n';
        if(!curNode || startPoint > endPoint) { return; }
        if(curNode->isExactInterval(startPoint, endPoint)) {
            curNode->updateLeaf(newValue);
            return;
        }
        
        int m = curNode->mid;
        assignRange(curNode->left, startPoint, m, newValue);
        assignRange(curNode->right, m + 1, endPoint, newValue);
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
        // l, r are the 
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
        inorderPrint(root);
    }

    void inorderPrint(rangeNode *node) {
        if(node == NULL) { return; }
        inorderPrint(node->left);

        node->print();
        std::cout << '\n';

        inorderPrint(node->right);
    }

};

int main(){
    rangeNode *n1 = new rangeNode(0, 10, 3);
    rangeNode *n2 = new rangeNode(2, 3, 5);
    std::cout << n2->overlaps(n1) << '\n';
    std::cout << n1->contains(2) << '\n';


    int int_temp, n; std::cin >> n;
    std::vector<int> arr; arr.reserve(n);
    while(n--) { std::cin >> int_temp; arr.push_back(int_temp); }

    blockArray obj = blockArray(arr);
    // obj.printTree();
    obj.update(0, 2, 10);
    obj.update(3, 7, -10);
    obj.printTree();
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