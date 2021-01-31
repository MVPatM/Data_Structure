/*
	array에서 index의 값이나 배열에 저장되어 있는 값을 하나만 알면 된다.
	변수를 2개로 설정을 하여서 2개 모두 저장할 필요가 없다.
	그리고 index를 저장하는 것이 유용한 경우가 많다.
*/

#include <iostream>

using namespace std;

// parent's priority is lower than children's
class MinHeap {
private:
	int* arr;
	int length;
public:
	MinHeap() :length(0) { arr = new int[100]; }
	void Insertion(int n);
	void MinDeletion_ver1();
	void MinDeletion_ver2();
	int QueryMin();
	bool isempty() { return length == 0; }
	void heapify_ver_NoRecur(int n, int index);
	void heapify_ver1_recur(int n, int index);
	void heapify_ver2_recur(int n, int index);
	void heapify_ver3_recur(int index);
	void heapsort_TopDown();
	void heapsort_BottomUp();
};

// parent's priority is higher than children's
class MaxHeap {
private:
	int* arr;
	int length;

public:
	MaxHeap() :length(0) { arr = new int[100]; }
	void Insertion(int n);
	void MaxDeletion();
	int QueryMax();
	bool isempty() { return length == 0; }
	void heapify_ver_NoRecur(int n, int index);
	void heapify(int n, int index);
};

int main(void) {
	MinHeap test = MinHeap();
	test.heapsort_BottomUp();

	return 0;
}

void MinHeap::Insertion(int n) {
	int insert_pos;
	
	for (insert_pos = ++length; (insert_pos > 1) || (arr[insert_pos / 2] > arr[insert_pos]); insert_pos /= 2) 
		arr[insert_pos] = arr[insert_pos / 2];
	
	arr[insert_pos] = n;
}

void MinHeap::MinDeletion_ver1() {
	if (isempty())
		return;
	
	int last_value = arr[length--];
	heapify_ver2_recur(last_value, 1);
}

void MinHeap::MinDeletion_ver2() {
	if (isempty())
		return;

	arr[1] = arr[length--];
	heapify_ver3_recur(1);
}

int MinHeap::QueryMin() {
	if (isempty())
		return -1;

	return arr[1];
}

//bottom-up method
void MinHeap::heapify_ver_NoRecur(int n, int index) {
	int comparison, next_index;

	while (index * 2 <= length) {
		comparison = arr[index * 2];
		next_index = index * 2;

		if ((index * 2 < length) && (comparison > arr[index * 2 + 1])) {
			comparison = arr[index * 2 + 1];
			next_index = index * 2 + 1;
		}

		if (comparison > arr[index])
			break;

		arr[index] = arr[next_index];
		index = next_index;
	}

	arr[index] = n;
}

// First, compare to two child nodes and then compare to parent node
void MinHeap::heapify_ver1_recur(int n, int index) {
	int comp_index;

	if (2 * index > length) {
		arr[index] = n;
		return;
	}

	comp_index = 2 * index;

	if ((2 * index < length) && (arr[comp_index] > arr[2 * index + 1]))
		comp_index = 2 * index + 1;

	if (arr[index] < arr[comp_index]) {
		arr[index] = n;
		return;
	}

	arr[index] = arr[comp_index];
	heapify_ver1_recur(n, comp_index);
}

// First, parent node compare to left child and then compare to right child
void MinHeap::heapify_ver2_recur(int n, int index) {
	int comp_index = index;
	arr[comp_index] = n; // 이 function은 array에 n값을 저장하는 것이 아니라 계속 n값을 전달해주기 때문에 필요하다.

	if ((2 * index <= length) && (arr[2 * index] < arr[comp_index]))
		comp_index = 2 * index;

	if ((2 * index < length) && (arr[2 * index + 1] < arr[comp_index]))
		comp_index = 2 * index + 1;

	if (comp_index != index) {
		arr[index] = arr[comp_index];
		heapify_ver2_recur(n, comp_index);
	}
}

/* 
	First, parent node compare to left child and then compare to right child
	Ver2와 달리 swap함수를 사용하여서 index만을 함수의 parameter로 사용하였다.
	재귀함수에서는 swap함수를 사용하는 것이
	int tmp = a;
	a = b;
	b = tmp;
	를 하는 것보다 더 좋다.
*/
void MinHeap::heapify_ver3_recur(int index) {
	int comp_index = index;

	if ((2 * index <= length) && (arr[2 * index] < arr[comp_index]))
		comp_index = 2 * index;

	if ((2 * index < length) && (arr[2 * index + 1] < arr[comp_index]))
		comp_index = 2 * index + 1;

	if (comp_index != index) {
		swap(arr[index], arr[comp_index]);
		heapify_ver3_recur(comp_index);
	}
}

// heap build시 들어오는 element마다 하나하나 비교를 하면서 위치를 정해주는 방법이다.
void MinHeap::heapsort_TopDown() {
	int itr, i, num;

	cin >> itr;

	for (i = 0; i < itr; i++) {
		cin >> num;
		Insertion(num);
	}

	for (i = 0; i < itr; i++) {
		cout << QueryMin() << " ";
		MinDeletion_ver1();
	}
}

// heap build를 할 때 제일 믿에 있는 subtree부터 heapify를 하는 방법이다.
void MinHeap::heapsort_BottomUp() {
	int itr, i, num;

	cin >> itr;
	length = itr;

	for (i = 1; i <= itr; i++) {
		cin >> num;
		arr[i] = num;
	}

	for (i = length / 2; i > 0; i--) heapify_ver3_recur(i);

	for (i = 0; i < itr; i++) {
		cout << QueryMin() << " ";
		MinDeletion_ver2();
	}
}

void MaxHeap::Insertion(int n) {
	int insert_pos;

	for (insert_pos = ++length; (insert_pos > 1) || (arr[insert_pos / 2] < arr[insert_pos]); insert_pos /= 2)
		arr[insert_pos] = arr[insert_pos / 2];

	arr[insert_pos] = n;
}

void MaxHeap::MaxDeletion() {
	if (isempty())
		return;

	int last_value = arr[length--];
	heapify_ver_NoRecur(last_value, 1);
}

int MaxHeap::QueryMax() {
	if (isempty())
		return -1;

	return arr[1];
}

void MaxHeap::heapify_ver_NoRecur(int n, int index) {
	int comparison, next_index;

	while (1) {
		if (arr[index * 2] > arr[index * 2 + 1]) {
			comparison = arr[index * 2];
			next_index = index * 2;
		}
		else {
			comparison = arr[index * 2 + 1];
			next_index = index * 2 + 1;
		}

		if (comparison < n)
			break;

		arr[index] = arr[next_index];
		index = next_index;
	}

	arr[index] = n;
}

void MaxHeap::heapify(int n, int index) {
	int comp_index = index;
	
	if ((2 * index <= length) && (arr[2 * index] > arr[comp_index]))
		comp_index = 2 * index;

	if ((2 * index < length) && (arr[2 * index + 1] > arr[comp_index]))
		comp_index = 2 * index + 1;

	if (comp_index != index) {
		arr[index] = arr[comp_index];
		heapify(n, comp_index);
	}
	else
		arr[index] = n;
}