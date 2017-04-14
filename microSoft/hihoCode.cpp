#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    public:
    void func(int N, int M, int K, vector<int>& leaves, vector<vector<int>>& nodes, vector<vector<int>>& distance) {
        vector<int> parents(N + 1, 0);
        vector<int> isLeaf(N + 1, false);
        for (int i = 0; i < leaves.size(); i++) isLeaf[leaves[i]] = true;
        int parent = 0, currLeave = nodes.size() - 1, index = 0;
        while (currLeave > 0) {
        	//找到倒数第二层的非叶子节点,此时parent为第一个非叶子节点 
            while (parent < nodes[currLeave - 1].size() && isLeaf[nodes[currLeave - 1][parent]]) parent++;
            
            while (index < nodes[currLeave].size()) {
            	//第一个叶子节点的父亲肯定是parent指向的节点，把父节点保存下来
                parents[nodes[currLeave][index]] = nodes[currLeave - 1][parent];
                
                for (int i = 0; i < distance.size(); i++) {
                    if (i == nodes[currLeave - 1][parent]) distance[i][i] = 0;
                    else {
                        distance[i][nodes[currLeave - 1][parent]] = distance[i][nodes[currLeave][index]] - 1;
                        distance[nodes[currLeave - 1][parent]][i] = distance[nodes[currLeave][index]][i] - 1;
                    }
                }
                if (index + 1 < nodes[currLeave].size() && distance[nodes[currLeave][index]][nodes[currLeave][index + 1]] > 2) {
                    parent++;
                    while (parent < nodes[currLeave - 1].size() && isLeaf[nodes[currLeave - 1][parent]]) parent++;
                }
                index++;
            }
            
            parent = 0;
            currLeave--;
            index = 0;
        }
        for (int i = 1; i < N; i++) {
            cout << parents[i] << ' ';
        }
        cout << parents[N] << endl;
    }
};

int main() {
    Solution* s = new Solution();
    int N, M, K, count;
    cin >> N >> M >> K;
    vector<vector<int>> nodes(M);
    for (int i = 0; i < M; i++) {
        cin >> count;
        nodes[i] = vector<int>(count);
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < nodes[i].size(); j++) {
            cin >> nodes[i][j];
        }
    }
    vector<int> leaves(K);
    for (int i = 0; i < K; i++) {
        cin >> leaves[i];
    }
    vector<vector<int>> distance(N + 1, vector<int>(N + 1, -1));
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            cin >> distance[leaves[i]][leaves[j]];
        }
    }
    s->func(N, M, K, leaves, nodes, distance);
    system("pause");
    return 0;
}
