#include <iostream>
#include <cmath>
#define COUNT 10
using namespace std;

struct Node{
    int data;
    int height;
    Node* left;
    Node* right;
    Node* parent;
};

int getheight(Node* tree){
    if(tree == NULL)
        return 0;
    else
        return 1 + max(getheight(tree->left), getheight(tree->right));
}

int Rank(Node* tree){
    if (tree == NULL)
        return 0;
    return tree->height;
}
Node* insert_(Node* tree, int x){
    if(tree == NULL){
        return new Node{x, 1, NULL, NULL, NULL};
    }
    if (tree->left != NULL || tree->right != NULL){
        if(x > tree->data){
            tree->right = insert_(tree->right, x);
            tree->right->parent = tree;
        }
        else if(x < tree->data){
            tree->left = insert_(tree->left, x);
            tree->left->parent = tree;
        }
        else
            return tree;
    }
    else{
        Node* temp = new Node{x, 1, NULL, NULL, tree};
        if(x > tree->data)
            tree->right = temp;
        else if(x < tree->data)
            tree->left = temp;
        else
            return tree;
    }
    tree->height = 1 + max(Rank(tree->left), Rank(tree->right));
    return tree;
}

void print2DUtil(Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->data<<"\n";
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(Node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}
int main(){
    Node* t = NULL;
    t = insert_(t, 10);
    t = insert_(t, 5);
    t = insert_(t, 15);
    t = insert_(t, 1);
    t = insert_(t, 7);
    t = insert_(t, 20);
    t = insert_(t, 12);
    t = insert_(t, 9);
    print2D(t);
    cout << t->height;
    return 0;
}
