# include <bits/stdc++.h>
using namespace std;

class poly{
public:
    int data;
    poly  *next;
    poly(int d = 0, poly *n = nullptr);
};

poly::poly(int d, poly *n){
    this->data = d;
    this->next = n;
}

class polyRow{
public:
    poly *head;
    poly *tail;
    int size;
    polyRow(poly *h = nullptr, poly *t = nullptr){
        this->head = h;
        this->tail = t;
        this->size = 0;
    }
    void push(poly *node);
    void print();
};

void polyRow::print(){
    poly *tmp{this->head};
    do{
        cout<<tmp->data<<" ";
        tmp = tmp->next;
    }while(tmp != this->tail);
    cout<<endl;
}

void polyRow::push(poly *node){
    if(this->head == nullptr){
        this->head = node;
        this->tail = node;
    }
    else{
        this->tail->next = node;
        this->tail = node;
    }
    (this->size)++;
}

int detection(polyRow *sor = nullptr, int pos = 0);

int main(void){
    polyRow *ans = new polyRow();
    string sor{"\0"}; getline(cin, sor);
    for(int i = 0; i<sor.size(); i++){
        if(sor[i] == ' ') continue;
        string tmp{""};
        while(i < sor.size()){
            if(sor[i] == ' ') break;
            tmp += sor[i];
            i++;
        }
        ans->push(new poly(stoi(tmp)));
    }

    int pos{0}; cin>>pos;
    // ans->print();
    cout<<detection(ans, pos)<<endl;
    
    return 0;
}

int detection(polyRow *sor, int pos){
    if((pos < 0) || (pos >= (sor->size))) return 0;
    poly *cycle{sor->head};
    for(int i = 0; i<pos; i++){
        cycle = cycle->next;
    }
    sor->tail->next = cycle;

    int cnt{0};
    while(cycle != sor->tail){
        cnt++;
        cycle = cycle->next;
    }
    cnt++;
    return cnt;
}

/////////////
/*
3 2 0 -4
1
*/

/*
3
*/
/////////////