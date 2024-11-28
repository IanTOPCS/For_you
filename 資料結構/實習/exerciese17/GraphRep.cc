# include <iostream>
using namespace std;

class vertex{
public:
    int x;
    int y;
    vertex *next;
    vertex(int x = 0, int y = 0, vertex *next = nullptr);
};

vertex::vertex(int x, int y, vertex *next){
    this->x = x;
    this->y = y;
    this->next = next;
}

class edge{
public:
    vertex *start;
    vertex *end;
    edge(vertex *start = nullptr, vertex *end = nullptr);
    void push(vertex *v);
};

edge::edge(vertex *start, vertex *end){
    this->start = start;
    this->end = end;
}

void edge::push(vertex *v){
    if((this->start) == nullptr){
        start = v;
        end = v;
    }
    else{
        end->next = v;
        end = v;
    }
    return;
}

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

class list{
public:
    node *head;
    node *tail;
    list(node *head = nullptr, node *tail = nullptr);
    void add(node *n);
    void push(node *n);
    void print();
};

void list::add(node *n){
    if(head == nullptr){
        head = n;
        tail = n;
        return;
    }

    node *tmp = head;
    while(tmp->next != nullptr){
        if((tmp->data < n->data) && (tmp->next->data > n->data)){
            node *insert = tmp->next;
            tmp->next = n;
            n->next = insert;
            return;
        }
        tmp = tmp->next;
    }
    tmp = head;
    while(tmp != nullptr){
        if(tmp->data == n->data){
            delete n;
            return;
        }
        tmp = tmp->next;
    }
    tail->next = n;
    tail = n;
    return;
}

void list::print(){
    node *tmp = head;
    while(tmp != nullptr){
        cout<<tmp->data<<" -> ";
        tmp = tmp->next;
    }
    cout<<"NULL"<<endl;
    return;
}

void list::push(node *n){
    if(this->head == nullptr){
        head = n;
        tail = n;
    }
    else{
        tail->next = n;
        tail = n;
    }
    return;
};

list::list(node *head, node *tail){
    this->head = head;
    this->tail = tail;
}

edge *get_edge();
int **get_matrix(edge*);
void print_matrix(int **);
list* get_list(int**);
void print_list(list*);

int main(void){
    edge *sor = get_edge();
    int **matrix = get_matrix(sor);
    print_matrix(matrix);
    list* ans = get_list(matrix);
    print_list(ans);
    return 0;
}

void print_list(list *sor){
    int size = sizeof(sor)/sizeof(sor[0]);
    for(int i = 0; i<size; i++){
        cout<<i<<": ";
        sor[i].print();
    }
    return;
}

void print_matrix(int **sor){
    cout<<"adjacency matrix:"<<endl;
    int size = sizeof(sor);
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            cout<<sor[i][j]<<" ";
        }
        cout<<endl;
    }
    return;
}

edge *get_edge(){
    edge *sor = new edge();
    int x{0}, y{0};
    while(cin>>x>>y){
        sor->push(new vertex(x, y));
    }
    return sor;
}

list* get_list(int **sor){
    int size = sizeof(sor);
    list *ans = new list[size];
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            if(sor[i][j] == 1){
                ans->add(new node(i));
                ans->add(new node(j));
                ans[i].push(new node(j));
                ans[j].push(new node(i));
            }
        }
    }
    return ans;
}

int **get_matrix(edge *sor){
    int max_val{0}, tmp_max{0};
    vertex *view = sor->start;
    while(view != nullptr){
        if(view->x > view->y) tmp_max = view->x;
        else tmp_max = view->y;
        if(tmp_max > max_val) max_val = tmp_max;
        view = view->next;
    }

    int **matrix = new int*[max_val+1];
    for(int i = 0; i<max_val+1; i++){
        matrix[i] = new int[max_val+1];
    }

    for(int i = 0; i<max_val+1; i++){
        for(int j = 0; j<max_val+1; j++){
            matrix[i][j] = 0;
        }
    }
    view = sor->start;
    while(view != nullptr){
        matrix[view->x][view->y] = 1;
        matrix[view->y][view->x] = 1;
        view = view->next;
    }

    return matrix;
}

//////////////////////////////
/*
0 3
1 2
1 3
2 3
*/