#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {};
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {};
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {};
};

struct BinarySearchTree {
    TreeNode* root = nullptr;

    TreeNode* insertNode(int data) {
        root = insertNodeHelper(root, data);
        return root;
    }
    TreeNode* insertNodeHelper(TreeNode* root, int data) {
        if (root == nullptr) {
            root = new TreeNode(data);
        } else if (root->val > data) {
            root->left = insertNodeHelper(root->left, data);
        } else if (root->val < data) {
            root->right = insertNodeHelper(root->right, data);
        }
        // if root->val == data -> duplicate, do nothing (ignored)
        return root;
    }

    void displayTree() {
        cout << "display the tree " << endl;
        cout << "-------------------------------------------" << endl;
        displayTreeHelper(root);
        cout << "End of  the tree " << endl;
        cout << "-------------------------------------------" << endl;
    }
    void displayTreeHelper(TreeNode* root) {
        if (root == nullptr) return;
        displayTreeHelper(root->left);
        cout << "> " << root->val << endl;
        displayTreeHelper(root->right);
    }

    bool search(int data) {
        if (root == nullptr) return false;
        if (root->val == data) return true;
        return searchHelper(root, data);
    }
    bool searchHelper(TreeNode* root, int data) {
        if (root == nullptr) return false;
        if (root->val == data)
            return true;
        else if (root->val > data)
            return searchHelper(root->left, data);
        else
            return searchHelper(root->right, data);
    }

    void removeNode(int data) {
        if (search(data)) {
            root = removeNodeHelper(root, data);
        } else {
            cout << " could not found node :" << data << endl;
        }
    };
    TreeNode* removeNodeHelper(TreeNode* root, int data) {
        if (root == nullptr) {
            return root;
        } else if (root->val > data) {
            root->left = removeNodeHelper(root->left, data);
        } else if (root->val < data) {
            root->right = removeNodeHelper(root->right, data);
        } else {
            if (root->left == nullptr && root->right == nullptr) {
                root = nullptr;
                return root;
            } else if (root->right != nullptr) {
                root->val = successor(root);
                root->right = removeNodeHelper(root->right, root->val);
            } else {
                root->val = predecessor(root);
                root->left = removeNodeHelper(root->left, root->val);
            }
        }
        return root;
    }
    int successor(TreeNode* root) {
        root = root->right;
        while (root->left != nullptr) {
            root = root->left;
        }
        return root->val;
    }
    int predecessor(TreeNode* root) {
        root = root->left;
        while (root->right != nullptr) {
            root = root->right;
        }
        return root->val;
    }
};

// Small helper just for the test driver: prints a banner so terminal output
// is easy to scan and you know exactly which test produced what's below it.
void printBanner(const string& title) {
    cout << "\n=================================================" << endl;
    cout << "  " << title << endl;
    cout << "=================================================" << endl;
}

// Small helper to print search results in a uniform "found / not found" style.
void printSearchResult(BinarySearchTree& bst, int value) {
    cout << "search(" << value << ") -> "
         << (bst.search(value) ? "FOUND" : "NOT FOUND") << endl;
}

int main() {
    cout << "just check work or not " << endl;

    // =====================================================
    // SECTION 1: INSERTION TESTS
    // =====================================================

    BinarySearchTree bst;

    printBanner("TEST 1: Insert into empty tree");
    bst.insertNode(50);
    bst.displayTree();  // expect: > 50

    printBanner("TEST 2: Insert smaller value (goes left)");
    bst.insertNode(30);
    bst.displayTree();  // expect: > 30, > 50

    printBanner("TEST 3: Insert larger value (goes right)");
    bst.insertNode(70);
    bst.displayTree();  // expect: > 30, > 50, > 70

    printBanner("TEST 4: Insert multiple values forming a balanced-ish tree");
    bst.insertNode(20);
    bst.insertNode(40);
    bst.insertNode(60);
    bst.insertNode(80);
    bst.displayTree();  // expect: > 20, > 30, > 40, > 50, > 60, > 70, > 80

    printBanner(
        "TEST 5: Insert duplicate value (duplicates should be ignored)");
    bst.insertNode(50);
    bst.displayTree();  // expect: 50 should NOT appear twice

    printBanner("TEST 6: Insert negative numbers");
    bst.insertNode(-10);
    bst.insertNode(-100);
    bst.displayTree();  // expect: -100, -10, then rest in order

    printBanner("TEST 7a: Insert into a single-branch (right-skewed) tree");
    BinarySearchTree skewed;
    skewed.insertNode(1);
    skewed.insertNode(2);
    skewed.insertNode(3);
    skewed.insertNode(4);
    skewed.displayTree();  // expect: > 1, > 2, > 3, > 4

    printBanner("TEST 7b: Insert into a single-branch (left-skewed) tree");
    BinarySearchTree skewedLeft;
    skewedLeft.insertNode(4);
    skewedLeft.insertNode(3);
    skewedLeft.insertNode(2);
    skewedLeft.insertNode(1);
    skewedLeft.displayTree();  // expect: > 1, > 2, > 3, > 4

    printBanner("TEST 8: Display empty tree (no insert at all)");
    BinarySearchTree empty;
    empty.displayTree();  // expect: nothing printed between the banners

    // =====================================================
    // SECTION 2: SEARCH TESTS
    // =====================================================
    // Rebuild a known tree so search results are predictable:
    // In-order should be: -100, -10, 30, 40, 50, 60, 70, 80
    printBanner("SEARCH SETUP: current bst contents (used for search tests)");
    bst.displayTree();

    printBanner("TEST S1: Search for the root value");
    printSearchResult(bst, 50);  // expect: FOUND

    printBanner("TEST S2: Search for a leaf node value");
    printSearchResult(bst, 80);  // expect: FOUND

    printBanner("TEST S3: Search for an internal (non-root, non-leaf) value");
    printSearchResult(bst, 70);  // expect: FOUND

    printBanner("TEST S4: Search for a value that does not exist");
    printSearchResult(bst, 9999);  // expect: NOT FOUND

    printBanner("TEST S5: Search for a negative value that exists");
    printSearchResult(bst, -100);  // expect: FOUND

    printBanner("TEST S6: Search for a negative value that does not exist");
    printSearchResult(bst, -999);  // expect: NOT FOUND

    printBanner("TEST S7: Search on an empty tree");
    printSearchResult(empty, 1);  // expect: NOT FOUND (root == nullptr branch)

    printBanner("TEST S8: Search on a single-node tree (value present)");
    BinarySearchTree singleSearch;
    singleSearch.insertNode(99);
    printSearchResult(singleSearch, 99);  // expect: FOUND

    printBanner("TEST S9: Search on a single-node tree (value absent)");
    printSearchResult(singleSearch, 1);  // expect: NOT FOUND

    printBanner("TEST S10: Search on a right-skewed chain (1->2->3->4)");
    printSearchResult(skewed, 1);  // expect: FOUND (root)
    printSearchResult(skewed, 4);  // expect: FOUND (deepest right)
    printSearchResult(skewed, 5);  // expect: NOT FOUND

    printBanner("TEST S11: Search on a left-skewed chain (4->3->2->1)");
    printSearchResult(skewedLeft, 4);  // expect: FOUND (root)
    printSearchResult(skewedLeft, 1);  // expect: FOUND (deepest left)
    printSearchResult(skewedLeft, 0);  // expect: NOT FOUND

    // =====================================================
    // SECTION 3: REMOVAL TESTS
    // =====================================================

    printBanner(
        "REMOVAL SETUP: building a fresh, larger tree for delete tests");
    bst = BinarySearchTree();  // reset bst to a clean tree
    bst.insertNode(50);
    bst.insertNode(30);
    bst.insertNode(70);
    bst.insertNode(20);
    bst.insertNode(40);
    bst.insertNode(60);
    bst.insertNode(80);
    bst.insertNode(10);
    bst.insertNode(25);
    // Initial tree in-order: 10, 20, 25, 30, 40, 50, 60, 70, 80
    bst.displayTree();

    cout << "\nStart deleting " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------" << endl;

    printBanner("TEST R1: Remove a leaf node (10)");
    bst.removeNode(10);
    bst.displayTree();  // expect: 20, 25, 30, 40, 50, 60, 70, 80

    printBanner(
        "TEST R2: Remove a node with only one child (right child) (20 -> 25)");
    bst.removeNode(20);
    bst.displayTree();  // expect: 25, 30, 40, 50, 60, 70, 80

    printBanner("TEST R3: Remove a node with only one child (left child)");
    BinarySearchTree t3;
    t3.insertNode(50);
    t3.insertNode(30);
    t3.insertNode(20);
    t3.removeNode(30);  // 30 has only left child 20
    t3.displayTree();   // expect: 20, 50

    printBanner(
        "TEST R4: Remove a node with two children (30, has children 25 and "
        "40)");
    bst.removeNode(30);
    bst.displayTree();  // expect successor (40) replaces 30

    printBanner("TEST R5: Remove the root node (root has two children)");
    bst.removeNode(50);
    bst.displayTree();  // expect tree restructured, root replaced by successor

    printBanner("TEST R6: Remove the root node when tree has only one node");
    BinarySearchTree single;
    single.insertNode(99);
    single.removeNode(99);
    single.displayTree();  // expect: nothing printed (empty tree)

    printBanner(
        "TEST R7: Remove a value that does not exist in the tree (9999)");
    bst.removeNode(9999);  // expect "could not found node" message
    bst.displayTree();     // expect: tree unchanged

    printBanner("TEST R8: Remove from an empty tree");
    empty.removeNode(5);  // expect "could not found node" message, no crash
    empty.displayTree();  // expect: nothing printed, no crash

    printBanner(
        "TEST R9: Remove all remaining nodes one by one (should leave empty "
        "tree)");
    bst.removeNode(25);
    bst.removeNode(40);
    bst.removeNode(60);
    bst.removeNode(70);
    bst.removeNode(80);
    bst.displayTree();  // expect: nothing printed (empty tree)

    printBanner("TEST R10: Remove the same value twice");
    bst.removeNode(40);
    bst.removeNode(40);  // second call should print "could not found", no crash
    bst.displayTree();   // expect: nothing printed (still empty)

    printBanner("ALL TESTS DONE");
    return 0;
}
