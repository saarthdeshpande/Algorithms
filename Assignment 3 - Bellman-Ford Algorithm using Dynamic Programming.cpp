#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#define MAX_INT 100000
#define MAX 50
using namespace std;

struct Edge { 
    int src, dest, weight; 
}; 
  
class Graph {
	int n_vertices, n_edges;
    struct Edge* edge; 
public:
	Graph(int, int);
	void getData();
	void bellmanFord(int);
	void display(int[], int[], int);
};

Graph::Graph(int n_vertices, int n_edges) {
    this -> n_vertices = n_vertices;
    this -> n_edges = n_edges;
    this -> edge = new Edge[n_edges];
}

void Graph::getData() {
    cout << "\nGraph Edges\n";
    for (int i = 0;i < n_edges;i++) {
        cout << "\nEdge #" << i + 1 << endl;
        cout << "Source Node: ";
        cin >> edge[i].src;
        cout << "Destination Node: ";
        cin >> edge[i].dest;
        cout << "Weight of Edge: ";
        cin >> edge[i].weight;
    }
}

void Graph::bellmanFord(int src) {
    int distance[n_vertices], parent[n_vertices];
    for (int i = 0;i < n_vertices;i++)   // initialize distances for all vertices as infinity
        distance[i] = INT_MAX;

    distance[src] = 0; 
    parent[src] = -1;

    // relax all edges for shortest path |V| -1 times
    for (int i = 1;i <= n_vertices - 1;i++) {
        for (int j = 0;j < n_edges;j++) {
            int u = edge[j].src; 
            int v = edge[j].dest; 
            int weight = edge[j].weight; 
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight; 
                parent[v] = u;
            }
        } 
    }
    // check if negative weight cycle present
    // If we get a shorter path than above relaxation, cycle is present
    for (int i = 0;i < n_edges;i++) {
        int u = edge[i].src; 
        int v = edge[i].dest; 
        int weight = edge[i].weight; 

        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains negative weight cycle!" << endl;
            return;
            // return if negative cycle detected
        } 
    } 

    // To display the shortest distance and the path 
    display(distance, parent, src);
}

void Graph::display(int distance[], int parent[], int src) {
    stack <int> st;
    cout << endl << "Source vertex: " << src + 1 << endl << endl;
    cout << setw(3) << "Destination"<< setw(10) << "Distance" << setw(13) << "Path" << endl;
    for(int i = 0;i < n_vertices;i++) {
        cout << setw(6) << i + 1 << setw(11) << distance[i] << setw(12);
		st.push(i + 1);
		int p = parent[i];
		while(p != -1) {
			st.push(p + 1);
			p = parent[p];
		}
        cout << st.top();
        st.pop();
        while (!st.empty()) {
            cout << " -> " << st.top();
            st.pop();
        }
        cout << endl << endl;
	}
}

int main() {
    int n_vertices = 0, n_edges = 0;
    cout << "\nBELLMAN FORD ALGORITHM\n\n";
    while (n_vertices <= 0 || n_edges <= 0) {
        cout << "Number of Vertices: ";
        cin >> n_vertices;
        cout << "Number of Edges: ";
        cin >> n_edges;
    }
    Graph G(n_vertices, n_edges);
    G.getData();
    G.bellmanFord(0);
    return 0;
}

