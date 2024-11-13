# include <bits/stdc++.h>
using namespace std;

class poly{
public:
    double coef;
    int expon;
    poly *next;
    poly(double c = 0.0, int e = 0, poly *n = nullptr);
};

poly::poly(double c, int e, poly *n){
    this->coef = c;
    this->expon = e;
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

void  polyRow::print(){
    cout<<this->size<<endl;
    poly *tmp = this->head;
    while(tmp != nullptr){
        cout<<tmp->coef<<" ";
        tmp = tmp->next;
    }
    cout<<endl;
    tmp = this->head;
    while(tmp != nullptr){
        cout<<tmp->expon<<" ";
        tmp = tmp->next;
    }
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

polyRow* mul(polyRow *a = nullptr, polyRow *b = nullptr);
polyRow* polyAdd(polyRow *a = nullptr, polyRow *b = nullptr);

int main(void){
    int term{0};
    polyRow *ans = new polyRow();
    ans->push(new poly(1.0, 0));                            // 初始條件，任何數乘一次都是自己，用在第一次迭代
    while(cin>>term){
        polyRow *sor = new polyRow();
        polyRow *coef = new polyRow();
        polyRow *expon = new polyRow();
        for(int i = 0; i<term; i++){
            double c{0}; cin>>c;
            coef->push(new poly(c, 0));
        }
        for(int i = 0; i<term; i++){
            int e{0}; cin>>e;
            expon->push(new poly(1.0, e));
        }
        poly *coefTerm = coef->head;
        poly *exponTerm = expon->head;
        for(int i = 0; i<term; i++){
            sor->push(new poly(coefTerm->coef, exponTerm->expon));
            coefTerm = coefTerm->next;
            exponTerm = exponTerm->next;
        }


        // debug 看輸入格式
        // cout<<"debug"<<endl;
        // sor->print();

        delete coef;
        delete expon;
        ans = mul(ans, sor);
        delete sor;
    }
    ans->print();
    delete ans;
    return 0;
}

polyRow* mul(polyRow *a, polyRow *b){
    polyRow *ans = new polyRow();
    ans->push(new poly(0.0, 0));                            // 初始條件，每列加法，用在第一次迭代
    poly *aTerm = a->head;
    while(aTerm != nullptr){
        poly *bTerm = b->head;
        polyRow *sor = new polyRow();
        while(bTerm != nullptr){
            sor->push(new poly(aTerm->coef*bTerm->coef, aTerm->expon+bTerm->expon));
            bTerm = bTerm->next;
        }
        ans = polyAdd(ans, sor);

        // debug 看每列加完格式
        // cout<<"add"<<endl;
        // ans->print();
        // cout<<endl;

        delete sor;
        aTerm = aTerm->next;
    }
    return ans;
}

polyRow* polyAdd(polyRow *a, polyRow *b){
    polyRow *ans = new polyRow();
    poly *aTerm = a->head;
    poly *bTerm = b->head;
    while(aTerm != nullptr && bTerm != nullptr){
        if(aTerm->expon > bTerm->expon){
            ans->push(new poly(aTerm->coef, aTerm->expon));
            aTerm = aTerm->next;
        }
        else if(aTerm->expon < bTerm->expon){
            ans->push(new poly(bTerm->coef, bTerm->expon));
            bTerm = bTerm->next;
        }
        else{
            double sum{aTerm->coef+bTerm->coef};
            if(sum != 0){
                ans->push(new poly(sum, aTerm->expon));
            }
            aTerm = aTerm->next;
            bTerm = bTerm->next;
        }
    }
    while(aTerm != nullptr){
        if(aTerm->coef != 0){                                       // 排除係數 0
            ans->push(new poly(aTerm->coef, aTerm->expon));
        } 
        aTerm = aTerm->next;
    }
    while(bTerm != nullptr){
        if(bTerm->coef != 0){                                       // 排除係數 0
            ans->push(new poly(bTerm->coef, bTerm->expon));
        } 
        bTerm = bTerm->next;
    }
    return ans;
}

/////////////////////////////////////////////////////////////////////////////////
/*
2
2 1
4 3
3
1 3 1
4 2 0
*/

/*
6
2 1 6 3 2 1
8 7 6 5 4 3
*/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
/*
2
2 1
4 3
1
1
0
3
1 3 1
4 2 0
*/

/*
6
2 1 6 3 2 1
8 7 6 5 4 3
*/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
/*
2
2 1
4 3
3
1 3 1
4 2 0
2
2 3
7 5
*/

/*
8
4 2 18 9 22 11 6 3
15 14 13 12 11 10 9 8
*/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
/*
2
2 3
1 0
2
-2 -1
1 0
*/

/*
3
-4 -8 -3
2 1 0
*/
/////////////////////////////////////////////////////////////////////////////////
  