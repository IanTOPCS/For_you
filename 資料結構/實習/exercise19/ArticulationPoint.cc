# include <bits/stdc++.h>
using namespace std;

int max_len{0};

class node{
public:
    int data;
    node *next;
    node(int data = 0, node *next = nullptr);
};

node::node(int data, node *next){
    this->data = data;
    this->next = next;
}

class myList{
public:
    node *head;
    node *tail;
    myList(node *head = nullptr, node *tail = nullptr);
    void push(node *node);
    void print();
};

void myList::print(){
    node *tmp = head;
    while(tmp!=nullptr){
        cout<<tmp->data<<" ";
        tmp = tmp->next;
    }
    cout<<endl;
}

myList::myList(node *head, node *tail){
    this->head = head;
    this->tail = tail;
}

void myList::push(node *node){
    if(head == nullptr){
        head = node;
        tail = node;
    }else{
        tail->next = node;
        tail = node;
    }
    return;
}

class vertex{
public:
    int x, y;
    vertex *next;
    vertex(int x = 0, int y = 0, vertex *next = nullptr);
};

vertex::vertex(int x, int y, vertex *next){
    this->x = x;
    this->y = y;
    this->next = next;
}

class vertex_array{
public:
    vertex *head;
    vertex *tail;
    vertex_array(vertex *head = nullptr, vertex *tail = nullptr);
    void push(vertex *vertex = nullptr);
};

vertex_array::vertex_array(vertex *head, vertex *tail){
    this->head = head;
    this->tail = tail;
}

void vertex_array::push(vertex *vertex){
    if(head == nullptr){
        head = vertex;
        tail = vertex;
    }
    else{
        tail->next = vertex;
        tail = vertex;
    }
    return;
}

void dfs(int now, bool *vis, myList *sor, int ban);

void Ap(myList *sor);

myList* get_graph();

int main(void){
    myList *source = get_graph();
    // for(int i = 0; i<max_len+1; i++) source[i].print();
    Ap(source);
    return 0;
}

myList* get_graph(){
    int num1{0}, num2{0}, max_num{0};
    vertex_array *input = new vertex_array();
    while((cin>>num1) && (cin>>num2)){
        input->push(new vertex(num1, num2, nullptr));
        int tmp_max = {num1};
        if(num2 > num1) tmp_max = num2;
        if(tmp_max > max_num) max_num = tmp_max;
    }
    max_len = max_num;
    myList *source = new myList[max_num+1];
    vertex *view = input->head;
    while(view != nullptr){
        source[view->x].push(new node(view->y));
        source[view->y].push(new node(view->x));
        view = view->next;
    }
    return source;
}

void dfs(int now, bool *vis, myList *sor, int ban){
    vis[now] = true;
    node *view = sor[now].head;
    while(view != nullptr){
        if(view->data != ban){
            if(vis[view->data] == false){
                dfs(view->data, vis, sor, ban);
            }
        }
        view = view->next;
    }
    return;
}

void Ap(myList* sor){
    for(int j = 0; j<max_len+1; j++){
        int components{0};
        bool *vis = new bool[max_len+1];
        for(int i = 0; i<max_len+1; i++) vis[i] = false;
        for(int i = 0; i<max_len+1; i++){
            if(i != j){
                if(vis[i] == false){
                    components++;
                    dfs(i, vis, sor, j);
                } 
            }
        }
        if(components > 1){
            cout<<j<<" ";
        }
        delete[] vis;
    }
    return;
}

///////////////////////////////
/*
0 1
1 2
1 3
2 4
3 5
5 6
5 7
6 7
7 8
7 9
*/
/*
1 2 3 5 7
*/
///////////////////////////////

///////////////////////////////
/*
0 1
1 2
1 3d
2 4
3 4
*/
/*
1
*/
///////////////////////////////
