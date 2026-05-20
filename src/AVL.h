#pragma once
#include <string>
#include <vector>
#include <algorithm>

class AVL {
private:
    struct Node {
        std::string name;   // Student Name
        std::string id;     // Student ID
        int height;         // Height of this Node
        Node* left;         // Left Child
        Node* right;        // Right Child

        // Constructor for a new node
        Node(std::string n, std::string i) {
            name = n;
            id = i;
            height = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root; // This is the root of the AVL tree

    // Returns the height of a node
    int h(Node* n) {
        if (n == nullptr) return 0;
        return n->height;
    }

    // Calculates the balance factor of a node
    // Balance = height of the left subtree - height of the right subtree
    int bal(Node* n) {
        if (n == nullptr) return 0;
        return h(n->left) - h(n->right);
    }

    // Updates the height of a node based on its children
    void fix(Node* n) {
        if (n == nullptr) return;
        n->height = 1 + std::max(h(n->left), h(n->right));
    }

    // Performs a right rotation
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* t = x->right;

        // Performs the actual rotation
        x->right = y;
        y->left = t;

        // Updates the heights after rotation
        fix(y);
        fix(x);
        return x;
    }

    // Performs a left rotation
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* t = y->left;

        // Performs the actual rotation
        y->left = x;
        x->right = t;

        // Updates the heights after roation
        fix(x);
        fix(y);
        return y;
    }

    // Checks the balance factor and performs rotations as needed
    Node* balanceNode(Node* n) {
        fix(n);

        // Left Heavy
        if (bal(n) > 1) {
            if (bal(n->left) < 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }

        // Right Heavy
        if (bal(n) < -1) {
            if (bal(n->right) > 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }

        return n;
    }

    // A recursive helper for insertion
    Node* insertRec(Node* n, std::string name, std::string id, bool& ok) {
        // Means reached empty spot, so insert here
        if (n == nullptr) {
            ok = true;
            return new Node(name, id);
        }

        // Traverses based on ID
        if (id < n->id)
            n->left = insertRec(n->left, name, id, ok);
        else if (id > n->id)
            n->right = insertRec(n->right, name, id, ok);
        else {
            // Means duplicate ID has been found
            ok = false;
            return n;
        }

        return balanceNode(n);
    }

    // Finds the node with the smallest ID in the subtree
    Node* minNode(Node* n) {
        while (n->left != nullptr)
            n = n->left;
        return n;
    }

    // A recursive helper for removal
    Node* removeRec(Node* n, std::string id, bool& ok) {
        if (n == nullptr) {
            ok = false;
            return nullptr;
        }

        // Searches for a node to remove
        if (id < n->id)
            n->left = removeRec(n->left, id, ok);
        else if (id > n->id)
            n->right = removeRec(n->right, id, ok);
        else {
            ok = true;

            // THe node has either 0 or 1 child
            if (n->left == nullptr || n->right == nullptr) {
                Node* temp = (n->left != nullptr) ? n->left : n->right;
                delete n;
                return temp;
            }

            // The node has 2 children
            Node* succ = minNode(n->right);
            n->name = succ->name;
            n->id = succ->id;

            bool dummy;
            n->right = removeRec(n->right, succ->id, dummy);
        }

        return balanceNode(n);
    }

    // Searches for a node by ID
    Node* findID(Node* n, std::string id) {
        if (n == nullptr) return nullptr;
        if (id == n->id) return n;
        if (id < n->id) return findID(n->left, id);
        return findID(n->right, id);
    }

    // Preorder traversal to find all matching names
    void findName(Node* n, std::string name, std::vector<std::string>& ids) {
        if (n == nullptr) return;

        if (n->name == name)
            ids.push_back(n->id);

        findName(n->left, name, ids);
        findName(n->right, name, ids);
    }

    // Inorder traversal
    void inorder(Node* n, std::vector<std::string>& v) {
        if (n == nullptr) return;
        inorder(n->left, v);
        v.push_back(n->name);
        inorder(n->right, v);
    }

    // Preorder traversal
    void preorder(Node* n, std::vector<std::string>& v) {
        if (n == nullptr) return;
        v.push_back(n->name);
        preorder(n->left, v);
        preorder(n->right, v);
    }

    // Postorder traversal
    void postorder(Node* n, std::vector<std::string>& v) {
        if (n == nullptr) return;
        postorder(n->left, v);
        postorder(n->right, v);
        v.push_back(n->name);
    }

    // Finds the nth node in inorder traversal
    bool getNth(Node* n, int& k, std::string& id) {
        if (n == nullptr) return false;

        if (getNth(n->left, k, id)) return true;

        if (k == 0) {
            id = n->id;
            return true;
        }
        k--;

        return getNth(n->right, k, id);
    }

    // Deletes all nodes in the tree
    void clear(Node* n) {
        if (n == nullptr) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

public:
    // Constructor
    AVL() {
        root = nullptr;
    }
    // Destructor
    ~AVL() {
        clear(root);
    }

    // Inserts a new student into the tree
    bool insert(std::string name, std::string id) {
        bool ok = false;
        root = insertRec(root, name, id, ok);
        return ok;
    }

    // Removes a student by ID
    bool removeID(std::string id) {
        bool ok = false;
        root = removeRec(root, id, ok);
        return ok;
    }

    // Searches for a student by ID
    bool searchID(std::string id, std::string& name) {
        Node* n = findID(root, id);
        if (n == nullptr) return false;
        name = n->name;
        return true;
    }

    // Searches for a student by name
    std::vector<std::string> searchName(std::string name) {
        std::vector<std::string> ids;
        findName(root, name, ids);
        return ids;
    }

    // Returns inorder traversal of names
    std::vector<std::string> printInorder() {
        std::vector<std::string> v;
        inorder(root, v);
        return v;
    }

    // Returns preorder traversal of names
    std::vector<std::string> printPreorder() {
        std::vector<std::string> v;
        preorder(root, v);
        return v;
    }

    // Returns postorder traversal of names
    std::vector<std::string> printPostorder() {
        std::vector<std::string> v;
        postorder(root, v);
        return v;
    }

    // Returns number of levels in the tree
    int levelCount() {
        return h(root);
    }

    // Removes the nth node in inorder traversal
    bool removeInorder(int n) {
        if (n < 0) return false;

        std::string id;
        if (!getNth(root, n, id)) return false;

        return removeID(id);
    }
};
