#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0)
#define vertex_size 1000000
#define INF INT_MAX
using pii = pair<int, int>; // <dest_vertex_num, edge_cost>

struct cmp{
    bool operator() (pii a, pii b){
        return a.second > b.second;
    }
};

bool isNotZeroIn[vertex_size]; // false: zero indegree value
bool isvisited[vertex_size];
int VertexCost[vertex_size];
int ans = 0;
int L_src, L_des;
vector<vector<pii>> graph(vertex_size);

void InputInfo();
void Initialize();
void Dijkstra(int start);

int main(void){
    fastio;
    InputInfo();
    
    for (int i = 0; i < vertex_size; i++){
        if (!isNotZeroIn[i]){
            Initialize();
            Dijkstra(i);
        }
    }

    cout << L_src << " " << L_des << " " << ans;
    
    return 0;
}

// Get the data from the file
void InputInfo() {
    ifstream fin;
    fin.open("1000000.graph");
    int src, des, cost;
    
    while (!fin.eof()){
        fin >> src;
        fin >> des;
        fin >> cost;
    
        graph[src].emplace_back(des, cost);
        isNotZeroIn[des] = true;
    }

    fin.close();
}

// Initialize the variable.
void Initialize() {
    memset(isvisited, false, sizeof(isvisited));
    fill(VertexCost, VertexCost + vertex_size, INF);
}

// Run the dijkstra algorithm
void Dijkstra(int start) {
    priority_queue<pii, vector<pii>, cmp> pq; // <vertex_num, cost>
    int cur_vertex, next_vertex, max_des, cur_cost, next_cost, max_value = 0;
    pq.emplace(start, 0);
    VertexCost[start] = 0;

    while (!pq.empty()){
        cur_vertex = pq.top().first;
        cur_cost = pq.top().second;
        pq.pop();

        if (!isvisited[cur_vertex]){
            for (int i = 0; i < graph[cur_vertex].size(); i++){
                next_vertex = graph[cur_vertex][i].first;
                next_cost = graph[cur_vertex][i].second;

                if (cur_cost + next_cost < VertexCost[next_vertex]){
                    VertexCost[next_vertex] = cur_cost + next_cost;
                    pq.emplace(next_vertex, VertexCost[next_vertex]);
                }
            }

            isvisited[cur_vertex] = true;

            if (cur_cost > max_value){
                max_value = cur_cost;
                max_des = cur_vertex;
            }
        }
    }
    
    if (max_value > ans){
        L_src = start;
        L_des = max_des;
        ans = max_value;
    }
}