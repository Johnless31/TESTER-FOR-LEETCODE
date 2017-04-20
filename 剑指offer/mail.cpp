#include <iostream>
#include <limits>
using namespace std;
class rotateArr{
public:
    int getMinInRoteArr(int arr[], int n) {
        if (arr == NULL || n <= 0) return INT_MAX;
        int i = 0;
        int j = n - 1;
        int ret = i;
        while(arr[i] >= arr[j]) {
            if (j - i == 1) {
                ret = j;
                break;
            }
            int m = i + ((j - i)>>1);
            if (arr[i] == arr[j] && arr[m] == arr[i]) {
                return getMinByAll(arr, n);
            }
            if (arr[m] >= arr[i]) {
                i = m;
            } else if (arr[m] <= arr[j]) {
                j = m;
            }
        }
        return arr[ret];
    }
    int getMinByAll(int arr[], int n) {
        int ret = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (arr[i] < ret) {
                ret = arr[i];
            }
        }
    }
};


int main(int argc, char* args[]) {
    int arr[] = {5,7,7,7,9,5,6};
    rotateArr r;
    cout<<r.getMinInRoteArr(arr, sizeof(arr)/sizeof(int));
}
