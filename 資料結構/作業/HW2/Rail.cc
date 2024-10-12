# include <bits/stdc++.h>
using namespace std;

class myVector{                             // 手刻 vector
public:
    int size;                               // 單列長度
    int lenSize;                            // 陣列列數
    int **data;
    int *source;
    ~myVector();
    myVector();
    bool one_empty();                       // 單列是否為空
    bool all_empty();                       // 全部列是否為空
    void push_back_one(int);
    void push_back_len();
    void print_data();
    void print_source();
    int back_one();
    void pop_back_one();
};

void myVector::print_source(){
    for(int i = 0; i<(this->size); i++){
        cout<<(this->source[i])<<" ";
    }
    cout<<endl;
}

void myVector::pop_back_one(){
    (this->size)--;
    int *tmp = new int[(this->size)];
    for(int i = 0; i<(this->size); i++){
        tmp[i] = this->source[i];
    }
    delete[] this->source;
    this->source = tmp;
}

int myVector::back_one(){
    return (this->source[(this->size)-1]);
}

void myVector::push_back_len(){
    for(int i = 0; i<this->size; i++){
        (this->data)[this->lenSize][i] = this->source[i];
    }
    (this->lenSize)++;
}

void myVector::print_data(){
    for(int i = 0; i<(this->lenSize); i++){
        for(int j = 0; j<(this->size); j++){
            cout<<(this->data[i][j])<<" ";
        }
        cout<<endl;
    }
}

void myVector::push_back_one(int num){
    (this->source)[this->size] = num;
    (this->size)++;
}

myVector::myVector(){
    this->size = 0;
    this->lenSize = 0;
    this->data = nullptr;
    this->source = nullptr;
}

myVector::~myVector(){
    if(this->data == nullptr) delete this->data;
    else{
        for(int i = 0; i<this->size; i++){
            delete[] this->data[i];
        }
        delete this->data;
    }
    if(this->source == nullptr) delete this->source;
    else delete[] this->source;
}

bool myVector::one_empty(){
    if (this->size == 0) return true;
    return false;
}

bool myVector::all_empty(){
    if (this->lenSize == 0) return true;
    return false;
}

int fab(int);

int main(void){
    int num{0};cin>>num;
    myVector all_posible;

    all_posible.data = new int*[fab(num)];     // 暴力窮舉所有排列可能時需要的容量數
    for(int i = 0; i<fab(num); i++){
        all_posible.data[i] = new int[num];
    }
    all_posible.source = new int[num];
    
    

    return 0;
}

int fab(int num){                               // 一開始要動態多少陣列的來源
    int ans{1};
    for(int i = 1; i<=num; i++){
        ans *= i;
    }
    return ans;
}