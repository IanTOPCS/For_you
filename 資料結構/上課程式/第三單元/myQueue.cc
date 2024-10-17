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
    int size{0}; cin>>size;
    myQueue sor(size);
    for(int i = 0; i<size; i++){
        cout<<sor.cnt<<endl;
        Node *tmp = new Node(i);
        sor.push(tmp);
    }
    sor.print();
    while(!sor.isEmpty()){
        cout<<sor.getHead()<<endl;
        sor.pop();
    }
    return 0;
}