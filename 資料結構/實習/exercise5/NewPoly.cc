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
    while((cin>>degree) && degree!= EOF){                                                           // 輸入最多幾項
        BeginEnd[indexCnt++] = index;                                                               // 存入此方程式開頭的位置
        for(int j = 0; j<degree; j++){                                                              // 輸入係數
            cin>>sor[index].coef;
            index++;
        }
        index -= degree;                                                                            // 為了對齊陣列
        for(int j = 0; j<degree; j++){
            cin>>sor[index].expon;                                                                  // 輸入指數
            index++;
        }
        BeginEnd[indexCnt++] = (index-1);                                                           // 存入方程式結束位置
        row++;                                                                                      // 有幾列方程式
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


    int ansEnd = BeginEnd[(row*2)-1]+1;                                                             // 先定義答案區間結束位置為最後方程式輸入完的位置之下一個
    int ansStart = ansEnd;                                                                          // 一開始還沒運算，開始==結束
    int upStart = ansStart;                                                                         // 記得上個起始位置，
    if(row > 1){                                                                                    // 起碼有兩列方程式才可相加
        ansEnd = Add(sor, BeginEnd[0], BeginEnd[1], BeginEnd[2], BeginEnd[3], ansStart, ansEnd);    // 第一、二列相加
        upStart = ansStart;                                                                         // 記好上一個起始位置
        ansStart = ansEnd;                                                                          // 下一刻的開始是上一個的結束點
    }
    for(int i = 4; i<(row*2); i+=2){                                                                // 每列（開始、結束）兩個，故跌代兩倍列數
        ansEnd = Add(sor, BeginEnd[i], BeginEnd[i+1], upStart, (ansEnd-1), ansStart, ansEnd);       // 新的一列與上個結果相加，跌代結果
        if(i != ((row-1)*2)){
            upStart = ansStart;
            ansStart = ansEnd;
            // cout<<"DE "<<upStart<<" "<<ansEnd<<endl;            //�L�X��mdegug
        }
        // if(i == ((row-1)*2)){                                   //�L�X��mdegug
        //     cout<<"DE "<<ansStart<<" "<<ansEnd<<endl;
        // }
    }

    cout<<ansEnd-ansStart<<endl;
    for(int i = ansStart; i<ansEnd; i++){                       //���G
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
    while((AS <= AE) && (BS <= BE)){                        // 先確定兩方程式都還位於區間內
        if(sor[AS].expon > sor[BS].expon){                  // 指數由高存到低，目前A較大
            sor[ansEnd].coef = sor[AS].coef;
            sor[ansEnd].expon = sor[AS].expon;
            AS++; ansEnd++;                                 // 存現在的A進End，關注下個A
        }
        else if(sor[AS].expon < sor[BS].expon){
            sor[ansEnd].coef = sor[BS].coef;
            sor[ansEnd].expon = sor[BS].expon;
            BS++; ansEnd++;                                 // 關注下個B
        }
        else{
            sor[ansEnd].coef = sor[AS].coef + sor[BS].coef; // 兩個指數相同，係數相加
            sor[ansEnd].expon = sor[AS].expon;
            AS++; BS++; ansEnd++;                           // 因為相同，全部往後
        }
    }
    while(AS <= AE){                                        // B做完了，A還沒結束，直接將A填入答案
        sor[ansEnd].coef = sor[AS].coef;
        sor[ansEnd].expon = sor[AS].expon;
        AS++; ansEnd++;
    }
    while(BS <= BE){                                        // A做完了，B還沒結束，將B填入答案
        sor[ansEnd].coef = sor[BS].coef;
        sor[ansEnd].expon = sor[BS].expon;
        BS++; ansEnd++;
    }
    return ansEnd;                                          // 回傳結束位置
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
