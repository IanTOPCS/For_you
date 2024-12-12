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
void prim(int**, int);
int start{0};
edge *record, *pointView = new edge();
int *vis = nullptr;

int main(void){
    int **sor = get_edge();
    prim(sor, start);
    return 0;
}

int** get_edge(){
    edge *ans= new edge();
    cin>>start;
    pointView->push(new node(0, start, start));
    int u{0}, v{0}, w{0};
    int nodeMax{0};
    while(cin>>u>>v>>w){
        int nodeMaxTmp = max(u, v);
        if(nodeMax < nodeMaxTmp) nodeMax = nodeMaxTmp;
        ans->push(new node(w, u, v));
    }
    
    vis = new int[nodeMax+1];

    int **sor = new int*[nodeMax+1];
    for(int i = 0; i<=nodeMax; i++){
        sor[i] = new int[nodeMax+1];
        for(int j = 0; j<=nodeMax; j++){
            sor[i][j] = 0;
        }
        vis[i] = 0;
    }

    node *tmp = ans->head;
    while(tmp != nullptr){
        sor[tmp->u][tmp->v] = tmp->weight;
        sor[tmp->v][tmp->u] = tmp->weight;
        tmp = tmp->next;
    }
    return sor;
}

void prim(int **sor, int start){
    if(vis[start] == 1) return;
    node *view = pointView->head;
    int min_u{INT_MAX}, min_v{INT_MAX}, min_w{INT_MAX};
    while(view != nullptr){
        for(int i = (view->u); i<(sizeof(sor[0])/sizeof(sor[0][0])); i++){
            if(vis[i] == 1) continue;
        }
        view = view->next;
    }

}