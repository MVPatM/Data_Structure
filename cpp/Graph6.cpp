#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits> // 각 자료형의 max값과 min값을 표현하는 상수값이 저장이 되어 있다.

using namespace std;

typedef vector<int> Vint;
typedef vector<bool> Vbool;
typedef pair<int, int> Pint;

class Node {
private:
	int V, cost;
public:
	Node() : V(-1), cost(-1) {}
	Node(int v, int c) : V(v), cost(c) {}
	inline int GetV() const { return V; }
	inline int GetCost() const { return cost; }
	inline void SetV(int v) { this->V = v; }
	inline void SetCost(int cost) { this->cost = cost; }
};

typedef vector<Node> Vnode;

class Graph {
private:
	int V, E;
	Vint prev, path_cost;
	vector<Vnode> graph;
public:
	Graph();
	void DoDijkstra();
	void PrintPath(int p);
	void InitiateVectorsAssociatedDijkstra();
};

int main(void) {
	Graph graph = Graph();
	graph.DoDijkstra();

	return 0;
}

Graph::Graph() {
	int i, tail, head, cost;
	Vnode tmp;

	cout << "Input the number of vertices: ";
	cin >> V;

	cout << "Input the number of edges: ";
	cin >> E;

	for (i = 0; i < V; i++) graph.push_back(tmp);

	for (i = 0; i < E; i++) {
		cout << "input the edge and cost: ";
		cin >> tail >> head >> cost;
		graph[tail].emplace_back(head, cost);
	}

	InitiateVectorsAssociatedDijkstra();
}

void Graph::DoDijkstra() {
	int start, target, TailVertexNum;
	priority_queue<Pint, vector<Pint>, greater<Pint>> heap;
	
	cout << "Input the start vertex in path: ";
	cin >> start;
	cout << "Input the last vertex in path: ";
	cin >> target;

	path_cost[start] = 0;
	heap.push(make_pair(path_cost[start], start));
	
	while (!heap.empty()) {
		//path cost 가 최소인 값을 tailvertexnum으로 설정을 하면 된다.
		TailVertexNum = heap.top().second; // 우선순위 큐에서 꺼내기
		heap.pop();

		for (int i = 0; i < graph[TailVertexNum].size(); i++) {
			 Node Headnode = graph[TailVertexNum][i];

			if (path_cost[Headnode.GetV()] > path_cost[TailVertexNum] + Headnode.GetCost()) {
				path_cost[Headnode.GetV()] = path_cost[TailVertexNum] + Headnode.GetCost();
				prev[Headnode.GetV()] = TailVertexNum;
				heap.push(make_pair(path_cost[Headnode.GetV()], Headnode.GetV()));
			}
		}
	}

	PrintPath(target);
	InitiateVectorsAssociatedDijkstra();
}

void Graph::PrintPath(int p) {
	if (p < 0)
		return;

	PrintPath(prev[p]);
	cout << p << "\n";
}

void Graph::InitiateVectorsAssociatedDijkstra() {
	for (int i = 0; i < V; i++) {
		prev.push_back(-1);
		path_cost.push_back(INT_MAX);
	}
}