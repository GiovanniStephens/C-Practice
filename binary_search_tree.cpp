/** This is a practice implementation of a 
 * binary search tree.
 * 
 * Author:  Giovanni Stephens
 * Date:    08/04/2022
 */
#include <iostream>
#include <string>

class Node {
    int value;
    Node* left;
    Node* right;
public:
    Node(int data);             // Done
    ~Node();                    // Done (maybe?)
    int getValue();             // Done
    Node* getLeft();            // Done
    Node* getRight();           // Done
    void setValue(int value);   // Done
    void setLeft(Node* left);   // Done
    void setRight(Node* right); // Done
    void insert(int value);     // Done
    Node* remove(Node* root, int value);
    Node* search(int value);
    void print(Node* root);     // Not sure how to print nicely
};

// Constructor
Node::Node(int data){
    this->value = data;
    this->left = NULL;
    this->right = NULL;
}

// Deconstructor
// Not sure if I need this if I have a remove function.
Node::~Node(){
    delete this->left;
    delete this->right;
}

// Return the value of the node
int Node::getValue(){
    return this->value;
}

// Returns the left node
Node* Node::getLeft(){
    return this->left;
}

// Returns the right node
Node* Node::getRight(){
    return this->right;
}

// Set the value of the node
void Node::setValue(int value){
    this->value = value;
}

// Set the left node
void Node::setLeft(Node* left){
    this->left = left;
}

// Set the right node
void Node::setRight(Node* right){
    this->right = right;
}


// Insert a value into the tree
void Node::insert(int value){
    if(value < this->value){
        if(this->left == NULL){
            this->left = new Node(value);
        } else {
            this->left->insert(value);
        }
    } else {
        if(this->right == NULL){
            this->right = new Node(value);
        } else {
            this->right->insert(value);
        }
    }
}

// Deletes a node using the copy method
Node* Node::remove(Node* root, int value) {
    if(root == NULL){
        return NULL;
    }
    if(value < root->value){
        root->left = remove(root->left, value);
    } else if(value > root->value){
        root->right = remove(root->right, value);
    } else {
        if(root->left == NULL){
            Node* temp = root->right;
            delete root;
            return temp;
        } else if(root->right == NULL){
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = root->right;
        while(temp->left != NULL){
            temp = temp->left;
        }
        temp->left = root->left;
        delete root;
        return root->right;
    }
    return root;
}

void Node::print(Node* root){
    if(root != NULL){
        std::cout << root->getValue() << " ";
        this->print(root->getLeft());
        this->print(root->getRight());
    }
}

int main() {
    // Create a tree
    Node* root = new Node(10);
    root->insert(5);
    root->insert(15);
    root->insert(3);
    root->insert(7);
    root->insert(13);
    root->print(root);
    root->remove(root, 5);
    root->print(root);
    return 0;
}