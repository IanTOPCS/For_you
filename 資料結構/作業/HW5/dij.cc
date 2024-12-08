#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int,int> iPair;

//類別
class Graph{
    int V; //有多少個點(Vertices)

    list<pair<int,int>>* adj; //用相鄰串列(Adjacency List)記錄圖(Graph)

public:
    Graph(int V);//建構子

    //添加E(邊)與權重，其中E(邊)是由兩個點(vertices)構成
    void addEdge(int u,int v,int w);

    //印出最短路徑
    void shortestPath(int s);
};

//類別實作

Graph::Graph(int V){
    this->V = V;//有多少個點(Vertices)
    adj = new list<iPair>[V];//創建相鄰串列(Adjacency List)，有V個點就有V個串列
}

void Graph::addEdge(int u,int v,int w){
    adj[u].push_back(make_pair(v,w));//以u為主的list儲存點v與到點v的權重(w)
    adj[v].push_back(make_pair(u,w));//v也可以到u
}

//印出點src到所有點的距離
void Graph::shortestPath(int src){

    //創建priority queue用於儲存vertices與距離，快速決定該回合最小距離
    //對於priority_queue的用法可以查看下面連結教學
    // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    priority_queue<iPair, vector<iPair>,greater<iPair>> pq;

    //設定到所有點的距離為無限(INF)
    //vector可以想成進階版array，下面的宣告代表
    //dist[0]=INF,dist[1]=INF,...,dist[V-1]=INF
    vector<int> dist(V, INF);

    //將起始點放入priority queue並初始化
    //make_pair(distance,vertex)
    //將起始點設定為距離0
    pq.push(make_pair(0,src));
    dist[src]=0;

    //持續loop直到priority queue為空
    while(!pq.empty()){

        //第一個vertex一定是起始點且他距離是0
        //pair的內容是(distance,vertex)
        //pair的第一項內容是距離(distance or weight)
        //pair的第二項內容是點(vertex)

        int u = pq.top().second;//取出vertex
        pq.pop();//取出後從pq移除

        //利用迭代器去走訪list
        list<pair<int,int>>::iterator i;
        //走訪當前vertex u的相鄰串列(走訪目前u能到的點)
        for(i = adj[u].begin();i!=adj[u].end();++i){

            int v = (*i).first;//u能到v點
            int weight = (*i).second;//u到v點的距離

            //如果從(起始點 ->u -> v)的距離小於目前所記錄 (起始點-> v) 的距離
            //代表找到更短的路徑，更新目前到該點最短距離
            //並將(distance,vertex)加入priority queue，等到迴圈結束再來評估下一步要前往哪個vertex(挑最小距離走)
            if(dist[v] > dist[u]+weight){
                dist[v] = dist[u]+weight;
                pq.push(make_pair(dist[v],v));
            }
        }

    }

    //迴圈結束後代表已經記錄完所有點的距離
    //印出
     printf("Vertex Distance from Source\n");
    for(int i = 0; i < V; ++i){
        printf("%d \t\t %d\n",i,dist[i]);
    }
}
int main()
{
    int V = 8;//有8個點
    Graph g(V);//創建圖

    //為點加上邊
    g.addEdge(0, 1, 1);
    g.addEdge(0, 6, 1);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 7, 1);
    g.addEdge(4, 0, 2);
    g.addEdge(4, 5, 1);
    g.addEdge(5, 2, 1);
    g.addEdge(6, 4, 4);
    g.addEdge(6, 7, 3);
    g.addEdge(7, 4, 2);
    g.addEdge(7, 5, 2);
    //從0開始走訪並印出
    g.shortestPath(0);

    return 0;
}