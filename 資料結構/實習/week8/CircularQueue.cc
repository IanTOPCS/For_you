# include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int value;
    Node *next;
    Node(int value=0, Node *next = nullptr);
};

Node::Node(int value, Node *next){
    this->value = value;
    this->next = next;
}

class myQueue{
public:
    Node *head;
    Node *tail;
    int cnt;
    int size;
    myQueue(int size=0);
    ~myQueue();
    void push(Node *node = nullptr);
    void pop();
    bool isEmpty();
    bool isFull();
    void print();
    int getHead();
};

int myQueue::getHead(){
    if(this->isEmpty()) return -1;
    return this->head->value;
}

myQueue::~myQueue(){
    while(!(this->isEmpty())) this->pop();
    this->tail = nullptr;
    this->head = nullptr;
    this->cnt = 0;
    this->size = 0;
}

void myQueue::push(Node *node){
    if(isFull()) return;
    if(this->head == nullptr){
        this->head = node;
        this->tail = node;
        node->next = nullptr;
        (this->cnt)++;
    }
    else{
        this->tail->next = node;
        this->tail = node;
        node->next = nullptr;
        (this->cnt)++;
    }
}

void myQueue::pop(){
    if(isEmpty()) return;
    Node *temp = this->head;
    this->head = this->head->next;
    delete temp;
    (this->cnt)--;
}

myQueue::myQueue(int size){
    if(size == 0){
        this->tail = nullptr;
        this->head = nullptr;
        this->cnt = 0;
        this->size = 0;
    }
    else{
        this->size = size;
        this->head = nullptr;
        this->tail = this->head;
        this->cnt = 0;  
    }
}

bool myQueue::isEmpty(){
    if(this->cnt <= 0) return true;
    return false;
}

bool myQueue::isFull(){
    if((this->cnt) >= (this->size)) return true;
    return false;
}

void myQueue::print(){
    Node *tmp = this->head;
    while(tmp != nullptr){
        cout<<(tmp->value)<<" ";
        tmp = tmp->next;
    }
    cout<<endl;
}

int main(void){
    ios::sync_with_stdio(0), cin.tie(0);
    int size{0}; cin>>size;
    myQueue sor(--size);
    int pos{0};
    while(cin>>pos){
        if(pos == -1) break;
        if(pos == 0){
            if(sor.isEmpty()){
                cout<<"EMPTY"<<endl;
                continue;
            } 
            cout<<sor.getHead()<<endl;
            sor.pop();
        }
        else if(pos == 1){
            int value{0};cin>>value;
            if(sor.isFull()){
                cout<<"FULL"<<endl;
                continue;
            } 
            Node *tmp = new Node(value);
            sor.push(tmp);
        }
    }
    return 0;
}

/*
3
1 2
1 3
1 4
1 5
0
0
1 5
0
0
0
-1
*/