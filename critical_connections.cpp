/*
You are given an undirected connected graph. 
An articulation point (or cut vertex) is defined as a vertex which, 
when removed along with associated edges, makes the graph disconnected (or more precisely, 
increases the number of connected components in the graph). 
The task is to find all articulation points in the given graph.

Input:
The input to the function/method consists of three arguments:
numNodes, an integer representing the number of nodes in the graph.
numEdges, an integer representing the number of edges in the graph.
edges, the list of pair of integers - A, B representing an edge between the nodes A and B.

Output:
Return a list of integers representing the critical nodes.
OR
Return a list of pairs representing the bridges.

Example:

Input: numNodes = 7, numEdges = 7, edges = [[0, 1], [0, 2], [1, 3], [2, 3], [2, 5], [5, 6], [3, 4]]
*/

#include<iostream>
#include<list>
#include<utility>  // pair
using namespace std;

class Graph {
private:
    int V; // Number of vertices
    int outEdges = 0;
    int id = 0;
    list<int> *adj; // Dynamic array of adjacency vertices
    list<pair<int, int>> bg; // bridges
    
    int *ids = new int[V];
    bool *visited = new bool[V];  // mark traversed vertices
    int *low = new int[V];  // low-link value for each vertex
    bool *ap = new bool[V];  // track AP 
    // int *parent = new int[V];  // track parent vertices
    
    void dfsAP(int root, int at, int parent);
    void dfsBG(int at, int parent);

public:
    Graph(int nv) : V{nv} { 
        adj = new list<int>[V]; 
        for(int i = 0; i < V; ++i) {
            visited[i] = false;
            ap[i] = false;
            low[i] = 0;
        }
    }
    void printLow() {
        for(int i = 0; i < V; i++) {
            cout << low[i] << " ";
        }
    }
    // Clear visited array (set to the default - false)
    void clear() {
        id = 0;
        for(int i = 0; i < V; ++i) {
            visited[i] = false;
            low[i] = 0;
        }
        return;
    }
    void addEdge(int v, int w);
    
    // Articulation Points
    void AP();
    
    // Bridges (Articulation Edges)
    void BG();
};

void Graph::addEdge(int v, int w) {
    if (v > V - 1 || w > V - 1) {
        printf("Vertex does not exist!\n");
        exit(1);
    }
    if (v == w) {
        printf("Not support self-link!\n");
        exit(1);
    }
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::AP() {
    for(int i = 0; i < V; ++i) {
        if(!visited[i]) {
            outEdges = 0;
            dfsAP(i, i, -1);
            // printf("%d\n", outEdges);
            ap[i] = (outEdges > 1);
        }
    }
    
    for(int i = 0; i < V; ++i) {
        if(ap[i] == true)
            printf("%d ", i);
    }
}

void Graph::dfsAP(int root, int at, int parent) {
    // Count of children in DFS tree
    if(parent == root)
        ++outEdges;
    visited[at] = true;
    low[at] = ids[at] = id;
    ++id;
    
    // iterate all adjacent vertices
    for(auto i = adj[at].begin(); i != adj[at].end(); ++i) {
        int to = *i; 
        if(to == parent) continue;
        // if "to" is not visited, make "to" a child of "at"
        if(!visited[to]) {
            dfsAP(root, to, at);
            
            // set low-link value of at
            low[at] = min(low[at], low[to]);
            
            // 1. AP found through bridge
            if(ids[at] < low[to])
                ap[at] = true;
            // 2. AP found through cycle
            if(ids[at] == low[to]) {
                // cout << "\""<< at << ", " << to << "\"";
                ap[at] = true;
            }
        }
        else {
            // Update low-link value of at for parent function calls. 
            low[at] = min(low[at], ids[to]);
        }
    }
}

void Graph::BG() {
    for(int i = 0; i < V; ++i) {
        if(!visited[i]) {
            // dfsBG(at, parent, bridges)
            dfsBG(i, -1);
        }
    }
    // Print bg
    for(auto& b : bg) {
        cout << "{" << b.first << "," << b.second << "}";
    }
}

void Graph::dfsBG(int at, int parent) {
    visited[at] = true;
    low[at] = ids[at] = id;
    ++id;
    
    for(auto i = adj[at].begin(); i != adj[at].end(); ++i) {
        int to = *i; 
        if(to == parent) continue;
        if(!visited[to]) {
            dfsBG(to, at);
            // set low-link value of at
            low[at] = min(low[at], low[to]);
            // AP found through bridge
            //if(at == 1 && to == 2)
              //  cout << "!!!03:" << ids[at] << low[to] <<"!!!\n";
            if(ids[at] < low[to])
                bg.emplace_back(at, to);
        }
        else
            // Update low-link value of at for parent function calls. 
            low[at] = min(low[at], ids[to]);
    }
}


/*
// If an undirected connections was given..

class Solution {
public:
    vector<vector<int>> bg;
    bool* visited;
    int* low;
    int* ids;
    list<int>* adj;
    
    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        visited = new bool[n];
        low = new int[n];
        ids = new int[n];
        for(int i = 0; i < n; ++i) {
            visited[i] = false;
        }
        adj = new list<int>[n];
        for(auto& v : connections) {
            adj[v[0]].push_back(v[1]);
            adj[v[1]].push_back(v[0]);
        }
        for(int i = 0; i < n; ++i) {
            if(!visited[i])
                dfsBG(i, -1);
        }
        return bg;
    }
    
    void dfsBG(int at, int parent) {
        static int id = 0;
        visited[at] = true;
        low[at] = ids[at] = id;
        ++id;
        for(auto i = adj[at].begin(); i != adj[at].end(); ++i) {
            int to = *i;
            if(to == parent) continue;
            if(!visited[to]) {
                dfsBG(to, at);
                // set low link value
                low[at] = min(low[at], low[to]);
                if(ids[at] < low[to]) {
                    bg.emplace_back(vector<int>{at, to});
                }
            }
            else
                low[at] = min(low[at], ids[to]);
        }
    }
};

*/

int main() {
    Graph g1(5); 
    g1.addEdge(1, 0); 
    g1.addEdge(0, 2); 
    g1.addEdge(2, 1); 
    g1.addEdge(0, 3); 
    g1.addEdge(3, 4); 
    printf("g1 AP:");
    g1.AP();
    g1.clear();
    printf("g1 BG:");
    g1.BG();
    printf("\n");
    //g1.printLow();
    
    
    Graph g2(4); 
    g2.addEdge(0, 1); 
    g2.addEdge(1, 2); 
    g2.addEdge(2, 3); 
    printf("g2 AP:");
    g2.AP();
    g2.clear();
    printf("g2 BG:");
    g2.BG();
    printf("\n");
    
    /*
    g1 AP:0 3 g1 BG:{3,4}{0,3}
    g2 AP:1 2 g2 BG:{2,3}{1,2}{0,1}
    */
    return 0;
}
