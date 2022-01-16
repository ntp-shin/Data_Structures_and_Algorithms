#include <iostream>
#include <cmath>

using namespace std;
#define COUNT 10

struct Node {
	int data;
	Node* left;
	Node* right;
	Node* parent;
	bool color;
	//1 -> Red   | 0 -> Black
};

Node* rotateRight(Node* root) {
    Node* x = root->left;
    Node* y = x->right;
    x->right = root;
    root->left = y;
    root->parent = x;
    if(y!=NULL)
        y->parent = root;
    return x;
}

Node* rotateLeft(Node* root) {
        Node* x = root->right;
        Node* y = x->left;
        x->left = root;
        root->right = y;
        root->parent = x; // parent resetting is also important.
        if(y!=NULL)
            y->parent = root;
        return x;
}

struct RedBlackTree {
	Node* Root;
	bool ll = false;
	bool rr = false;
	bool lr = false;
	bool rl = false;
	RedBlackTree() {
		Root = NULL;
	}
	Node* insertHelp(Node* root, int key) {
		// f đúng khi có xung đột RED RED
		bool f = false;

		if (root == NULL) {
			return new Node{ key, NULL, NULL, NULL, 1 }; // RED Node
		}
		else if (key < root->data) {
			root->left = insertHelp(root->left, key);
			root->left->parent = root;
			if (Root != root) {
				if (root->color == root->left->color == 1)
					f = true;
			}
		}
		else {
			root->right = insertHelp(root->right, key);
			root->right->parent = root;
			if (Root != root) {
				if (root->color == root->right->color == 1)
					f = true;
			}
		}

		// Xử lý 4 TH lệch
		// Case 1 : Left left - Trái trái
		if (rr) {
			root = rotateRight(root);
			root->color = 0;
			root->right->color = 1;
			rr = false;
		}
		// Case 2 : Right right - Phải phải
		else if (ll) {
			root = rotateLeft(root);
			root->color = 0;
			root->left->color = 1;
			ll = false;
		}
		// Case 3 : Left right - Phải trái
		else if (lr) {
			root->left = rotateLeft(root->left);
			root->left->parent = root;

			root = rotateRight(root);
			root->color = 0;
			root->right->color = 1;
			lr = false;
		}
		// Case 4 : Right left - Phải trái
		else if (rl) {
			root->right = rotateRight(root->right);
			root->right->parent = root;

			root = rotateLeft(root);
			root->color = 0;
			root->left->color = 1;
			rl = false;
		}

		// Xử lí xung đột đỏ - RED RED
		if (f) {
			if (root->parent->right == root) {
				if (root->parent->left == NULL || root->parent->left->color == 0) {
					if (root->left != NULL && root->left->color == 1)
						rl = true;
					if (root->right != NULL && root->right->color == 1)
						ll = true;
				}
				else {
					root->color = root->parent->left->color = 0;
					if (root != Root)
						root->parent->color = 1;
				}
			}
			else if(root->parent->left == root) {
				if (root->parent->right == NULL || root->parent->right->color == 0) {
					if (root->left != NULL && root->left->color == 1)
						rr = true;
					if (root->right != NULL && root->right->color == 1)
						lr = true;
				}
				else {
					root->color = root->parent->right->color = 0;
					if (root != Root)
						root->parent->color = 1;
				}
			}
			f = false;
		}
		return root;
	}

	void Insert(int key) {
		if (Root == NULL) {
			Root = new Node{ key, NULL, NULL, NULL, 0 };
		}
		else {
			Root = insertHelp(Root, key);
			if (Root->color == 1)
				Root->color = 0;
		}
	}
};

string getColor(Node* root) {
	if (root->color == 1)
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


int main() {
	RedBlackTree RBTree;
	RBTree.Insert(1);
	RBTree.Insert(4);
	RBTree.Insert(6);
	RBTree.Insert(3);
	RBTree.Insert(5);
	RBTree.Insert(7);
	RBTree.Insert(8);
	RBTree.Insert(9);
	RBTree.Insert(2);

	print2D(RBTree.Root);
	return 0;
}
