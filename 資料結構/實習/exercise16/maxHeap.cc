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
    int index = ++(*size);
    while((index != 1) && (value > heap[index/2])){
        heap[index] = heap[index/2];
        index /= 2;
    }
    heap[index] = value;
}

void pop(int *size){
    int max_val = heap[1];
    int last_val = heap[(*size)--];
    int parent{1}, child{2};
    while(child <= *size){
        if((child < *size) && (heap[child] < heap[child+1])) child++;
        if(last_val >= heap[child]) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = last_val;
    return;
}

/*
10 15 14 20 2 19
2
*/