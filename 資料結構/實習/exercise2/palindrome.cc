# include <bits/stdc++.h>
using namespace std;

bool par(string, int, int);

int main(void){
    string sor = "";
    cin>>sor;
    int mid = ceil(sor.size()/2);               //�j��W�w���W��
    cout<<par(sor, mid, 0)<<endl;
    return 0;
}

bool par(string sor, int mid, int index){
    if(index == mid) return 1;                  //�p�G�줤���S�h�X�j��A�N�O�e�����ŦX�W�h
    if(sor[index] == sor[sor.size()-1-index]){  //�p�G�ŦX�^��W�h�A�N�~�򻼰j
        return par(sor, mid, index+1);
    }
    return 0;                                   //���ŦX�N�h�X
}
