#include <iostream>

using namespace std;

#define COUNT 10
struct Node{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    bool color;
    // 1 -> Red | 0 -> Black
};

struct RedBlackTree{
    Node* Root;
    Node* insertHelp(Node* root, int key){
        if(root == NULL)
            return new Node{key, NULL, NULL, NULL, 1};
        else if(key > root->data){
            root->right = insertHelp(root->right, key);
            root->right->parent = root;
        }
        else{
            root->left = insertHelp(root->left, key);
            root->left->parent = root;
        }
        return root;
    }
    void Insert(int key){
        Root = insertHelp(Root, key);
    }
    RedBlackTree(){
        Root = NULL;
    }
};

string getColor(Node* root) {
	if (root != NULL && root->color)
		return "RED";
	return "BLACK";
}

// In - Print 2D ra console
void print2DUtil(Node* root, int space) {
	if (root == NULL)
		return;
	space += COUNT;

	print2DUtil(root->right, space);
	cout << endl;

	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->data << " (" << getColor(root) << ") " << "\n";

	print2DUtil(root->left, space);
}

void print2D(Node* root) {
	print2DUtil(root, 0);
}


int main(){
    RedBlackTree RBTree;
    RBTree.Insert(10);
    RBTree.Insert(5);
    RBTree.Insert(7);
    RBTree.Insert(12);
    RBTree.Insert(15);
    print2D(RBTree.Root);

}
