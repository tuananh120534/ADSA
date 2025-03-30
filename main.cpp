#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;
};
//get maximum of two integers
int max(int a, int b); //get height // of the tree
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
} //get maximum // of two integers
int max(int a, int b) { return (a > b) ? a : b; }

Node *newNode(int key)
{
    Node *node = new Node();
    node->key = key;

    node->left = NULL;
    node->right = NULL;

    node->height = 1;
    return (node);
} //right-rotate subtree rooted with y
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}
// get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
Node *insert(Node *node, int key)
{
    if (node == NULL)
        return (newNode(key));
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys not allowed
        return node;
    //Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));
    //Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node); // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node); // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    } // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node *maxValueNode(Node *node) {
    Node *current = node;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

Node *deleteNode(Node *root, int key) {
    if (root == NULL)
        return root;

    // Standard BST delete operations
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                // No child case
                delete root;
                root = NULL;
            } else {
                // One child case
                *root = *temp; // Shallow copy
                delete temp;
            }

        } else {
            // Node with two children: Get the inorder successor
            Node *temp = maxValueNode(root->left);
        root->key = temp->key;
        root->left = deleteNode(root->left, temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = max(height(root->left), height(root->right)) + 1;

    // Check balance factor of this node to see if it became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preOrder(Node *root)
{
    if (root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
void printPostorder(Node *node)
{
    if (node == NULL)
        return;                  
    printPostorder(node->left);
    printPostorder(node->right);
    cout << node->key << " ";
}
void printInorder(Node *node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    cout << node->key << " ";
    printInorder(node->right);
}
int extractIntegerWords(string str)
{
    size_t i = 0;
    for (; i < str.length(); i++)
    {
        if (isdigit(str[i]))
            break;
    }
    str = str.substr(i, str.length() - i);
    int id = atoi(str.c_str());
    return id;
}

int main() {
    Node* root = NULL;
    string command;

    while (cin >> command) {
        if (command[0] == 'A') { 
            int num = stoi(command.substr(1));
            root = insert(root, num);

        } else if (command[0] == 'D') {
            int num = stoi(command.substr(1));
            root = deleteNode(root, num);

        } else if (command == "IN") {
            if (root != NULL) printInorder(root);
            else cout << "EMPTY";
            break;

        } else if (command == "PRE") {
            if (root != NULL) preOrder(root);
            else cout << "EMPTY";
            break;
            
        } else if (command == "POST") {
            if (root != NULL) printPostorder(root);
            else cout << "EMPTY";
            break;
        }
    }

    return 0;
}