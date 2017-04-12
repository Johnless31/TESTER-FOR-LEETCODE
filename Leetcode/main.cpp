#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <limits.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	sort(candidates.begin(), candidates.end());
	size_t len = candidates.size();
	for (int i=0; i <len; i++) {
		vector<int> set;
		set.push_back(candidates[i]);
		do {
			
		} while()
	}
	 
	        
}*/
int searchInsert(vector<int>& nums, int target) {
	int start = 0;
	int end = nums.size();
	int m;
	if (end == 0 || target <= nums[0])
		return 0;
	else if (target > nums[end - 1])
		return end;
	else if (target == nums[end - 1])
		return end - 1;
	do{
		m = (start + end) >> 1;
		if (nums[m] == target) {
			return m;
		} else if(nums[m] > target) {
			end = m - 1;
		} else {
			start = m + 1;
		}
		
	} while (start <= end);
	return nums[m] > target ? m : (m + 1);
}
int maxSubArray(vector<int>& nums) {
	int len = nums.size();
	int p = 0;
	while (nums[p] <= 0) p++;
	if (p >= len) {
		int max = INT_MIN;
		for (int z=0; z < len; z++) {
			if (nums[z] > max)
				max = nums[z];
		}
		return max;
	}
	int ret = nums[p];
	while (p < len) {
		int i = p;
		int tmp = nums[i];
		if (tmp > ret)
			ret = tmp;
		i++;
		while(i < len) {
			tmp = tmp + nums[i];
			if (tmp > ret)
				ret = tmp;
			if (tmp <= 0) {
				break;
			}
			i++;
		}
		if (i < len)
			p = i;
		else
			p++;
		while (nums[p] <= 0) p++;
	}
	
	return ret;     
}
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	if (n == 0)
		return;
	if (m == 0) {
		for (int i = 0; i < n; i++)
			nums1[i] = nums2[i];
		return;
	}
	int i1 = m - 1;
	int i2 = n - 1;
	for (int z = m+n - 1; z >=0; z--) {
		if (nums1[i1] > nums2[i2] ){
			nums1[z] = nums1[i1];
			i1--;
		} else {
			nums1[z] = nums2[i2];
			i2--;
		}
		if (i2 < 0)
		return;
		if (i1 < 0) {
			for (int i = 0; i <= i2; i++)
				nums1[i] = nums2[i];
			return;
		}
	}
}

vector<vector<int> > generate(int numRows) {
	vector<vector<int> > ret;
	if (numRows <= 0)
		return ret;
	vector<int> f(1,1);
	ret.push_back(f);
	numRows--;
	for (int i = 0; i < numRows; i++) {
		vector<int> tmp = ret[i];
		int tmp_size = tmp.size();
		int len = i + 2;
		vector<int> v(len, 1);
		for (int z = 0; z < tmp_size - 1; z++) {
			v[z+1] = tmp[z] + tmp[z+1];
		}
		ret.push_back(v);
	}
	return ret;
	        
}

int findMaxConsecutiveOnes(vector<int>& nums) {
	int l = nums.size();
	int ret = 0;
	int tmp = 0;
	for (int i = 0; i < l; i++) {
		tmp = tmp * nums[i] + nums[i];
		ret = max(tmp, ret);	
	}
	return ret;
}

int search(vector<int>& nums, int target) {
	int ret = -1;
	int len = nums.size();
	if (len == 0)
		return ret;
	if (len == 1)
		return nums[0] == target ? 0 : -1;
	if (nums[len - 1] == target)
		return len - 1;
	int r = 0;
	for (;r < len - 1; r++) {
		if (nums[r] == target)
			return r;
		if (nums[r] > nums[r + 1])
			break;
	}
	
	int start, end;
	if (target > nums[len - 1]) {
		start = 0;
		end = r;
	} else {
		start = r + 1;
		end = len - 1;
	}
	while(start <= end) {
		int m = (start + end)>>1;
		if (nums[m] == target) {
			return m;
		} else if (nums[m] > target) {
			end = m - 1;
		} else {
			start = m + 1;
		}
	}
	return ret;      
}

//
vector<int> searchRange(vector<int>& nums, int target) {
	vector<int> ret(2, -1);
	int start = 0;
	int len = nums.size();
	int end = len - 1;
	if (end < 0)
		return ret;
	while(start <= end) {
		int m = (start + end) >> 1;
		if (nums[m] == target) {
			int l = m - 1;
			int h = m + 1;
			while(nums[l] == target && l >= 0) l--;
			while(nums[h] == target && h < len) h++;
			ret[0] = l + 1;
			ret[1] = h - 1;
			return ret;
		} else if (nums[m] > target) {
			end = m - 1;
		} else {
			start = m + 1;
		}
	}
	return ret;
}

class Test1{
	private:
		int h = 0;
		int w = 0;
	public:
		Test1(int a, int b) {
			this->h = a;
			this->w = b;
		}
		Test1(const Test1& c) {
			cout<<"hehe"<<endl;
			h = c.h;
			w = c.w;
		}
		
		int getH() {
			return this->h;
		}
		int getW() {
			return this->w;
		}
		void setH(int a) {
			this->h = a;
			return;
		}
		void setW(int a) {
			this->w = a;
			return;
		}
};

Test1 func(const Test1& rhs){
	return rhs;
}

void func2(Test1& rhs){
	rhs.setH(99);
}

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
vector<int> inorderTraversal(TreeNode* root) {
	vector<int> ret;
    if (root == NULL)
    return ret;
    map<TreeNode*,char> mymap;
	TreeNode* node;
	stack<TreeNode*> store;
	store.push(root);
	while(store.size() > 0) {
		node = store.top();
		if (node->left != NULL && mymap[node->left] != '0') {
			store.push(node->left);
		} else {
			TreeNode* self = store.top();
			store.pop();
			ret.push_back(self->val);
			mymap[self] = '0';
			if (self->right != NULL) {
				store.push(self->right);
			}
		}
	}
	return ret;
}
class Tree{
	public:
		TreeNode* root;
		Tree() {
			
		}
};

void IOTest()
{
	int N = 0;
	cin>>N;
	if (N > 0) {
		int arr[N] = {0};
		for (int i = 0; i < N; i++) {
			cin>>arr[i];
		}
		for (int i = 0; i < N; i++)
		cout<<arr[i]<<endl;
	}
	
}

int main(int argc, char** argv) {
	TreeNode* root = (TreeNode*)new TreeNode(0);
	TreeNode* left1 = (TreeNode*)new TreeNode(1);
	TreeNode* right1 = (TreeNode*)new TreeNode(2);
	TreeNode* left2 = (TreeNode*)new TreeNode(3);
	TreeNode* right2 = (TreeNode*)new TreeNode(4);
	root->left = left1;
	root->right = right1;
	left1->left = left2;
	left1->right = right2;
	inorderTraversal(TreeNode* root)
	return 0;
}
