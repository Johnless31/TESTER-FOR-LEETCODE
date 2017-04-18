#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

/*
将一个英文句子的单词反转
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
*/
string reverseWords(string s) {
    int i = 0, j = 0, k = 0;
    int len = s.size();
    if (len == 0) {
        return s;
    }
    while(k < len) {
        if (s[k] == ' ') {
            j = k - 1;
            while(i < j) {
                s[i] = s[i] + s[j];
                s[j] = s[i] - s[j];
                s[i] = s[i] - s[j];
                i++;
                j--;
            }
            i = k + 1;
            j = i;
        }
        k++;
    }
    j = k - 1;
    while(i < j) {
        s[i] = s[i] + s[j];
        s[j] = s[i] - s[j];
        s[i] = s[i] - s[j];
        i++;
        j--;
    }
    return s;
}

/*
Given a positive 32-bit integer n, you need to find the smallest 32-bit integer
which has exactly the same digits existing in the integer n and is greater in value than n.
If no such positive 32-bit integer exists, you need to return -1

Input: 12
Output: 21

Input: 21
Output: -1
*/
class Solution{
public:
    int getMinGreaterN(vector<char>nums, int b, int e, int target) {
        if (b > e) {
            return -1;
        }
        while(b < e -1) {
            int m = b + ((e - b)>>1);
            if (nums[m] > target) {
                e = m;
            } else {
                b = m + 1;
            }
        }
        if (nums[b] > target) {
            return b;
        } else if (nums[e] > target) {
            return e;
        } else {
            return -1;
        }
    }

    int nextGreaterElement(int n) {
        if (n <= 0) {
            return -1;
        }
        stringstream ss;
        ss<<n;
        string intstr;
        ss>>intstr;
        int i = intstr.size() - 1;
        if (i == 0) {
            return -1;
        }
        vector<char> cvec;
        while((i - 1) >= 0 && intstr[i - 1] >= intstr[i]) {
            cvec.push_back(intstr[i]);
            i--;
        }
        cvec.push_back(intstr[i]);
        if (i <= 0) {
            return -1;
        }
        int j = i - 1;

        //std::reverse(cvec.begin(), cvec.end());
        int index = this->getMinGreaterN(cvec, 0, cvec.size() - 1, intstr[j]);
        if (index == -1){
            return -1;
        }
        char tmp = intstr[j];
        intstr[j] = cvec[index];
        cvec[index] = tmp;
        for (int z = i; z < intstr.size(); z++) {
            intstr[z] = cvec[z - i];
        }
        int ret = parseInt(intstr);
        return ret;
    }

    int parseInt(string str) {
        stringstream ss(str);
        int ret;
        ss>>ret;
        ss.clear();
        ss<<ret;
        string cp = ss.str();
        if (cp == str) {
            return ret;
        } else {
            return -1;
        }
    }

};


/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
*/
class Solution71 {
public:
    string simplifyPath(string path) {

    }
};
/*
    实现string的trim
*/
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
/*
    实现atoi
*/
int myAtoI(string str) {
    long result = 0;
    int indicator = 1;
    if (str.size() == 0)
        return 0;
    int i = str.find_first_not_of(' ');
    if(str[i] == '-' || str[i] == '+')
        indicator = (str[i++] == '-')? -1 : 1;
    while('0'<= str[i] && str[i] <= '9')
    {
        result = result*10 + (str[i++]-'0');
        if(result*indicator >= INT_MAX) return INT_MAX;
        if(result*indicator <= INT_MIN) return INT_MIN;
    }
    return result*indicator;
}

int main(int argc, char** argv) {
    string s = "+9";
    cout<<myAtoI(s)<<endl;
}
