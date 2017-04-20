#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
using namespace std;
/*62进制相加，0-9a-zA-Z共62个字符代表0-61请设计一个函数可以对大数进行相加*/
char itoc(int i) {
    if (0 <= i && i <= 9) {
        return '0' + i;
    } else if (10 <= i && i <= 35) {
        return 'a' + (i - 10);
    } else if (36 <= i && i <= 61) {
        return 'A' + (i - 36);
    } else {
        return -1;
    }
}
int ctoi(char x) {
    if ('0' <= x && x<= '9') {
        return x - '0';
    } else if ('a' <= x && x<= 'z') {
        return (x - 'a') + 10;
    } else if ('A' <= x && x<= 'Z') {
        return (x - 'A') + 36;
    } else {
        return -1;
    }
}
int AddBigNum(const char* a, const char* b, char* result, int len) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int j = len_b -1;
    int i = len_a - 1;
    int max_len = max(len_a, len_b);
    if (len < max_len)
        return -1;
    int over = 0;
    result[len-1] = '\0';
    int r = len - 2;
    while(j >= 0 && i >= 0) {
        int tmp = ctoi(a[i]) + ctoi(b[j]);
        if (over > 0) {
            tmp = tmp + 1;
            over = 0;
        }
        if (tmp >= 62) {
            over = 1;
        }
        int bit = tmp%62;
        char relBit = itoc(bit);
        result[r--] = relBit;
        i--;
        j--;
    }
    if (r <= 0 && over == 1) {
            return -1;
    }
    if (r <= 0 && over == 1) {
            return -1;
    }
    while(j >= 0) {
        char c;
        if (over > 0) {
            int t = ctoi(b[j]) + 1;
            if (t >= 62) {
                over = 1;
            } else {
                over = 0;
            }
            c = ctoi(t%62);
        } else {
            c = b[j];
        }
        j--;
        if (r == 0 && over == 1) {
            return -1;
        }
        result[r--] = c;
    }
    while(i >= 0) {
        char c;
        if (over > 0) {
            int t = ctoi(a[i]) + 1;
            if (t >= 62) {
                over = 1;
            } else {
                over = 0;
            }
            c = ctoi(t%62);
        } else {
            c = a[i];
        }
        i--;
        if (r == 0 && over == 1) {
            return -1;
        }
        result[r--] = c;
    }

    return 0;
}

/*字符串压缩,压缩比率比较低*/
string compressStr(string s) {
    int len = s.size();
    if (len <= 2) return s;
    stringstream ss;
    string ret = "";
    int cnt = 0;
    char ch = s[0];
    for(int i = 0; i < len; i++) {
        if (s[i] == ch) {
            cnt++;
        } else {
            ss<<(cnt - 1);
            ret = ret + ch + ss.str();
            ss.str("");
            cnt = 1;
            ch = s[i];
        }
    }
    if (ret.size() < len) {
        return ret;
    } else {
        return s;
    }
}
/*字符串压缩,压缩比率比较低*/
string compressStr2(string s) {
    int len = s.size();
    if (len <= 2) return s;
    stringstream ss;
    string ret = "";
    int cnt = 0;
    char ch = s[0];
    for(int i = 0; i < len; i++) {
        if (s[i] == ch) {
            cnt++;
        } else {
            if (cnt >= 3) {
                ss<<(cnt - 1);
                ret = ret + ch + ss.str();
            } else {
                for (int z = 0; z < cnt; z++) {
                    ret = ret + ch;
                }
            }
            ss.str("");
            cnt = 1;
            ch = s[i];

        }
    }
    if (ret.size() < len) {
        return ret;
    } else {
        return s;
    }
}
char* testMalloc() {
    char* result = (char *)new char[3];
    result[2] = '\0';
    result[1] = 'b';
    result[0] = 'a';
    return result;
}

/*
    找出第K大的数，第一大就是最大
*/
int parse(int arr[], int b, int e) {
    int base = arr[b];
    int p = b;
    for (int i = b + 1; i <= e; i++) {

        if (arr[i] < base) {
            p++;
            arr[i] = arr[i] + arr[p];
            arr[p] = arr[i] - arr[p];
            arr[i] = arr[i] - arr[p];
        }
    }
    arr[b] = arr[p];
    arr[p] = base;
    return p;
}
int topk(int arr[], int b, int e, int k) {
    if (k <= 0 || b > e) return INT_MIN;
    int m = parse(arr, b, e);
    if (e - m + 1 == k) {
        return arr[m];
    } else if (e - m + 1 == k) {
        topk(arr, b, m - 1, k - (e - m + 1));
    } else {
        topk(arr, m+1, e, k);
    }
}

class Tnode {
public:
    Tnode* left;
    Tnode* right;
    char val;
};
class Tree{
public:
    Tnode* recreateTree(char fro[], int b, int e, char mid[], int mb, int me){
        if (b == -1 || e == -1 || mb == -1 || me == -1 || e < b || me < mb) {
            return NULL;
        }
        Tnode* node = (Tnode*)new Tnode();
        node->val = fro[b];
        cout<<"fro[b]="<<fro[b]<<endl;
        int lb, le, lmb, lme;
        this->findMidLeft(mid, mb, me, fro[b], lmb, lme);
        this->findFroLeft(fro, b, e, lb, le, lmb, lme);
        int rb, re, rmb, rme;
        this->findMidRight(mid, mb, me, fro[b], rmb, rme);
        this->findFroRight(fro, b, e, rb, re, rmb, rme);
        node->left = recreateTree(fro, lb, le, mid, lmb, lme);
        node->right = recreateTree(fro, rb, re, mid, rmb, rme);
        return node;
    }

    void afOrderPrint(Tnode* node) {
        if (node == NULL) return;
        if (node->left != NULL) {
            afOrderPrint(node->left);
        }
        if (node->right != NULL) {
            afOrderPrint(node->right);
        }
        cout<<node->val<<" ";
    }
private:
    void findMidLeft(char mid[], int b, int e, char target, int& i, int& j) {
        if (e < b) {
            i = -1;
            j = -1;
            return;
        }
        int z = b;
        while(mid[z] != target) z++;
        if (z == b) {
            i = -1;
            j = -1;
            return;
        }
        i = b;
        j = z - 1;
        return;
    }
    void findFroLeft(char fro[], int b, int e, int& k, int& z, int i, int j) {
        if (e < b || i == -1 || j == -1) {
            k = -1;
            z = -1;
            return;
        }
        int len = j - i + 1;
        k = b + 1;
        z = k + len - 1;
        return;
    }

    void findMidRight(char mid[], int b, int e, char target, int& i, int& j) {
        if (e < b) {
            i = -1;
            j = -1;
            return;
        }
        int z = e;
        while(mid[z] != target) z--;
        if (z == e) {
            i = -1;
            j = -1;
            return;
        }
        i = z + 1;
        j = e;
        return;
    }
    void findFroRight(char fro[], int b, int e, int& k, int& z, int i, int j){
        if (i == -1 || j == -1 || e < b) {
            k = -1;
            z = -1;
            return;
        }
        z = e;
        k = z - (j - i);
        return;
    }
};
int main(){

    /*ifstream fin("data.txt");
    stringstream ss("sjdfhjkaa/fkwejfkwnsdfkjkaa/wehaa");
    string s;
    while(getline(ss,s,'/'))
        cout<<s<<endl;
    fin.clear();
    fin.close();*/
    char fro[] = {'a', 'b', 'd', 'c', 'e', 'f'};
    char mid[] = {'d', 'b', 'a', 'e', 'c', 'f'};
    Tree t;
    Tnode* node = t.recreateTree(fro, 0, 5, mid, 0, 5);
    t.afOrderPrint(node);
}
