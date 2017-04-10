#include <iostream>
#include <vector>
using namespace std;
/*
�������һ��������N����һ����С��������M��M>1����
ʹ��N*M��ʮ���Ʊ�ʾ��ʽ��ֻ����0��1 
*/
class BigInt{
	public:
		vector<int> vec; //[0]=10^0=1;[0,1]=10^0+10^1=11;[0,2]=10^0+10^2=101
};
vector<int> getMinM(unsigned int N) {
	vector<int> remainder[N];
	remainder[1].push_back(0);//��1�Ž�ȥ
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
int main(){
	int N = 3;
	vector<int> vec = getMinM(N);
	for (int i = 0; i < vec.size(); i++ )
	cout<<vec[i]<<endl;
}
