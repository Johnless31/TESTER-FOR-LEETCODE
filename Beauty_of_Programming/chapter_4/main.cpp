#include <iostream>
#include <vector>
#include <stack>
#include <queue>
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
/*
��ȡһ��������ȣ�ֻ��һ���ڵ�����Ϊ1
*/
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

/*
�ж�һ�����Ƿ�Ϊ��ȫ��������
��ȫ������vec�м䲻�����NULL��
������ȫ�������м�����NULL
*/
bool isBTS(Tnode* root) {
	if (root == NULL) {
		return false;
	}
	vector<Tnode*> vec;
	vec.push_back(root);
	int i = 0;
	while(i < vec.size()) {
        Tnode* node = vec[i];
        if (node == NULL) {
            i++;
            continue;
        }
        vec.push_back(node->left);
        vec.push_back(node->right);
        i++;
	}

	int flag = 0;
	for(int z = 0; z < vec.size(); z++) {
        if (flag == 0 && vec[z] == NULL) {
            flag = 1;
        } else if (flag == 1 && vec[z] != NULL) {
            return false;
        }
	}
    return true;

}

void test() {
	Tnode* root = new Tnode('1');

	Tnode* left1 = new Tnode('2');
	Tnode* right1 = new Tnode('3');
	root->left = left1;
	root->right = right1;

	Tnode* left2 = new Tnode('4');
	Tnode* right2 = new Tnode('5');
	left1->left = left2;
	left1->right = right2;

	/*Tnode* right3 = new Tnode('6');
	left2->right = right3;*/

	cout<<isBTS(root)<<endl;
	freeTree(root);
}



/*
void printTreeByLevel(Tnode* root) {

}*/
int main(){
	test();
}
