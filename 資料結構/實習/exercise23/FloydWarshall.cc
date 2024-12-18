# include <bits/stdc++.h>
using namespace std;

class node{
public:
    int u;
    int v;
    int w;
    node *next;
    node(int u = 0, int v = 0, int w = 0, node *next = nullptr);
};

node::node(int u, int v, int w, node *next){
    this->u = u;
    this->v = v;
    this->w = w;
    this->next = next;
}

class myList{
public:
    node *head;
    node *tail;
    myList(node *head = nullptr, node *tail = nullptr);
    void push(node *node = nullptr);
};

myList::myList(node *head, node *tail){
    this->head = head;
    this->tail = tail;
}

void myList::push(node *node){
    if(this->head == nullptr){
        this->head = node;
        this->tail = node;
    }
    else{
        this->tail->next = node;
        this->tail = node;
    }
    return;
}

int nodeNum{0};

int** get_sor(void);
void floydWarshall(int **graph = nullptr);

int main(void){
    int **sor = get_sor();

    // debug 來源資料查看
    // for(int i = 0; i<nodeNum+1; i++){
    //     for(int j = 0; j<nodeNum+1; j++){
    //         cout<<sor[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    floydWarshall(sor);  

    return 0;
}

void floydWarshall(int **graph){
    for(int k = 0; k<(nodeNum+1); k++){
        for(int i = 0; i<(nodeNum+1); i++){
            for(int j = 0; j<(nodeNum+1); j++){
                if((graph[i][k] != INT_MAX) && (graph[k][j] != INT_MAX) && (graph[i][j] > graph[i][k] + graph[k][j])){
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }

    for(int k = 0; k<(nodeNum+1); k++){
        for(int i = 0; i<(nodeNum+1); i++){
            for(int j = 0; j<(nodeNum+1); j++){
                // 小心 underflow, 不可以 INT_MIN
                if((graph[i][k] != INT_MAX) && (graph[k][j] != INT_MAX) && (graph[i][j] > graph[i][k] + graph[k][j])){
                    graph[i][j] = -404;
                }
            }
        }
    }

    for(int i = 0; i<(nodeNum+1); i++){
        for(int j = 0; j<(nodeNum+1); j++){
            if(graph[i][j] == INT_MAX){
                cout<<"INF ";
            }
            else if(graph[i][j] == -404){
                cout<<"-INF ";
            }
            else{
                cout<<graph[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    return;
}

int** get_sor(void){
    int beginNode{0}; cin>>beginNode;
    myList *sor = new myList();
    int u{0}, v{0}, w{0};
    int tmpMax{0};
    while(cin>>u>>v>>w){
        sor->push(new node(u, v, w));
        tmpMax = max(u, v);
        if(tmpMax > nodeNum) nodeNum = tmpMax;
    }

    int **ans = new int*[nodeNum+1];
    for(int i = 0; i<(nodeNum+1); i++){
        ans[i] = new int[nodeNum+1];
    }

    for(int i = 0; i<(nodeNum+1); i++){
        for(int j = 0; j<(nodeNum+1); j++){
            if(i == j) ans[i][j] = 0;
            else ans[i][j] = INT_MAX;
        }
    }
    node *view = sor->head;
    while(view != nullptr){
        ans[view->u][view->v] = view->w;
        view = view->next;
    }

    return ans;
}

//////////////////////
/*
0
0 1 5
0 3 10
1 2 3
2 3 1
3 1 -1
*/

/*
0 5 8 9
INF 0 3 4
INF 0 0 1
INF -1 2 0
*/
//////////////////////

//////////////////////
/*
0
0 1 5
0 3 10
1 2 3
2 1 -4
2 3 1
3 1 1
*/

/*
0 -INF -INF -INF
INF -INF -INF -INF
INF -INF -INF -INF
INF -INF -INF -INF
*/
//////////////////////