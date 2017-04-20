#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <assert.h>
#include <limits.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <stack>
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
获取一棵树的深度，只有一个节点的深度为1
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
判断一棵树是否为完全二叉树，
完全二叉树vec中间不会出现NULL，
而非完全二叉树中间会出现NULL
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


bool myfunction (map<string, vector<char> >::iterator i, map<string, vector<char> >::iterator j)
{
    return (i->second.size() < j->second.size());
}
string trim(string s) {
    if (s.size() <= 0) {
        return s;
    }
    int b = 0;
    int e = s.size() - 1;
    while(s[b] == ' ') b++;
    while(s[e] == ' ') e--;
    if (b <= e) {
        return s.substr(b, e+1);
    } else {
        return "";
    }
}
void diaryHandler() {
    while(1) {
        string diaryb = "diary";
        string diarye = "/diary";
        string colorb = "color";
        string colore = "/color";
        string ss = "";
        string op;
        string content;
        vector<char> opVec;
        string colorType="";
        string currType = "";
        int s;
        int status = 0; //0 接收指令；1结束接收并处理指令
        cin >> s;
        if (s > 0 && s <=10) {
            map<string, vector<char> > textMap[s];
            string text[s];
            for (int i = 0; i < s; i++) {
                cin>>text[i];
            }
            for (int i = 0; i < s; i++) {
                stack<string> colorSta;
                colorSta.push("black");
                string diary = trim(text[i]);
                for (int j = 0; j < diary.size(); j++) {
                    char ch = diary[j];
                    if (ch == '<') {
                        status = 0; //接收指令
                        content = ss;
                        ss = "";
                    } else if (ch == '>') {
                        status = 1; //处理指令
                        op = ss;
                        ss = "";
                    }
                    if (ch != '<' && ch != '>') {
                        ss.push_back(ch);
                    }
                    if (status == 0) {
                        if (content.size() > 0) {
                            for(int c = 0; c < content.size(); c++) {
                                if (content[c] != ' ') {
                                    opVec.push_back(content[c]);
                                }
                            }
                            //cout<<"content="<<content<<endl;
                            content = "";
                        }
                    } else if (status == 1) {
                        if (op.size() > 0) {
                            if (op.find("color=") != string::npos) {
                                colorType = op.substr(6, op.size());
                                op = op.substr(0, 5);
                            }
                            if (op == diaryb) {
                                if (!colorSta.empty()) {
                                    currType = colorSta.top();
                                    colorSta.pop();
                                    opVec = textMap[i][currType];
                                }
                            } else if (op == diarye) {
                                textMap[i][currType] = opVec;
                            } else if (op == colorb) {
                                textMap[i][currType] = opVec; //保存上一次链表
                                colorSta.push(currType);
                                currType = colorType;
                                opVec = textMap[i][currType];
                            } else if (op == colore) {
                                textMap[i][currType] = opVec;
                                if (!colorSta.empty()) {
                                    currType = colorSta.top();
                                    colorSta.pop();
                                    opVec = textMap[i][currType];
                                }

                            }
                            op = "";
                        }
                    }
                }
            }
            for(int m = 0; m < s; m++) {
                if (textMap[m].size() > 0) {
                    vector<map<string, vector<char> >::iterator > toSort;
                    map<string, vector<char> >::iterator it=textMap[m].begin();
                    for (;it != textMap[m].end(); ++it) {
                        toSort.push_back(it);
                    }
                    sort(toSort.begin(), toSort.end(), myfunction);
                    for (int t = 0; t < toSort.size(); t++) {
                        cout<<toSort[t]->first<<" "<<toSort[t]->second.size()<<endl;
                    }
                }
            }

        }
    }
}

/*
 归并排序
*/
class MergeSort {
public:
    mergeSort(int arr[], int b, int e){
        if (e > b) {
            int m = b + (e - b)/2;
            mergeSort(arr, b, m);
            mergeSort(arr, m + 1, e);
            this->msort(arr, b, m, e);
        }
    }
private:
    void msort(int arr[], int b, int m, int e) {
        int temp[e - b + 1];
        int p = 0;
        int i = b;
        int j = m + 1;
        while(i <= m && j <= e) {
            if (arr[i] < arr[j]) {
                temp[p] = arr[i];
                i++;
            } else {
                temp[p] = arr[j];
                j++;
            }
            p++;
        }
        while(i <= m) {
            temp[p] = arr[i];
            i++;
            p++;
        }
        while(j <= e) {
            temp[p] = arr[j];
            j++;
            p++;
        }
        for (int z = 0; z < (e - b + 1); z++) {
            arr[z+b] = temp[z];
        }
    }
};

class HeapSort{
public:
    heapSort(int arr[], int n) {
        this->createHeap(arr, n);
        int e = n - 1;
        while(e > 0) {

        }
    }

private:
    void createHeap(int arr[], int n) {
        for (int i = n/2-1; i <= 0; i--) {
            this->fixUp(arr, n, i);
        }
    }
    //最大堆调整
    void fixUp(int arr[], int n, int i) {
        if (i > (n - 1)) {
          return;
        }
        while((i-1)/2 >= 0) {
            int p = (i-1)/2;
            if (arr[p] < arr[i]) {
                arr[i] = arr[i] + arr[p];
                arr[p] = arr[i] - arr[p];
                arr[i] = arr[i] - arr[p];
            }
            i = p;
        }
    }
};

int main(){
    MergeSort ms;
    int arr[] = {5,3,1,6,7,9,34,78,11,22};
    int len = sizeof(arr)/sizeof(int);
    ms.mergeSort(arr, 0, len - 1);
    for (int a = 0; a < len; a++)
    cout<<arr[a]<<endl;
    return 0;
}
