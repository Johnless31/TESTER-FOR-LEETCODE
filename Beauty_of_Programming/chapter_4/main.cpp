#include <iostream>
#include <vector>
#include <assert.h>
#include <limits.h>
using namespace std;
class Tnode{
	public:
		Tnode * left;
		Tnode * right;
		char data;
		Tnode(char d) {
			this->data = d;
			this->left = NULL;
			this->right = NULL;
		}
};
int getTreeDepth(Tnode* root) {
	if (root == NULL) {
		return 0;
	}
	int ld = 1 + getTreeDepth(root->left);
	int rd = 1 + getTreeDepth(root->right);
	return ld > rd ? ld : rd; 
}
void freeTree(Tnode* root) {
	if (root == NULL) {
		return;
	}
	if (root->left != NULL) {
		freeTree(root->left);
	}
	if (root->right != NULL) {
		freeTree(root->right);
	}
	cout<<"delete "<<root->data<<endl;
	delete root;
}
int main(){
	Tnode* root = new Tnode('1');
	
	Tnode* left1 = new Tnode('2');
	Tnode* right1 = new Tnode('3');
	root->left = left1;
	root->right = right1;
	
	Tnode* left2 = new Tnode('4');
	Tnode* right2 = new Tnode('5');
	left1->left = left2;
	left1->right = right2;
	
	Tnode* right3 = new Tnode('6');
	left2->right = right3;
	
	cout<<getTreeDepth(root)<<endl;
	freeTree(root);
}
