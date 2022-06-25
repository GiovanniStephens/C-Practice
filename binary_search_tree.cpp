/** This is a practice implementation of a
 * binary search tree.
 *
 * Author:  Giovanni Stephens
 * Date:    08/04/2022
 */
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Node {
    int value;
    Node *left;
    Node *right;

  public:
    Node(int data);
    int getValue();
    Node *getLeft();
    Node *getRight();
    int getHeight(Node *node);
    void setValue(int value);
    void setLeft(Node *left);
    void setRight(Node *right);
    void insert(int value);
    Node *remove(Node *root, int value);
    Node *search(int value);
    void print(Node *root); // Not sure how to print nicely
    void printRow(const Node *node, const int height, const int depth);
    void getLine(const Node *root, int depth, std::vector<int> &vals);
};

// Constructor
Node::Node(int data) {
    this->value = data;
    this->left = NULL;
    this->right = NULL;
}

// Return the value of the node
int Node::getValue() { return this->value; }

// Returns the left node
Node *Node::getLeft() { return this->left; }

// Returns the right node
Node *Node::getRight() { return this->right; }

// Set the value of the node
void Node::setValue(int value) { this->value = value; }

// Set the left node
void Node::setLeft(Node *left) { this->left = left; }

// Set the right node
void Node::setRight(Node *right) { this->right = right; }

// Insert a value into the tree
void Node::insert(int value) {
    if (value < this->value) {
        if (this->left == NULL) {
            this->left = new Node(value);
        } else {
            this->left->insert(value);
        }
    } else {
        if (this->right == NULL) {
            this->right = new Node(value);
        } else {
            this->right->insert(value);
        }
    }
}

// Deletes a node using the copy method
Node *Node::remove(Node *root, int value) {
    if (root == NULL) {
        return NULL;
    }
    if (value < root->value) {
        root->left = remove(root->left, value);
    } else if (value > root->value) {
        root->right = remove(root->right, value);
    } else {
        if (root->left == NULL) {
            Node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        Node *temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        temp->left = root->left;
        delete root;
        return root->right;
    }
    return root;
}

int Node::getHeight(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

void Node::printRow(const Node *p, const int height, int depth) {
    std::vector<int> vec;
    getLine(p, depth, vec);
    std::cout << std::setw((height - depth) * 2); // scale setw with depth
    bool toggle = true;                           // start with left
    if (vec.size() > 1) {
        for (int v : vec) {
            if (v != (1 << 31)) {
                if (toggle) {
                    std::cout << "/"
                              << "   ";
                } else {
                    std::cout << "\\"
                              << "   ";
                }
            }
            toggle = !toggle;
        }
        std::cout << std::endl;
        std::cout << std::setw((height - depth) * 2);
    }
    for (int v : vec) {
        if (v != (1 << 31)) {
            std::cout << v << "   ";
        }
    }
    std::cout << std::endl;
}

void Node::getLine(const Node *root, int depth, std::vector<int> &vals) {
    if (depth <= 0 && root != nullptr) {
        vals.push_back(root->value);
        return;
    }
    if (root->left != nullptr) {
        getLine(root->left, depth - 1, vals);
    } else if (depth - 1 <= 0) {
        vals.push_back((1 << 31));
    }
    if (root->right != nullptr) {
        getLine(root->right, depth - 1, vals);
    } else if (depth - 1 <= 0) {
        vals.push_back((1 << 31));
    }
}

void Node::print(Node *p) {
    int height = getHeight(p) * 2;
    for (int i = 0; i < height; i++) {
        printRow(p, height, i);
    }
}

int main() {
    // Create a tree
    Node *root = new Node(10);
    root->insert(5);
    root->insert(15);
    root->insert(3);
    root->insert(7);
    root->insert(13);
    root->remove(root, 5);
    root->print(root);

    return 0;
}