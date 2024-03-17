#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

// data input max = 100001 so set the value = 100001
int arr[100001]; // file1, file2's maximum value is smaller than 1000. so i use integer
int SortedArr[100001];
int cnt[100000]; // 3자리수 정수가 최대이다.
int len = 0;
int maxvalue = 0;
// max 사용 못함 지원하지 않는 자료형이기 때문에

void CountingSort(int digit);
void RadixSort();

int main(void) {
    fastio;
    int i = 0;
    // open the file
    ifstream fin;
    fin.open("Q3_2.txt"); // ""안에 file 이름 넣기

    int num;
    // input the value
    while (1) {
        if (fin.eof())
            break;

        fin >> num;
        arr[len] = num;
        len++;
        maxvalue = max(maxvalue, num);
    }

    // close the file
    fin.close();

    RadixSort();

    for (int i = 0; i < len; i++)
        cout << SortedArr[i] << " ";

    return 0;
}

void CountingSort(int digit) {
    memset(cnt, 0, sizeof(cnt));
    // count
    for (int i = 0; i < len; i++)
        cnt[(arr[i] / digit) % 100000]++;

    // cumulate
    for (int i = 1; i < 100000; i++)
        cnt[i] += cnt[i - 1];

    // sorting
    for (int i = len - 1; i >= 0; i--) {
        SortedArr[cnt[(arr[i]/ digit) % 100000] - 1] = arr[i];
        cnt[(arr[i] / digit) % 100000]--;
    }
}

void RadixSort() {
    for (int i = 1; maxvalue / i > 0; i *= 100000) {
        CountingSort(i);
        for (int j = 0; j < len; j++) {
            arr[j] = SortedArr[j];
        }
    }
}