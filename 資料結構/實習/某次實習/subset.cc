# include <bits/stdc++.h>
using namespace std;

void subset(int*, int, int, int*);
bool isEmpty(int*, int);

int main(void){

    int numCnt{0};
    int sor[100000]{0};
    while((cin>>sor[numCnt]) && sor[numCnt]) numCnt++;
    int *choice = new int[numCnt];
    for(int i = 0; i<numCnt; i++) choice[i] = 0;
    subset(sor, 0, numCnt-1, choice);

    delete[] choice;
    return 0;
}

void subset(int* sor, int left, int right, int* choice){
    if(left > right){
        if(isEmpty(choice, right)) cout<<"EMPTY-SET\n";
        else{
            for(int i = 0; i<right+1; i++){
                if(choice[i] == 1) cout<<sor[i]<<" ";
            }
            cout<<endl;
        }
        return;
    }
    choice[left] = 1;
    subset(sor, left+1, right, choice);
    choice[left] = 0;
    subset(sor, left+1, right, choice);
}

bool isEmpty(int* choice, int right){
    for(int i = 0; i<right+1; i++){
        if(choice[i] == 1) return false;
    }
    return true;
}