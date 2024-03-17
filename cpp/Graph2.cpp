/*
	class�� �ִ� member variable�� �°� �Լ��� �����ϱ�
	�̷������� ����� �Ӹ����� �̷������ ������ 1�� ��찡 ���� ���� ������
	������ �ڵ带 ����� ������ 2����찡 �ξ� ���� ��찡 �ִ�.
*/

#include <iostream>
#include <queue>

using namespace std;

// class�ڷ����� �̿��ؼ� dynamic array�� ���� ������ class�� default constructor�� ���Ǹ� ���־���Ѵ�.
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

// NodeŬ������ �̿��Ϸ��� ���� Node class�� ���Ǹ� ���־�� �Ѵ�.
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

// �⺻�μ� ������ error�߻� -> default parameter�� �Լ��� ������ �� ���� ǥ�����ָ� �ȴ�. ���� �� ���� ǥ�ø� �ϸ� error�߻�
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

// ���� node���� ������ �ؼ� �� node���� Ž���� �ϰ� �� node���� ���ο� node�� �����. 
void GraphbyList1::addVertex1(int v1, int v2) {
	if (graph[v1] == NULL) {
		graph[v1] = new Node1(v2);
		return;
	}

	graph[v1]->Node_add(v2, graph[v1]);
}

// Last Node�� ����Ű�� array�� ���� ���� last Node�� �����ϰ� �Ͽ� �ٷιٷ� ���ο� Node�� ������Ű�� �Ͽ���.
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

// (����) �ٸ� �Լ��� ���� queue�� �׳� �����ϸ� �ٸ� �Լ����� push�� pop������ �� ���� �ݿ��� ���� �ʴ´�. 
// queue�� pointer�������� ������ ������ �ʾұ� ������ ������ �߻��� �ϴ� ���̴�.
// 
void GraphbyList1::BFS() {
	int i;
	Node1* n;
	bool* isvisited = new bool[vertex_num];
	queue<int> queue;

	for (i = 0; i < vertex_num; i++) isvisited[i] = false;
	
	for (i = 0; i < vertex_num; i++) {
		if (!isvisited[i]) {
			isvisited[i] = true; // queue�� empty�� ��Ȳ���� vertex�� bfsŽ���� �ؾ� �� �� ������ �ذ��� �ش�.
			queue.push(i);       // >> while������ push�� �ϴµ� empty�� ���ܰ� ����? > �̸� �տ��� �ϳ��� queue�� push�� ���ش�.

			while (!queue.empty()) {
				for (n = graph[queue.front()]; n != NULL; n = n->NextAccessor()) {
					if (!isvisited[n->DataAccessor()]) {
						isvisited[n->DataAccessor()] = true; // queue�� push�� �ϸ鼭 bool�ڷ����� ���� �ٲ��� ������ queue�� ���� ���� push�� �Ǵ� ������ �߻�
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

// if (a == false) <=> if (!a)  ���� a�� bool�ڷ����� ������ �ִٸ�.
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