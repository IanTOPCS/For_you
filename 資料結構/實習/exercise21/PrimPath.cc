# include <bits/stdc++.h>
using namespace std;

class node{
public:
    node *next;
    int weight;
    int u;
    int v;
    node(int weight=0, int u=0, int v=0, node *next = nullptr){
        this->weight = weight;
        this->u = u;
        this->v = v;
        this->next = next;
    }
};

class edge{
public:
    node *head;
    node *tail;
    int sz;
    edge(node *head = nullptr, node *tail = nullptr, int sz = 0){
        this->head = head;
        this->tail = tail;
        this->sz = sz;
    }
    void push(node *node){
        if(this->head == nullptr){
            this->head = node;
            this->tail = node;
            (this->sz)++;
        }
        else{
            this->tail->next = node;
            this->tail = node;
            (this->sz)++;
        }
        return;
    }
};

int** get_edge();
void prim(int**, int, int);
int start{0};
edge *record, *pointView = new edge();
int *vis = nullptr;
int nodeMax = 0;  // 新增全局變量記錄節點數量

int main(void){
    int **sor = get_edge();
    record = new edge();  // 初始化 record
    
    // 從起始節點開始生成最小生成樹
    prim(sor, start, nodeMax);

    int w_sum{0};
    node *tmp = record->head;
    while(tmp != nullptr){
        cout<<"("<<tmp->u<<" "<<tmp->v<<") ";
        w_sum += tmp->weight;
        tmp = tmp->next;
    }
    cout<<endl<<w_sum<<endl;
    return 0;
}

int** get_edge(){
    edge *ans= new edge();
    cin>>start;
    pointView->push(new node(0, start, start));
    int u{0}, v{0}, w{0};
    nodeMax = 0;  // 初始化 nodeMax
    while(cin>>u>>v>>w){
        int nodeMaxTmp = max(u, v);
        if(nodeMax < nodeMaxTmp) nodeMax = nodeMaxTmp;
        ans->push(new node(w, u, v));
    }
    
    vis = new int[nodeMax+1]();  // 使用 () 初始化為 0

    int **sor = new int*[nodeMax+1];
    for(int i = 0; i<=nodeMax; i++){
        sor[i] = new int[nodeMax+1]();  // 使用 () 初始化為 0
    }

    node *tmp = ans->head;
    while(tmp != nullptr){
        sor[tmp->u][tmp->v] = tmp->weight;
        sor[tmp->v][tmp->u] = tmp->weight;
        tmp = tmp->next;
    }
    return sor;
}

void prim(int **sor, int start, int totalNodes){
    vis[start] = 1;  // 標記起始節點已訪問

    // 找尋當前已訪問節點能連接的最小權重邊
    int min_u{-1}, min_v{-1}, min_w{INT_MAX};
    for(int i = 0; i <= totalNodes; i++) {
        if(vis[i] == 1) {  // 對已訪問的節點
            for(int j = 0; j <= totalNodes; j++) {
                if(vis[j] == 0 && sor[i][j] > 0 && sor[i][j] < min_w) {
                    min_w = sor[i][j];
                    min_u = i;
                    min_v = j;
                }
            }
        }
    }

    // 如果找到最小權重邊
    if(min_u != -1 && min_v != -1) {
        record->push(new node(min_w, min_u, min_v));
        
        // 遞迴繼續生成樹
        prim(sor, min_v, totalNodes);
    }
}

/*
0
0 1 4
0 7 8
1 7 11
1 2 8
2 3 7
2 5 4
2 8 2
6 7 1
6 8 6
7 8 7
3 5 14
3 4 9
4 5 10
5 6 2
*/