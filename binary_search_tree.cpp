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
    void remove(int value);
    Node* search(int value);
    void print();               // Not sure how to print nicely
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

// Incomplte
// void Node::remove(int value){
//     if(value < this->value){
//         if(this->left != NULL){
//             this->left->remove(value);
//         }
//     } else if(value > this->value){
//         if(this->right != NULL){
//             this->right->remove(value);
//         }
//     } else {
//         if(this->left == NULL && this->right == NULL){
//             delete this;
//         } else if(this->left == NULL){
//             Node* temp = this->right;
//             delete this;
//             this = temp;
//         } else if(this->right == NULL){
//             Node* temp = this->left;
//             delete this;
//             this = temp;
//         } else {
//             Node* temp = this->right;
//             while(temp->left != NULL){
//                 temp = temp->left;
//             }
//             this->value = temp->value;
//             this->right->remove(temp->value);
//         }
//     }
// }

void Node::print(){
    std::cout << this->value << std::endl;
    if(this->left != NULL){
        this->left->print();
    }
    if(this->right != NULL){
        this->right->print();
    }
}