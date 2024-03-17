#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

class Node {
private:
	int vertex, weight;
public:
	Node() : vertex(-1), weight(-1) {}
	Node(int v, int w) :vertex(v), weight(w) {}
	inline int GetVertex() const { return vertex; }
	inline int GetWeight() const { return weight; }
};

typedef vector<Node> VNode;

class Edge {
private:
	Node dst;
	int src;
public:
	Edge() : dst(Node()), src(-1) {}
	Edge(Node n, int s):dst(n), src(s) {}
	inline Node GetDst() const { int n = 5; n = 8; return dst; }
	inline int Getsrc() const { return src; }
	friend bool operator> (const Edge& n1, const Edge& n2) { return n1.dst.GetWeight() > n2.dst.GetWeight(); }
};

class Graph {
private:
	int V, E; // express the number of vertices and edges.
	vector<VNode> graph; // 2 dimensional vector
public:
	Graph();
	void doPrim();
	void PrintMST(const vector<Edge>& mst);
};

int main(void){
	Graph g = Graph();
	g.doPrim();

	return 0;
}

Graph::Graph() {
	int i, src, dst, w;
	VNode tmp;
	cout << "Input the number of vertices: ";
	cin >> V;

	for (i = 0; i < V; i++) graph.push_back(tmp);

	cout << "Input the number of edges: ";
	cin >> E;

	for (i = 0; i < E; i++) {
		cout << "Input the edge: ";
		cin >> src >> dst;
		cout << "Input the cost: ";
		cin >> w;

		graph[src].emplace_back(dst, w);
		graph[dst].emplace_back(src, w);
	}
}

// 실수한 점: mst를 만드는 과정에서 무조건 target에서 시작되는 edge가 가장 cost가 작은 edge라고 가정이 된 채로 코딩이 진행되었다.
void Graph::doPrim() {
	vector<bool> isvisited(V, false);
	priority_queue<Edge, vector<Edge>, greater<Edge>> Min_Heap;
	Node tmp;
	vector<Edge> MST;

	for (int i = 0, target = 0; i < V - 1; i++) {
		isvisited[target] = true;

		for (unsigned int j = 0; j < graph[target].size(); j++) {
			if (!isvisited[graph[target][j].GetVertex()])
				Min_Heap.emplace(graph[target][j], target);
		}

		if (Min_Heap.empty()) {
			cout << "This graph doesn't make the MST" << "\n";
			return;
		}

		MST.emplace_back(Min_Heap.top());
		target = Min_Heap.top().GetDst().GetVertex();
		Min_Heap.pop();
	}

	PrintMST(MST);
}

void Graph::PrintMST(const vector<Edge>& mst) {
	for (unsigned int i = 0; i < mst.size(); i++)
		cout << mst[i].Getsrc() << "--" << mst[i].GetDst().GetVertex() << "\n";
}