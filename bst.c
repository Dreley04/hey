/*Andrew Otieno SCT221-0284/2022
Victor Nzwili SCT221-0236/2022
Thomas Mwera SCT221-0285/2022*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

Node* insert(Node* node, int data) {
    if (node == NULL) return newNode(data);
    if (data < node->data) node->left  = insert(node->left, data);
    else if (data > node->data) node->right = insert(node->right, data);
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) current = current->left;
    return current;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) return root;
    if (data < root->data) root->left = deleteNode(root->left, data);
    else if(data > root->data) root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int height(Node* node) {
    if (node==NULL) return 0;
    else {
        int lheight = height(node->left);
        int rheight = height(node->right);
        if (lheight > rheight) return(lheight+1);
        else return(rheight+1);
    }
}

void printGivenLevel(Node* root, int level) {
    if (root == NULL) return;
    if (level == 1) printf("%d ", root->data);
    else if (level > 1) {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}

void printLevelOrder(Node* root) {
    int h = height(root);
    int i;
    for (i=1; i<=h; i++) printGivenLevel(root, i);
}

int main() {
    Node *root = NULL;
    root = insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 10);
    insert(root, 25);
    insert(root, 35);
    insert(root, 45);
    insert(root, 5);
    insert(root, 15);

    printf("Height of tree is %d\n", height(root));

    printf("Level Order traversal of binary tree is \n");
    printLevelOrder(root);

    printf("\nDelete 20\n");
    root = deleteNode(root, 20);

    printf("Level Order traversal of binary tree is \n");
    printLevelOrder(root);

    return 0;
}
