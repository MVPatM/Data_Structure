// 다음과 같이 coding을 하면 multigraph를 표현을 하지 못한다.
#include <iostream>

using namespace std;

//No Digraph
class GraphbyArray {
private:
	int** G; // (tail, head)
	int vertex_num;
	int edge_num;
public:
	GraphbyArray();
	void PrintWeight(int tail, int head);
	int ReturnDegree(int v);
	bool isexistLoop();
};

class WeightgraphbyArray {
private:
	int** G; // (tail, head)
	int vertex_num;
	int edge_num;
public:
	WeightgraphbyArray();
	void PrintWeight(int tail, int head);
};

class DigraphbyArray {
private:
	int** G; // (tail, head)
	int vertex_num;
	int edge_num;
public:
	DigraphbyArray();
	void PrintWeight(int tail, int head);
};

int main(void) {

	GraphbyArray graph = GraphbyArray();
	cout << graph.ReturnDegree(3) << "\n";
	cout << graph.isexistLoop() << "\n";

	return 0;
}

GraphbyArray::GraphbyArray() {
	int v1, v2, i, j;
	
	cin >> vertex_num;

	G = new int* [vertex_num];
	for (i = 0; i < vertex_num; i++) G[i] = new int[vertex_num];

	for (i = 0; i < vertex_num; i++) {
		for (j = 0; j < vertex_num; j++)
			G[i][j] = 0;
	}

	cin >> edge_num;

	for (i = 0; i < edge_num; i++) {
		cin >> v1 >> v2;
		
		if ((v1 >= vertex_num) || (v2 >= vertex_num)) {
			i--;
			continue;
		}

		G[v1][v2] = 1;
		G[v2][v1] = 1;
	}
}

void GraphbyArray::PrintWeight(int tail, int head) {
	if ((tail >= vertex_num) || (head >= vertex_num))
		cout << "OutOfBound" << "\n";

	cout << G[tail][head] << "\n";
}

int GraphbyArray::ReturnDegree(int v) {
	int i, d = 0;

	for (i = 0; i < vertex_num; i++) d += G[v][i];

	d += G[v][v]; // For loop case

	return d;
}

bool GraphbyArray::isexistLoop() {
	for (int i = 0; i < vertex_num; i++) {
		if (G[i][i] == 1)
			return true;
	}

	return false;
}

WeightgraphbyArray::WeightgraphbyArray() {
	int v1, v2, weight, i, j;

	cin >> vertex_num;

	G = new int* [vertex_num];
	for (i = 0; i < vertex_num; i++) G[i] = new int[vertex_num];

	for (i = 0; i < vertex_num; i++) {
		for (j = 0; j < vertex_num; j++)
			G[i][j] = 0;
	}

	cin >> edge_num;

	for (i = 0; i < edge_num; i++) {
		cin >> v1 >> v2;

		if ((v1 >= vertex_num) || (v2 >= vertex_num)) {
			i--;
			continue;
		}

		cin >> weight;

		G[v1][v2] = weight;
		G[v2][v1] = weight;
	}
}

void WeightgraphbyArray::PrintWeight(int tail, int head) {
	if ((tail >= vertex_num) || (head >= vertex_num))
		cout << "OutOfBound" << "\n";

	cout << G[tail][head] << "\n";
}

DigraphbyArray::DigraphbyArray() {
	int tail, head, i, j;

	cin >> vertex_num;

	G = new int* [vertex_num];
	for (i = 0; i < vertex_num; i++) G[i] = new int[vertex_num];

	for (i = 0; i < vertex_num; i++) {
		for (j = 0; j < vertex_num; j++)
			G[i][j] = 0;
	}

	cin >> edge_num;

	for (i = 0; i < edge_num; i++) {
		cin >> tail >> head;

		if ((tail >= vertex_num) || (head >= vertex_num)) {
			i--;
			continue;
		}

		G[tail][head] = 1;
	}
}

void DigraphbyArray::PrintWeight(int tail, int head) {
	if ((tail >= vertex_num) || (head >= vertex_num))
		cout << "OutOfBound" << "\n";

	cout << G[tail][head] << "\n";
}