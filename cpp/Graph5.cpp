#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
private:
	int vertex;
public:
	Node() : vertex(-1) {}
	Node(int v) : vertex(v) {}
	inline int GetVertex() const { return vertex; }
};

typedef vector<Node> VNode;
typedef vector<bool> Vbool;

class DiGraph {
private:
	int V, E;
	vector<VNode> graph;
	vector<int> indegree;
public:
	DiGraph();
	void doDFS();
	void DFS(Vbool& visit, int v);
	inline void Calindegree() { doDFS(); }
	void TopologicalSort();
};

int main(void) {
	DiGraph t;
	t.TopologicalSort();

	return 0;
}

DiGraph::DiGraph() {
	int i, s, d;
	VNode tmp;

	cout << "Input the number of vertices: ";
	cin >> V;

	for (i = 0; i < V; i++) {
		graph.push_back(tmp);
		indegree.push_back(0);
	}

	cout << "Input the number of edges: ";
	cin >> E;

	for (i = 0; i < E; i++) {
		cout << "Input the edge: ";
		cin >> s >> d;
		graph[s].emplace_back(d);
	}
}

void DiGraph::doDFS() {
	int i;
	Vbool isvisited;

	for (i = 0; i < V; i++)
		isvisited.push_back(false);

	for (i = 0; i < V; i++) {
		if (!isvisited[i])
			DFS(isvisited, i);
	}
}

void DiGraph::DFS(Vbool& visit, int v) {
	int dst;
	visit[v] = true;

	for (int i = 0; i < graph[v].size(); i++) {
		dst = graph[v][i].GetVertex();
		indegree[dst]++;

		if (!visit[dst])
			DFS(visit, dst);
	}
}

void DiGraph::TopologicalSort() {
	int i, j, src, dst;
	queue<int> ZeroIndegreeVertices;
	Vbool ispushed;
	vector<int> sorted;

	Calindegree();
	
	// 조건에 맞는 값을 queue에 일단 모두 push 하고서 그 값을 원할 때 queue에서 꺼내어서 사용한다.
	// 그때 그때 조건에 맞는 값을 찾으면 더 시간이 많이 걸린다.
	for (i = 0; i < V; i++) {
		ispushed.push_back(false);

		if (indegree[i] == 0)
			ZeroIndegreeVertices.push(i);
	}

	for (i = 0; i < V; i++) {
		if (ZeroIndegreeVertices.empty()) {
			cout << "This Graph can't do topological sort\n";
			return;
		}
	
		src = ZeroIndegreeVertices.front();

		for (j = 0; j < graph[src].size(); j++) {
			dst = graph[src][j].GetVertex();
			indegree[dst]--;

			if (indegree[dst] == 0 && !ispushed[dst])
				ZeroIndegreeVertices.push(dst);
		}

		sorted.push_back(src);
		ZeroIndegreeVertices.pop();
	}

	for (i = 0; i < V; i++)
		cout << sorted[i] << " ";
}