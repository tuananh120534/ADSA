#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode *leftChild;
    TreeNode *rightChild;
    int nodeHeight;
};

int getMax(int a, int b);

int getHeight(TreeNode *node) {
    if (node == NULL)
        return 0;
    return node->nodeHeight;
}

int getMax(int a, int b) { return (a > b) ? a : b; }

TreeNode *createNode(int value) {
    TreeNode *newNode = new TreeNode();
    newNode->value = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->nodeHeight = 1;
    return newNode;
}

TreeNode *rotateRight(TreeNode *y) {
    TreeNode *x = y->leftChild;
    TreeNode *T2 = x->rightChild;

    x->rightChild = y;
    y->leftChild = T2;

    y->nodeHeight = getMax(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;
    x->nodeHeight = getMax(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;

    return x;
}

TreeNode *rotateLeft(TreeNode *x) {
    TreeNode *y = x->rightChild;
    TreeNode *T2 = y->leftChild;

    y->leftChild = x;
    x->rightChild = T2;

    x->nodeHeight = getMax(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;
    y->nodeHeight = getMax(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;

    return y;
}

int getBalance(TreeNode *node) {
    if (node == NULL)
        return 0;
    return getHeight(node->leftChild) - getHeight(node->rightChild);
}

TreeNode *insert(TreeNode *node, int value) {
    if (node == NULL)
        return createNode(value);

    if (value < node->value)
        node->leftChild = insert(node->leftChild, value);
    else if (value > node->value)
        node->rightChild = insert(node->rightChild, value);
    else
        return node;

    node->nodeHeight = 1 + getMax(getHeight(node->leftChild), getHeight(node->rightChild));
    int balance = getBalance(node);

    if (balance > 1 && value < node->leftChild->value)
        return rotateRight(node);

    if (balance < -1 && value > node->rightChild->value)
        return rotateLeft(node);

    if (balance > 1 && value > node->leftChild->value) {
        node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    }

    if (balance < -1 && value < node->rightChild->value) {
        node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    }

    return node;
}

TreeNode *getMaxNode(TreeNode *node) {
    TreeNode *current = node;
    while (current->rightChild != NULL) {
        current = current->rightChild;
    }
    return current;
}

TreeNode *deleteNode(TreeNode *root, int value) {
    if (root == NULL)
        return root;

    if (value < root->value)
        root->leftChild = deleteNode(root->leftChild, value);
    else if (value > root->value)
        root->rightChild = deleteNode(root->rightChild, value);
    else {
        if (root->leftChild == NULL || root->rightChild == NULL) {
            TreeNode *temp = root->leftChild ? root->leftChild : root->rightChild;
            if (temp == NULL) {
                delete root;
                root = NULL;
            } else {
                *root = *temp;
                delete temp;
            }
        } else {
            TreeNode *temp = getMaxNode(root->leftChild);
            root->value = temp->value;
            root->leftChild = deleteNode(root->leftChild, temp->value);
        }
    }

    if (root == NULL)
        return root;

    root->nodeHeight = getMax(getHeight(root->leftChild), getHeight(root->rightChild)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->leftChild) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->leftChild) < 0) {
        root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->rightChild) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->rightChild) > 0) {
        root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }

    return root;
}

void printPreorder(TreeNode *node) {
    if (node != NULL) {
        cout << node->value << " ";
        printPreorder(node->leftChild);
        printPreorder(node->rightChild);
    }
}

void printPostorder(TreeNode *node) {
    if (node == NULL)
        return;
    printPostorder(node->leftChild);
    printPostorder(node->rightChild);
    cout << node->value << " ";
}

void printInorder(TreeNode *node) {
    if (node == NULL)
        return;
    printInorder(node->leftChild);
    cout << node->value << " ";
    printInorder(node->rightChild);
}

int main() {
    TreeNode *root = NULL;
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
            if (root != NULL) printPreorder(root);
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
