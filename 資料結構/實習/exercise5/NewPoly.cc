# include <bits/stdc++.h>
using namespace std;

class poly{
public:
    double coef;
    int expon;
    poly();
};

poly::poly(){
    this->coef = 0.0;
    this->expon = 0;
}

int Add(poly*, int, int, int, int, int, int);

poly *sor = new poly[10000];
int main(void){
    int BeginEnd[10000]{0};
    int index{0};
    int degree{0}, indexCnt{0};
    int row{0};
    while((cin>>degree) && degree!= EOF){
        BeginEnd[indexCnt++] = index;
        for(int j = 0; j<degree; j++){
            cin>>sor[index].coef;
            index++;
        }
        index -= degree;
        for(int j = 0; j<degree; j++){
            cin>>sor[index].expon;
            index++;
        }
        BeginEnd[indexCnt++] = (index-1);
        row++;
    }

    //Debug
    //for(int i = 0; i<indexCnt; i++){
    //    cout<<BeginEnd[i]<<endl;
    //}
    // for(int i = 0; i<index; i++){
    //     cout<<sor[i].coef<<' '<<sor[i].expon<<" "<<endl;
    // }
    // for(int i = 0; i<(row*2); i++){
    //     cout<<BeginEnd[i]<<endl;
    // }


    int ansEnd = BeginEnd[(row*2)-1]+1;
    int ansStart = ansEnd;
    int upStart = ansStart;
    if(row > 1){
        ansEnd = Add(sor, BeginEnd[0], BeginEnd[1], BeginEnd[2], BeginEnd[3], ansStart, ansEnd);
        upStart = ansStart;
        ansStart = ansEnd;
        // cout<<"DE "<<upStart<<" "<<ansEnd<<endl;                    //印出位置degug
    }
    for(int i = 4; i<(row*2); i+=2){
        ansEnd = Add(sor, BeginEnd[i], BeginEnd[i+1], upStart, (ansEnd-1), ansStart, ansEnd);
        if(i != ((row-1)*2)){
            upStart = ansStart;
            ansStart = ansEnd;
            // cout<<"DE "<<upStart<<" "<<ansEnd<<endl;            //印出位置degug
        }
        // if(i == ((row-1)*2)){                                   //印出位置degug
        //     cout<<"DE "<<ansStart<<" "<<ansEnd<<endl;
        // }
    }

    cout<<ansEnd-ansStart<<endl;
    for(int i = ansStart; i<ansEnd; i++){                       //結果
        cout<<sor[i].coef<<' ';
    }
    cout<<endl;
    for(int i = ansStart; i<ansEnd; i++){
        cout<<sor[i].expon<<' ';
    }
    cout<<endl;
    delete[] BeginEnd;
    delete[] sor;
    return 0;
}

int Add(poly* sor, int AS, int AE, int BS, int BE, int ansStart, int ansEnd){
    while((AS <= AE) && (BS <= BE)){
        if(sor[AS].expon > sor[BS].expon){
            sor[ansEnd].coef = sor[AS].coef;
            sor[ansEnd].expon = sor[AS].expon;
            AS++; ansEnd++;
        }
        else if(sor[AS].expon < sor[BS].expon){
            sor[ansEnd].coef = sor[BS].coef;
            sor[ansEnd].expon = sor[BS].expon;
            BS++; ansEnd++;
        }
        else{
            sor[ansEnd].coef = sor[AS].coef + sor[BS].coef;
            sor[ansEnd].expon = sor[AS].expon;
            AS++; BS++; ansEnd++;
        }
    }
    while(AS <= AE){
        sor[ansEnd].coef = sor[AS].coef;
        sor[ansEnd].expon = sor[AS].expon;
        AS++; ansEnd++;
    }
    while(BS <= BE){
        sor[ansEnd].coef = sor[BS].coef;
        sor[ansEnd].expon = sor[BS].expon;
        BS++; ansEnd++;
    }
    return ansEnd;
}

/*
2
2 1
1000 0
4
1 10 3 1
4 3 2 0
1
-1
10
5
3 4 7 8 10
5 4 3 2 1
*/
