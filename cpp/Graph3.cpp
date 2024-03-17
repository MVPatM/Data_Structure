// 변수 이름을 정할 때 ㅣ을 사용을 하지 않도록 하자 왜냐하면 1과 I와 헷갈리기 떄문이다.

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

// class 배열을 하나하나 초기화 시키지 않으면 default constructor를 이용해서 초기화가 된다.
MinHeap::MinHeap(int l) {
	int length = l + 1;
	heap = new Edge[length];
	lastIndex = 0;

	// Buffer overrun warning 발생 >> 동적할당을 할 때 기본variable 에 연산을 통해서 g하면 warning 발생이 된다.
	for (int i = 0; i < length; i++) heap[i] = Edge();
}

// 연산 오버로딩 주의 하기
void MinHeap::swapEdge(int i1, int i2) {
	Edge tmp = heap[i1];
	heap[i1] = heap[i2];
	heap[i2] = tmp;
}

// recursion을 이용하면 직전의 index위치를 알려주어야 한다. But graph에서는 Heap내부 정보를 모른다. > recursion 사용 x
void MinHeap::insert(int src, int dst, int w) {
	heap[++lastIndex].mutatorEdge(src, dst, w);

	// for안에 if문 하나만을 사용할 때 for문에서의 조건을 명시하는 부분에 적어서 더 code를 간단히 할 수 있다.
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

// union을 할 때 height가 작은 것이 큰 것으로 합쳐지는 방식을 이용을 하면 각각의 height가 같으면은 height+1를 해야하고 다르다면 큰 것의 height가 그대로 유지된다.
// 이 과정에서 cardinality를 이용할 때 하지 않아도 되는 또다른 비교를 하게 된다,      
// cardinality를 이용을 하면 그냥 큰 cardinality에 작은 cardinality를 더하기만 하면 된다.
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

// return 형식으로는 오버로딩을 할 수 없다. parameter 형식의 다양함을 통해서 오버로딩을 할 수 있다.
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
	// heap이 empty하거나 edge에 넣은 수가 v-1일때 까지 반복하기
	
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