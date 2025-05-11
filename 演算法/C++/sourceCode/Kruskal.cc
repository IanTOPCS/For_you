// Kruskal's algorithm in C++

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define edge pair<int, int>

class Graph {
private:
    vector<pair<int, edge> > G;  // graph
    vector<pair<int, edge> > T;  // mst
    vector<int> rank;
    int *parent;
    int V;  // number of vertices/nodes in graph
    public:
    Graph(int V);
    void AddWeightedEdge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};
Graph::Graph(int V) {
    parent = new int[V];
    rank.resize(V, 0);
    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }
}
void Graph::AddWeightedEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}
int Graph::find_set(int i) {
    if (i != parent[i]) 
        parent[i] = find_set(parent[i]);  // 路徑壓縮
    return parent[i];
}
void Graph::union_set(int u, int v) {
    int rootU = find_set(u);
    int rootV = find_set(v);
    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}
void Graph::kruskal() {
    int i, uRep, vRep;
    sort(G.begin(), G.end());  // increasing weight
    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            T.push_back(G[i]);  // add to tree
            union_set(uRep, vRep);
        }
    }
}
void Graph::print() {
    int total{0};
    // cout << "Edge :" << " Weight" << endl;
    for (int i = 0; i < T.size(); i++) {
        // cout << T[i].second.first << " - " << T[i].second.second << " : "<< T[i].first << endl;
        total += T[i].first;
    }
    cout<<"The cost of minimum spanning tree: "<<total<<endl;
}

class store{
public:
    int u;
    int v;
    int w;
    store(int u = 0, int v = 0, int w = 0);
};

store::store(int u, int v, int w){
    this->u = u;
    this->v = v;
    this->w = w;
}

int main() {
    int nodeNum{0}, edgeNum{0}, cinNum{0};
    cin>>nodeNum>>edgeNum;
    int u{0}, v{0}, w{0};
    vector<store>tmp;
    while(cin>>u>>v>>w){
        tmp.push_back(store(u, v, w));
        cinNum++;
    }
    Graph g(nodeNum);
    for(int i = 0; i<cinNum; i++) g.AddWeightedEdge(tmp[i].u, tmp[i].v, tmp[i].w);
    g.kruskal();
    g.print();
    return 0;
}

/*
7 9
0 1 28
0 5 10
1 2 16
1 6 14
2 3 12
3 4 22
3 6 18
4 5 25
4 6 24
*/

/*
5 7
0 1 88
0 2 58
0 4 10
1 2 82
1 3 92
2 4 67
3 4 7
*/