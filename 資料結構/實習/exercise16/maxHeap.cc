# include <bits/stdc++.h>
using namespace std;

int heap[10000]{0};

void push(int, int*);
void pop(int*);

int main(void){
    int size{0};
    string sor{""};
    getline(cin, sor);
    string tmp = {""};
    for(int i = 0; i<sor.size(); i++){
        if ((sor[i] == ' ') || (sor[i] == EOF)){
            push(stoi(tmp), &size);
            tmp = {""};
            continue;
        }
        tmp += sor[i];
    }
    push(stoi(tmp), &size);


    int pop_round{0};
    cin>>pop_round;
    for(int i = 0; i<pop_round; i++){
        pop(&size);
    }

    for(int i = 0; i<size; i++){
        cout<<"("<<(i+1)<<", "<<heap[i+1]<<") ";
    }

    return 0;
}

void push(int value, int *size){
    int index = ++(*size);                              // 增加填值空間(1 base)
    while((index != 1) && (value > heap[index/2])){     // 非 root(有空間調整) 且 比上一層大
        heap[index] = heap[index/2];                    // 下移較小的值(下層調整完畢)
        index /= 2;                                     // 關注上一層
    }
    heap[index] = value;                                // 於正確層數更新填入值
}

void pop(int *size){
    int max_val = heap[1];
    int last_val = heap[(*size)--];
    int parent{1}, child{2};
    while(child <= *size){
        if((child < *size) && (heap[child] < heap[child+1])) child++;   // 兄弟較大
        if(last_val >= heap[child]) break;                              // 找到合適位置
        heap[parent] = heap[child];                                     // 向上覆蓋父節點
        parent = child;                                                 // 關心下一層
        child *= 2;                                                     // 關心下一層
    }
    heap[parent] = last_val;                                            // 更新合適位置值
    return;
}

/*
10 15 14 20 2 19
2
*/