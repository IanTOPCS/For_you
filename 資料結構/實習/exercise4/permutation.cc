# include <bits/stdc++.h>
using namespace std;

void perm(string, int);
int cnt{0};

int main(void){
    string sor = "";
    cin>>sor;
    sort(sor.begin(), sor.end());
    perm(sor, 0);
    cout<<"Total�G"<<cnt<<endl;
    return 0;
}

void perm(string sor, int index){
    if(index == sor.size()-1){                      //�פ����A���̫��������
        for(int i = 0; i<sor.size(); i++){
            cout<<sor[i];
        }
        cout<<endl;
        cnt++;
    }
    else{
        for(int i = index; i<sor.size(); i++){
            bool boom = false;                      //�P�_�ϧ_�ƹL
            for(int j = index; j<i; j++){           //�e���O�ƹL���A�p�G�e�����P�ڬۦP���r�A�N��w�g��L
                if(sor[i] == sor[j]){
                    boom = true;
                    break;                          //�w�g�T�{�ƹL
                }
            }
            if(boom) continue;                      //�����O�귽�����ƪ���
            swap(sor[i], sor[index]);               //�洫�H���զU�ؤ��P���ƦC�զX
            perm(sor, index+1);                     //�i�J�P�_
            swap(sor[i], sor[index]);               //�N���L�����G��_�A�H��i����U�@���~�򻼰j
        }
    }
}
