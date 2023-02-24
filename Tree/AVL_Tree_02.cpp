#include <iostream>
#include <cmath>
#define COUNT 10

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
	int height;
};

int getHeight(Node* root) {
	if (root == NULL)
		return 0;
	//return 1 + max(getHeight(root->left), getHeight(root->right));
	return root->height;
}


Node* rightRotate(Node* root){
	Node* x = root->left;

	// Bắt đầu quay phải
	root->left = x->right;
	x->right = root;

	// Thiết lập chiều cao
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	x->height = 1 + max(getHeight(x->left), getHeight(x->right));

	// Return x - trả về root mới
	return x;
}

Node* leftRotate(Node* root) {
	Node* y = root->right;

	// Bắt đầu quay trái
	root->right = y->left;
	y->left = root;

	// Thiết lập chiều cao
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	y->height = 1 + max(getHeight(y->left), getHeight(y->right));

	// Return y - trả về root mới
	return y;
}
// Insertion - AVL Tree
Node* Insert(Node* root, int value) {
	// 1. Insert
	if (root == NULL)
		return new Node{ value, NULL, NULL, 1 }; // Trả về Node có height = 1
	if (value > root->data)
		root->right = Insert(root->right, value);
	else if (value < root->data)
		root->left = Insert(root->left, value);
	else
		return root; // Neu bang thi khong them

	// 2. Set height
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));

	// 3. Rotate
	int valBalance = getHeight(root->left) - getHeight(root->right);
	
	// Kiểm tra 4 TH xảy ra:
	// 4.1. Left left
	if (valBalance > 1 && value < root->left->data)
		return rightRotate(root);

	// 4.2. Right Right
	if (valBalance < -1 && value > root->right->data)
		return leftRotate(root);

	// 4.3. Left Right
	if (valBalance > 1 && value > root->left->data) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// 4.4. Right Left
	if (valBalance < -1 && value < root->right->data) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

// Giá trị cân bằng - Value Balance
int valueBalance(Node* root) {
	if (root == NULL)
		return 0;
	return getHeight(root->left) - getHeight(root->right);
}

Node* maxValueNode(Node* root)
{
	Node* current = root;

	// Tìm kiếm Node có giá trị lớn nhất
	while (current->right != NULL)
		current = current->right;

	return current;
}

// Deletion - AVL Tree
Node* deleteNode(Node* root, int key) {
	// 1. XÓA NODE - DELETE
	if (root == NULL)
		return root;

	if (key > root->data)
		root->right = deleteNode(root->right, key);
	else if (key < root->data)
		root->left = deleteNode(root->left, key);

	// Nếu key có giá trị bằng với root->data 
	// Thì đây chính là Node cần xóa
	else {
		// Trường hợp 0 con hoặc 1 con
		if (root->left == NULL || root->right == NULL) {
			// Sử dụng Node temp để kiểm tra
			Node* temp = root->left;
			if (root->right != NULL)
				temp = root->right;

			// TH: 0 con - No child case
			if (temp == NULL) {
				temp = root;
				root = NULL;
				delete temp;
			}
			// TH: 1 con - One child case
			else {
				// Gán tất cả các giá trị (bao gồm left, right, height) của temp vào root
				*root = *temp;
				delete temp;
			}
		}
		// Trường hợp 2 con - Two child case
		else {
			// Tìm Node lớn nhất bên trái (nhỏ nhất bên phải)
			// successor - biggest in the left subtree
			Node* temp = maxValueNode(root->left);

			// Đưa data của temp vào root
			root->data = temp->data;

			// Xóa temp như 2 TH trên - Delete the inorder successor
			root->right = deleteNode(root->right, temp->data);
		}
	}

	// Nếu không còn gì thì trả về luôn !!
	if (root == NULL)
		return root;

	// 2. CẬP NHẬT CHIỀU CAO - UPDATE HEIGHT OF THE CURRENT NODE
	root->height = 1 + max(getHeight (root->left), getHeight (root->right));

	// 3. CÂN BẰNG CÂY - GET THE BALANCE FACTOR
	int valBalance = valueBalance(root);

	// Kiểm tra 4 TH xảy ra - There are 4 cases

	// Case 1: Left left - Trái trái
	if (valBalance > 1 && valueBalance(root->left) >= 0)
		return rightRotate(root);

	// Case 2: Right right - Phải phải
	if (valBalance < -1 && valueBalance(root->right) <= 0)
		return leftRotate(root);

	// Case 3: Left right - Trái phải
	if (valBalance > 1 && valueBalance(root->left) < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Case 4: Right left - Phải trái
	if (valBalance < -1 && valueBalance(root->right) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}
// In - Print 2D ra console
void print2DUtil(Node* root, int space){
	if (root == NULL)
		return;
	space += COUNT;

	print2DUtil(root->right, space);
	cout << endl;

	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->data << " (" << root->height << ") " << "\n";

	print2DUtil(root->left, space);
}

void print2D(Node* root){
	print2DUtil(root, 0);
}

int main() {
	Node* tree = NULL;
	tree = Insert(tree, 10);
	tree = Insert(tree, 5);
	tree = Insert(tree, 15);
	tree = Insert(tree, 3);
	tree = Insert(tree, 12);
	tree = Insert(tree, 17);
	tree = Insert(tree, 11);
	print2D(tree);
	cout << "\n ------------Delete 3----------- \n";
	tree = deleteNode(tree, 3);
	print2D(tree);
}