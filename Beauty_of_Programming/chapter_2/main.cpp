#include <iostream>
#include <vector>
#include <assert.h>
#include <limits.h> 
using namespace std;
/*
任意给定一个正整数N，求一个最小的正整数M（M>1），
使得N*M的十进制表示形式里只含有0和1 
*/
class BigInt{
	public:
		vector<int> vec; //[0]=10^0=1;[0,1]=10^0+10^1=11;[0,2]=10^0+10^2=101
};
vector<int> getMinM(unsigned int N) {
	vector<int> remainder[N];
	remainder[1].push_back(0);//把1放进去
	int k = 1;
	int re;
	for(k=1,re=10%N;;k++,re=(re*10)%N) {
		if (remainder[re].size() == 0) {
			remainder[re].push_back(k);
		}
		for (int i = 0; i < N; i++) {
			vector<int> vTmp = remainder[i];
			bool flag = true;
			if (vTmp.size() > 0) {
				for (int z=0; z < vTmp.size(); z++) {
					if (vTmp[z] >= k) {
						flag = false;
					}
				}
			} else {
				flag = false;
			}
			if (flag) {
				int newRe = (i + re)%N;
				if (remainder[newRe].size() == 0) {
					remainder[newRe].push_back(k);
					for (int z=0; z < vTmp.size(); z++) {
						remainder[newRe].push_back(vTmp[z]);
					}
				}
			}
		}
		if (remainder[0].size() > 0) {
			return remainder[0];
		}
	}
}

/*
一个有N个整数元素的一维数组，求子数组（相邻的一段）之和的最大值。
思路：前i个元素和如果小于0，则对后面的相加没有帮助 
*/
int getMaxSubarray(vector<int> nums) {
	int len = nums.size();
	assert(len > 0);
	int ret = INT_MIN;
	int tmp = 0;
	for (int i = 0; i < len; i++) {
		tmp += nums[i];
		if (tmp > ret) {
			ret = tmp;
		}
		if (tmp < 0) {
			tmp = 0;
		}
	}
	return ret;
}

/*
有一个无序的，元素个数为2n的正整数数组，要求：
如何能把这个数组分割为元素个数为n的两个数组，并使两个子数组的和最接近  
*/
class Node{
	public:
		Node() {};
		Node(Node* n) {
			for (int i = 0; i < n->list.size(); i++) {
				this->list.push_back(n->list[i]);
			}
			this->sum = n->sum;
		};
		Node(int data) {
			this->list.push_back(data);
			this->sum = data;
		}
		void addValue(int target) {
			this->list.push_back(target);
			this->sum += target;
		}
		vector<int> list;
		int sum;
};
Node getMindiffSubarray(vector<int> nums) {
	int len = nums.size();
	unsigned int sum = 0;
	vector<Node> sumCnt[len];
	for (int i = 0; i < len; i++) {
		sum += nums[i];
		int target = nums[i];
		for (int z = i; z >= 0; z--) {
			vector<Node> curList = sumCnt[z];
			if (z == 0) {
				Node node(target);
				curList.push_back(node);
			} else {
				vector<Node> prenodeList = sumCnt[z - 1];
				for (int j = 0; j < prenodeList.size(); j++) {
					Node n = prenodeList[j];
					Node newNode((Node*)&n);
					newNode.addValue(target);
					curList.push_back(newNode);
				}
			}
			sumCnt[z] = curList;
		}
	}
	
	int in = (len >> 1) - 1;
	vector<Node> targetList = sumCnt[in];
	int halfSum = sum >> 1;
	int tmpDiff = INT_MAX;
	Node targetNode;
	for (int q = 0; q < targetList.size(); q++) {
		Node tmpNode = targetList[q];
		if (abs(halfSum - tmpNode.sum) < tmpDiff) {
			tmpDiff = abs(halfSum - tmpNode.sum);
			targetNode = tmpNode;
		}
	}
	return targetNode;
}

/*
用C/C++实现根据前序和中序遍历来重建二叉树 
*/
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
class Tree{
	public:
		Tnode* root;
		Tree() {
			this->root = NULL;
		}
		Tree(Tnode* r) {
			this->root = r;
		}
		virtual ~Tree() {
			this->clean(this->root);
		}
		
		void postOrderPrintTree() {
			this->postordervisit(this->root);
		}
	
		void rebuild(char* preStr, int pb, int pe, char* ordStr, int ob, int oe) {
			this->root = this->reBuildTree(preStr, pb, pe, ordStr, ob, oe);
		}
		
		int printNodeAtLevel(int level) {
			this->printNodeAtLevel(this->root, level);
		}
			
	private:
		void clean(Tnode* r) {
			if (r == NULL) {
				return;
			}
			if (r->left != NULL) {
				clean(r->left);
			}
			if (r->right != NULL) {
				clean(r->right);
			}
			delete r;
		}
		
		void postordervisit(Tnode* r) {
			if (r == NULL) {
				return;
			}
			if (r->left != NULL) {
				this->postordervisit(r->left);
			}
			if (r->right != NULL) {
				this->postordervisit(r->right);
			}
			cout<<r->data<<" ";
		}
		
		Tnode* reBuildTree(char* preStr, int pb, int pe, char* ordStr, int ob, int oe) {
			if (pb > pe || ob > oe) {
				return NULL;
			}
			char target = preStr[pb];
			Tnode* node = (Tnode*)new Tnode(target);
			//构建左子树 
			int lob;
			int len = 0;
			for (lob = ob; ordStr[lob] != target; lob++);
			if (lob > ob) {
				len = lob - ob;
				int lpb = pb;
				bool isOk = false;
				for (;;) {
					char ch = preStr[lpb];
					for (int z = ob; z < lob; z++) {
						if (ch == ordStr[z]) {
							isOk = true;
							break;
						}
					}
					if (isOk) {
						break;
					}
					++lpb;
				}
				node->left = reBuildTree(preStr, lpb, lpb+len-1, ordStr, ob, lob-1); 
			}
			
			//构建右子树
			if (lob < oe) {
				node->right = reBuildTree(preStr, pb+len+1, pe, ordStr, lob+1, oe);
			}
			return node;
		}
		
		int printNodeAtLevel(Tnode* root, int level) {
			if (root == NULL || level < 0) {
				return 0;
			}
			if (level == 0) {
				cout<<root->data<<" ";
				return 1;
			}
			return printNodeAtLevel(root->left, level - 1) + printNodeAtLevel(root->right, level - 1); 
		}
};
/*
char* preStr, int pb, int pe,先序字符序列，pb是开始index，pe是结束index 
char* ordStr, int ob, int oe，后序字符序列，ob是开发index，oe是结束index 
*/ 
int main(){
	char preStr[] = {'a','b','d','c','e','f'};
	char ordStr[] = {'d','b','a','e','c','f'};
	Tree tree;
	tree.rebuild(preStr, 0, 5, ordStr, 0, 5);
	tree.postOrderPrintTree();
	cout<<endl;
	int ret = tree.printNodeAtLevel(2);
	cout<<endl;
	cout<<ret<<endl;
//	int N[] = {1,3,5,2,17,10,18,30};
//	vector<int> vec(N, N+sizeof(N)/sizeof(int));
//	Node ret = getMindiffSubarray(vec);
//	for (int i = 0; i < ret.list.size(); i++) {
//		cout<<ret.list[i]<<endl;
//	} 
}
