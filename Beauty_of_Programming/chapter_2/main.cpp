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

int main(){
	int N[] = {1,3,5,2,17,10,18,30};
	vector<int> vec(N, N+sizeof(N)/sizeof(int));
	Node ret = getMindiffSubarray(vec);
	for (int i = 0; i < ret.list.size(); i++) {
		cout<<ret.list[i]<<endl;
	} 
}
