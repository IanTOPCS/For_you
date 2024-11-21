# include <bits/stdc++.h>
using namespace std;

class node{                                                         // 題目要求
public:
    int data;
    node* llink;
    node* rlink;
    node(int data=0, node* llink=nullptr, node* rlink=nullptr); 
};

node::node(int data, node* llink, node* rlink){                     // 題目要求
    this->data = data;
    this->llink = llink;
    this->rlink = rlink;
}

class myLink{                                                       // 題目要求
public:
    node* head;
    node* tail;
    myLink(node* head=nullptr, node* tail=nullptr){
        this->head = head;
        this->tail = tail;
    }
};

void push(myLink *sor = nullptr, node *node = nullptr);             // 獨立於題目外，動態增加數列長度
int isArithmetic(myLink *sor = nullptr);
myLink *get_Link();
void print(myLink *sor = nullptr);

int main(void){
    srand(static_cast<unsigned>(time(nullptr)));                    // 以亂數測非等差
    myLink *sor = get_Link();                                       // 拿到動態數列(可能等差、非等差)
    cout<<"The input source is : ";
    print(sor);                                                     // 印出動態數列
    cout<<"The result is : "<<isArithmetic(sor)<<endl;              // 判斷是否為等差(1 是， 0 否)
    return 0;
}

void push(myLink *sor, node *node){
    if(sor->tail == nullptr){
        sor->head = node;
        sor->tail = node;
    }
    else{
        sor->tail->rlink = node;
        node->llink = sor->tail;
        sor->tail = node;
    }
    return;
}

int isArithmetic(myLink *sor){                                      // 判斷是否為等差
    node *tmp = sor->head;
    int diff = (tmp->data - tmp->rlink->data);
    while(tmp->rlink != nullptr){
        if((tmp->data - tmp->rlink->data) != diff) return 0;
        tmp = tmp->rlink;
    }
    return 1;
}

myLink *get_Link(){
    cout<<"Please input the size of the link : ";
    int size{0};
    cin>>size;
    cout<<"Please input the begin of the link : ";
    int begin{0};
    cin>>begin;
    cout<<"Please input the diff of the link : ";
    int diff{0};
    cin>>diff;
    myLink *ans = new myLink();

    for(int i = 0; i<size; i++){                                    // 測試等差
        push(ans, new node(begin + i*diff));
    }

    // for(int i = 0; i<size; i++){                                    // 測試非等差
    //     push(ans, new node(begin + (rand()%100)));
    // }

    return ans;
}

void print(myLink *sor){                                            // 確認數據資料
    node *tmp = sor->head;
    while(tmp != nullptr){
        cout<<tmp->data<<" ";
        tmp = tmp->rlink;
    }
    cout<<endl;
    return;
}

////////////////////////
/*
10
6
3
*/

/*
1
*/
////////////////////////