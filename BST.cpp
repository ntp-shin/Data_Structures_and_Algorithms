#include <iostream>
#define COUNT 10
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};
bool TwoChild(Node* t){
    if(t->left && t->right != NULL)
        return true;
    return false;
}
bool NoChild(Node* t){
    if(t->left && t->right == NULL)
        return true;
    return false;
}
Node* insert(Node* t, int x){
    if(t == NULL){
        Node* temp = new Node{x, NULL, NULL};
        return temp;
    }
    else{
        if(x > t->data)
            t->right = insert(t->right, x);
        else if(x < t->data)
            t->left = insert(t->left, x);
        else
            return t;
    }
    return t;
}
Node* Search(Node* t, int x){
    Node* cur = t;
    while (cur->data != x || cur != NULL){
        if(x > cur->data)
            cur = cur->right;
        else if(x < cur->data)
            cur = cur->left;
    }
    return cur;
}
Node* MaxLeft(Node* t){
    Node* cur = t->left;
    if(cur == NULL){
        return t;
    }
    while(cur != NULL && cur->right != NULL){
        cur = cur->right;
    }
    return cur;
}

Node* Delete(Node* t, int x){
    if(t == NULL)
        return t;

    if(t->data == x){
        if(TwoChild(t)){
            Node* temp = MaxLeft(t);
            t->data = temp->data;
            t->left = Delete(t->left, temp->data);
            return t;
        }
        else if(NoChild(t))
        {
            delete t;
        }
        else if(t->left != NULL){
            Node* temp = t->left;
            delete t;
            return temp;
        }
        else {
            Node* temp = t->right;
            delete t;  
            return temp;
        }
    }
    else if(t->data < x){
        t->right = Delete(t->right, x);
    }
    else if(t->data > x)
        t->left = Delete(t->left, x);
    return t;
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
    t = insert(t, 10);
    t = insert(t, 5);
    t = insert(t, 15);
    t = insert(t, 1);
    t = insert(t, 7);
    t = insert(t, 20);
    t = insert(t, 12);
    t = insert(t, 9);
    cout << t->data << " -> " << t->left->data << " --> " << t->right->data << endl;
    cout << t->left->data << " -> " << t->left->left->data << " --> " << t->left->right->data << endl;
    cout << t->right->data << " -> " << t->right->left->data << " --> " << t->right->right->data << endl;
    cout << MaxLeft(t)->data << endl;
    print2D(t);
    t = Delete(t, 10);
    cout << t->data << " -> " << t->left->data << " --> " << t->right->data << endl;
    cout << t->left->data << " -> " << t->left->left->data << " --> " << t->left->right->data << endl;
    cout << t->right->data << " -> " << t->right->left->data << " --> " << t->right->right->data << endl;
    if(MaxLeft(t) != NULL)
        cout << MaxLeft(t)->data << endl;
    print2D(t);

    return 0;
}