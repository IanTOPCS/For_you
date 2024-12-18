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

int nodeNum{0}, beginNode{0};

int **get_sor(void);
int minDis(int *distance = nullptr, bool *vis = nullptr);
void dijkstra(int **graph = nullptr, int beginNode = 0);

int main(void){
    int **sor = get_sor();

    //debug 來源資料查看
    // for(int i = 0; i<nodeNum+1; i++){
    //     for(int j = 0; j<nodeNum+1; j++){
    //         cout<<sor[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    dijkstra(sor, beginNode);
    return 0;
}

int minDis(int *distance, bool *vis){
    int minIndex{INT_MAX}, nextDis{INT_MAX};
    for(int i = 0; i<(nodeNum+1); i++){
        if((vis[i] == false) && (distance[i] < nextDis)){
            nextDis = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int **graph, int beginNode){
    int *distance = new int[nodeNum+1];
    bool *vis = new bool[nodeNum+1];
    for(int i = 0; i<(nodeNum+1); i++) {
        distance[i] = INT_MAX;
        vis[i] = false;
    }
    distance[beginNode] = 0;
    for(int i = 0; i<(nodeNum+1); i++){
        int nextNode = minDis(distance, vis);

        if(nextNode == INT_MAX){
            cout<<"Not connect component"<<endl;
            return;
        }

        // cout<<"nextNode: "<<nextNode<<endl;
        vis[nextNode] = true;
        for(int j = 0; j<(nodeNum+1); j++){
            if((vis[j] == false) && (graph[nextNode][j] != 0) 
                && (distance[nextNode] != INT_MAX) 
                && (distance[nextNode] + graph[nextNode][j] < distance[j])){
                    distance[j] = distance[nextNode] + graph[nextNode][j];
            }
        }
    }

    for(int i = 0; i<(nodeNum+1); i++){
        cout<<i<<": "<<distance[i]<<endl;
    }
    return;
}

int** get_sor(void){
    myList *sor = new myList();
    cin>>beginNode;
    int u{0}, v{0}, w{0};
    int tmpMax{0};
    while(cin>>u>>v>>w){
        sor->push(new node(u, v, w));
        tmpMax = max(u, v);
        if(tmpMax > nodeNum) nodeNum = tmpMax;
    }

    int **ans = new int*[nodeNum+1];
    for(int i = 0; i<nodeNum+1; i++) ans[i] = new int[nodeNum+1];
    for(int i = 0; i<(nodeNum+1); i++){
        for(int j = 0; j<(nodeNum+1); j++){
            ans[i][j] = 0;
        }
    }
    
    node *view = sor->head;
    while(view != nullptr){
        ans[view->u][view->v] = view->w;
        view = view->next;
    }

    return ans;
}

////////////////////////
/*
0
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10 
5 6 2
6 7 1
6 8 6
7 8 7
*/

/*
0: 0
1: 4
2: 12
3: 19
4: 28
5: 16
6: 18
7: 8
8: 14
*/
////////////////////////