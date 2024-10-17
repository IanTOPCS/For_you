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

class myStack{
public:
    int size;                           // 最多可以存放多少在此stack
    int cnt;                            // 目前有多少存在值於stack
    Node *top;                          // 指到 linked list 的最前面當作top
    myStack(int size=0);
    void push(Node *node = nullptr);
    void pop();
    bool isEmpty();
    bool isFull();
    void print();
    int getTop();
};

int myStack::getTop(){
    if(isEmpty()) return -1;
    return this->top->value;
}

void myStack::print(){
    Node *temp = this->top;
    while(temp!=nullptr){
        cout<<temp->value<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

myStack::myStack(int size){
    this->size = size;
    this->top = nullptr;
    this->cnt = -1;
}

void myStack::push(Node *node){
    if(isFull()) return;
    node->next = this->top;
    this->top = node;
    this->cnt++;
}

void myStack::pop(){
    if(isEmpty()) return;
    Node *temp = this->top;
    this->top = this->top->next;
    delete temp;
    (this->cnt)--;
}

bool myStack::isEmpty(){
    if((this->cnt) < 0) return true;
    return false;
}

bool myStack::isFull(){
    if((this->cnt) == (this->size)-1) return true;
    return false;
}

int main(void){
    int myStackSize{0};cin>>myStackSize;
    myStack myStack(myStackSize);
    for(int i = 0; i<myStackSize; i++){
        Node *tmp = new Node(i);
        myStack.push(tmp);
    }
    myStack.print();
    while(!myStack.isEmpty()){
        cout<<myStack.getTop()<<endl;
        myStack.pop();
    } 
    if(myStack.isEmpty()) cout<<"yes"<<endl;
    myStack.print();
    return 0;
}