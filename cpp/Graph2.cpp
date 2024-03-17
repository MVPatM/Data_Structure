/*
	class에 있는 member variable에 맞게 함수를 설정하기
	이론적으로 사람의 머리에서 이루어지는 동작은 1번 경우가 옳을 수도 있지만
	실제로 코드를 만들다 보면은 2번경우가 훨씬 좋은 경우가 있다.
*/

#include <iostream>
#include <queue>

using namespace std;

// class자료형을 이용해서 dynamic array를 만들 때에는 class에 default constructor를 정의를 해주어야한다.
class Node1 {
private:
	int data, weight;
	Node1* next;
public:
	Node1(int d, int w = 1) : data(d), weight(w), next(NULL) {};
	Node1() :data(-1), weight(-1), next(NULL) {};
	int DataAccessor() { return data; }
	Node1* NextAccessor() { return next; }
	void NextMutator(Node1* n) { next = n; }
	void Node_add(int d, Node1* n, int w = 1);
	void PrintdataFromStartToEnd(Node1* n);
};

class Node2 {
private:
	int vertex1, vertex2, weight;
	Node2* next_v1, *next_v2;
public:
	Node2(int v1, int v2, int w = 1) :vertex1(v1), vertex2(v2), weight(w), next_v1(NULL), next_v2(NULL) {};
	Node2() : vertex1(-1), vertex2(-1), weight(-1), next_v1(NULL), next_v2(NULL) {};
	int V1Accessor() { return vertex1; }
	int V2Accessor() { return vertex2; }
	void Next1Mutator(Node2* n) { next_v1 = n; }
	void Next2Mutator(Node2* n) { next_v2 = n; }
	Node2* Next1Accessor() { return next_v1; }
	Node2* Next2Accessor() { return next_v2; }
};

// Node클래스를 이용하려면 먼저 Node class를 정의를 해주어야 한다.
class GraphbyList1 {
private:
	int vertex_num;
	int edge_num;
	Node1** graph;
	Node1** lastNode;
public:
	GraphbyList1();
	void addVertex1(int v1, int v2);
	void addVertex2(int v1, int v2);
	void PrintConnectedVertex1(int v) { graph[v]->PrintdataFromStartToEnd(graph[v]); }
	void PrintConnectedVertex2(int v) { for (Node1* n = graph[v]; n != NULL; n = n->NextAccessor()) cout << n->DataAccessor() << " "; }
	void DFS();
	void doDFS(int v, bool* visit);
	void isvisit(int v, bool* visit);
	void BFS();
};

class GraphbyList2 {
private:
	int vertex_num;
	int edge_num;
	Node2** graph;
	Node2** lastNode;
public:
	GraphbyList2();
	void AddEdge(int v1, int v2);
	void PrintEdges(int v);
	void DFS();
	void doDFS(int v, Node2* n, bool* visit);
	void isvisit(int v, bool* visit);
};

int main(void) {
	GraphbyList1 test = GraphbyList1();
	test.BFS();

	return 0;
}

// 기본인수 재정의 error발생 -> default parameter는 함수를 선언을 할 때만 표시해주면 된다. 정의 할 때도 표시를 하면 error발생
void Node1::Node_add(int d, Node1* n, int w) {
	if (n->next == NULL) {
		n->next = new Node1(d, w);
		return;
	}

	n = n->next;
	Node_add(d, n, w);
}

void Node1::PrintdataFromStartToEnd(Node1* n) {
	if (n == NULL)
		return;

	cout << n->data << " ";
	PrintdataFromStartToEnd(n->next);
}

GraphbyList1::GraphbyList1() {
	int i, v1, v2;
	
	cout << "Input the number of vertices: ";
	cin >> vertex_num;
	graph = new Node1 * [vertex_num];
	lastNode = new Node1 * [vertex_num];

	for (i = 0; i < vertex_num; i++) {
		graph[i] = NULL;
		lastNode[i] = NULL;
	}

	cout << "Input the number of edges: ";
	cin >> edge_num;

	for (i = 0; i < edge_num; i++) {
		cin >> v1 >> v2;
		//addVertex1(v1, v2);
		//addVertex1(v2, v1);
		addVertex2(v1, v2);
		addVertex2(v2, v1);
	}
}

// 시작 node부터 시작을 해서 끝 node까지 탐색을 하고 끝 node에서 새로운 node를 만든다. 
void GraphbyList1::addVertex1(int v1, int v2) {
	if (graph[v1] == NULL) {
		graph[v1] = new Node1(v2);
		return;
	}

	graph[v1]->Node_add(v2, graph[v1]);
}

// Last Node를 가리키는 array를 새로 만들어서 last Node를 저장하게 하여 바로바로 새로운 Node를 생성시키게 하였다.
void GraphbyList1::addVertex2(int v1, int v2) {
	if (lastNode[v1] == NULL) {
		graph[v1] = new Node1(v2);
		lastNode[v1] = graph[v1];
		return;
	}

	lastNode[v1]->NextMutator(new Node1(v2));
	lastNode[v1] = lastNode[v1]->NextAccessor();
}

// {if (!a)} == {if (a == false)}
void GraphbyList1::DFS() {
	int i;
	bool* isvisited = new bool[vertex_num];

	for (i = 0; i < vertex_num; i++) isvisited[i] = false;
	
	for (i = 0; i < vertex_num; i++) {
		if (!isvisited[i])
			doDFS(i, isvisited);
	}
}

void GraphbyList1::doDFS(int v, bool* visit) {
	isvisit(v, visit);
	
	for (Node1* n = graph[v]; n != NULL; n = n->NextAccessor()) {
		if (!visit[n->DataAccessor()])
			doDFS(n->DataAccessor(), visit);
	}
}

void GraphbyList1::isvisit(int v, bool* visit) {
	visit[v] = true;
	cout << v << " ";
}

// (주의) 다른 함수로 가서 queue를 그냥 전달하면 다른 함수에서 push나 pop연산을 한 것이 반영이 되지 않는다. 
// queue를 pointer형식으로 전달을 해주지 않았기 때문에 문제가 발생을 하는 것이다.
// 
void GraphbyList1::BFS() {
	int i;
	Node1* n;
	bool* isvisited = new bool[vertex_num];
	queue<int> queue;

	for (i = 0; i < vertex_num; i++) isvisited[i] = false;
	
	for (i = 0; i < vertex_num; i++) {
		if (!isvisited[i]) {
			isvisited[i] = true; // queue가 empty인 상황에서 vertex를 bfs탐색을 해야 할 때 문제를 해결해 준다.
			queue.push(i);       // >> while문에서 push를 하는데 empty인 예외가 존재? > 미리 앞에서 하나를 queue에 push를 해준다.

			while (!queue.empty()) {
				for (n = graph[queue.front()]; n != NULL; n = n->NextAccessor()) {
					if (!isvisited[n->DataAccessor()]) {
						isvisited[n->DataAccessor()] = true; // queue에 push를 하면서 bool자료형의 값을 바꾸지 않으면 queue에 같은 수가 push가 되는 문제가 발생
						queue.push(n->DataAccessor());
					}
				}
				cout << queue.front() << " ";
				queue.pop();
			}
		}
	}
}

GraphbyList2::GraphbyList2() {
	int i, v1, v2;

	cout << "Input the number of vertices: ";
	cin >> vertex_num;
	graph = new Node2 * [vertex_num];
	lastNode = new Node2 * [vertex_num];

	for (i = 0; i < vertex_num; i++) {
		graph[i] = NULL;
		lastNode[i] = NULL;
	}

	cout << "Input the number of edges: ";
	cin >> edge_num;

	for (i = 0; i < edge_num; i++) {
		cin >> v1 >> v2;
		AddEdge(v1, v2);
	}

}

void GraphbyList2::AddEdge(int v1, int v2) {
	Node2* tmp = new Node2(v1, v2);

	if (lastNode[v1] == NULL) {
		graph[v1] = tmp;
		lastNode[v1] = tmp;
	}
	else {
		if (v1 == lastNode[v1]->V1Accessor())
			lastNode[v1]->Next1Mutator(tmp);
		else
			lastNode[v1]->Next2Mutator(tmp);

		lastNode[v1] = tmp;
	}

	if (lastNode[v2] == NULL) {
		graph[v2] = tmp;
		lastNode[v2] = tmp;
	}
	else {
		if (v2 == lastNode[v2]->V1Accessor())
			lastNode[v2]->Next1Mutator(tmp);
		else
			lastNode[v2]->Next2Mutator(tmp);

		lastNode[v2] = tmp;
	}
}

void GraphbyList2::PrintEdges(int v) {
	for (Node2* n = graph[v]; n != NULL;) {
		cout << n->V1Accessor() << "-" << n->V2Accessor() << "\n";

		if (v == n->V1Accessor())
			n = n->Next1Accessor();
		else
			n = n->Next2Accessor();
	}
}

// if (a == false) <=> if (!a)  만약 a가 bool자료형을 가지고 있다면.
void GraphbyList2::DFS() {
	int i;
	bool* isvisited = new bool[vertex_num];

	for (i = 0; i < vertex_num; i++) isvisited[i] = false;

	for (i = 0; i < vertex_num; i++) {
		if (!isvisited[i]) {
			isvisit(i, isvisited);
			doDFS(i, graph[i], isvisited);
		}
	}
}

void GraphbyList2::doDFS(int v, Node2* n, bool* visit) {
	if (n == NULL)
		return;

	int d;
	Node2* next1, *next2;

	if (v == n->V1Accessor()) {
		d = n->V2Accessor();
		next1 = n->Next2Accessor();
		next2 = n->Next1Accessor();
	}
	else {
		d = n->V1Accessor();
		next1 = n->Next1Accessor();
		next2 = n->Next2Accessor();
	}

	if (!visit[d])
		isvisit(d, visit);

	doDFS(d, next1, visit);
	doDFS(v, next2, visit);
}

void GraphbyList2::isvisit(int v, bool* visit) {
	visit[v] = true;
	cout << v << " ";
}