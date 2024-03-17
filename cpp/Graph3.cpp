// ���� �̸��� ���� �� ���� ����� ���� �ʵ��� ���� �ֳ��ϸ� 1�� I�� �򰥸��� �����̴�.

#include <iostream>
#include <queue>

using namespace std;

class Node {
private:
	int vertex, weight;
	Node* next;
public:
	Node() : vertex(-1), weight(-1), next(nullptr) {}
	Node(int v, int w) :vertex(v), weight(w), next(nullptr) {}
	Node* accessorNext() { return next; }
	void mutatorNext(Node* n) { next = n; }
	int GetVertexNum() { return vertex; }
	int GetWeight() { return weight; }
};

class Edge {
private:
	int v1, v2, cost;
public:
	Edge() : v1(NULL), v2(NULL), cost(NULL) {}
	Edge(int s, int d, int w) : v1(s), v2(d), cost(w) {}
	int GetV1Num() { return v1; }
	int GetV2Num() { return v2; }
	int GetCost() { return cost; }
	void mutatorV1(int v) { v1 = v; }
	void mutatorV2(int v) { v2 = v; }
	void mutatorCost(int c) { cost = c; }
	void mutatorEdge(int s, int d, int w);
};

class MinHeap {
private:
	Edge* heap;
	int lastIndex;
public:
	MinHeap() : heap(nullptr), lastIndex(0) {}
	MinHeap(int l);
	~MinHeap() { delete[] heap; }
	bool isempty() { return lastIndex == 0; }
	void swapEdge(int i1, int i2);
	void insert(int src, int dst, int w);
	Edge deleteMin();
	void heapify(int index);
};

class UF {
private:
	int* parent;
	int* card;
public:
	UF(): parent(nullptr), card(nullptr) {}
	UF(int num);
	~UF() { delete parent; delete card; }
	void un(int n1, int n2);
	int find(int n);
	bool issameparent(int n1, int n2) { return find(n1) == find(n2); }
};

class Graph {
private:
	Node** graph;
	Node** lastNode;
	int vertex_num, edge_num;
public:
	Graph();
	~Graph();
	void addvertex(int src, int dst, int cost);
	void FindAllEdges(MinHeap* h);
	void doKruskal();
	void printMST(Edge* tree);
};

int main(void) {
	Graph g = Graph();
	g.doKruskal();
	 
	return 0;
}

void Edge::mutatorEdge(int s, int d, int w) {
	mutatorV1(s);
	mutatorV2(d);
	mutatorCost(w);
}

// class �迭�� �ϳ��ϳ� �ʱ�ȭ ��Ű�� ������ default constructor�� �̿��ؼ� �ʱ�ȭ�� �ȴ�.
MinHeap::MinHeap(int l) {
	int length = l + 1;
	heap = new Edge[length];
	lastIndex = 0;

	// Buffer overrun warning �߻� >> �����Ҵ��� �� �� �⺻variable �� ������ ���ؼ� g�ϸ� warning �߻��� �ȴ�.
	for (int i = 0; i < length; i++) heap[i] = Edge();
}

// ���� �����ε� ���� �ϱ�
void MinHeap::swapEdge(int i1, int i2) {
	Edge tmp = heap[i1];
	heap[i1] = heap[i2];
	heap[i2] = tmp;
}

// recursion�� �̿��ϸ� ������ index��ġ�� �˷��־�� �Ѵ�. But graph������ Heap���� ������ �𸥴�. > recursion ��� x
void MinHeap::insert(int src, int dst, int w) {
	heap[++lastIndex].mutatorEdge(src, dst, w);

	// for�ȿ� if�� �ϳ����� ����� �� for�������� ������ ����ϴ� �κп� ��� �� code�� ������ �� �� �ִ�.
	for (int idx = lastIndex; idx > 1 && heap[idx / 2].GetCost() > w; idx /= 2) swapEdge(idx, idx / 2);
}

Edge MinHeap::deleteMin() {
	if (isempty())
		return Edge();
	
	swapEdge(1, lastIndex--);
	heapify(1);

	return heap[lastIndex + 1];
}

void MinHeap::heapify(int index) {
	int target = index;
	
	if ((lastIndex >= 2 * index) && (heap[target].GetCost() > heap[2 * index].GetCost()))
		target = 2 * index;

	if ((lastIndex > 2 * index) && (heap[target].GetCost() > heap[2 * index + 1].GetCost()))
		target = 2 * index + 1;

	if (target != index) {
		swapEdge(index, target);
		heapify(target);
	}
}

UF::UF(int num) {
	parent = new int[num];
	card = new int[num];

	for (int i = 0; i < num; i++) {
		parent[i] = i;
		card[i] = 1;
	}
}

// union�� �� �� height�� ���� ���� ū ������ �������� ����� �̿��� �ϸ� ������ height�� �������� height+1�� �ؾ��ϰ� �ٸ��ٸ� ū ���� height�� �״�� �����ȴ�.
// �� �������� cardinality�� �̿��� �� ���� �ʾƵ� �Ǵ� �Ǵٸ� �񱳸� �ϰ� �ȴ�,      
// cardinality�� �̿��� �ϸ� �׳� ū cardinality�� ���� cardinality�� ���ϱ⸸ �ϸ� �ȴ�.
void UF::un(int n1, int n2) {
	int p1 = find(n1);
	int p2 = find(n2);

	if (card[p1] > card[p2]) {
		parent[p2] = p1;
		card[p1] += card[p2];
	}
	else {
		parent[p1] = p2;
		card[p2] += card[p1];
	}
}

int UF::find(int n) {
	int p;

	for (p = n; parent[p] != p; p = parent[p]) {}

	return p;
}

Graph::Graph() {
	int i, s, d, w;

	cout << "Input the number of vertices: ";
	cin >> vertex_num;

	graph = new Node * [vertex_num];
	lastNode = new Node * [vertex_num];

	for (i = 0; i < vertex_num; i++) {
		graph[i] = NULL;
		lastNode[i] = NULL;
	}

	cout << "Input the number of edges: ";
	cin >> edge_num;

	for (i = 0; i < edge_num; i++) {
		cin >> s >> d;
		cout << "Input the edge's cost: ";
		cin >> w;

		addvertex(s, d, w);
		addvertex(d, s, w);
	}
}

Graph::~Graph() {
	for (int i = 0; i < vertex_num; i++) {
		delete graph[i];
		delete lastNode[i];
	}

	delete[] graph;
	delete[] lastNode;
}

void Graph::addvertex(int src, int dst, int cost) {
	if (lastNode[src] == NULL) {
		graph[src] = new Node(dst, cost);
		lastNode[src] = graph[src];
		return;
	}

	lastNode[src]->mutatorNext(new Node(dst, cost));
	lastNode[src] = lastNode[src]->accessorNext();
}

// return �������δ� �����ε��� �� �� ����. parameter ������ �پ����� ���ؼ� �����ε��� �� �� �ִ�.
void Graph::FindAllEdges(MinHeap* h) { // search for all edges
	int i;
	Node* n;

	for (i = 0; i < vertex_num; i++) {
		for (n = graph[i]; n != NULL; n = n->accessorNext()) {
			if (n->GetVertexNum() > i)
				h->insert(i, n->GetVertexNum(), n->GetWeight());
		}
	}
}

void Graph::doKruskal() {
	int mstEdge_num = 0;
	int l = vertex_num - 1;
	MinHeap* h = new MinHeap(edge_num);
	UF uf = UF(vertex_num);
	Edge tmp;
	Edge* mst = new Edge[l];
	for (int i = 0; i < vertex_num - 1; i++) mst[i] = Edge();

	FindAllEdges(h);
	// heap�� empty�ϰų� edge�� ���� ���� v-1�϶� ���� �ݺ��ϱ�
	
	while (!h->isempty() || mstEdge_num != vertex_num - 1) {
		do {
			tmp = h->deleteMin();
		} while (uf.issameparent(tmp.GetV1Num(), tmp.GetV2Num()));

		uf.un(tmp.GetV1Num(), tmp.GetV2Num());
		mst[mstEdge_num++].mutatorEdge(tmp.GetV1Num(), tmp.GetV2Num(), tmp.GetCost());
	}

	if (mstEdge_num != vertex_num - 1)
		cout << "It's not minimum spanning tree" << "\n";
	else
		printMST(mst);
}

void Graph::printMST(Edge* tree) {
	for (int i = 0; i < vertex_num - 1; i++) {
		cout << tree[i].GetV1Num() << "----" << tree[i].GetV2Num() << "\n";
	}
}