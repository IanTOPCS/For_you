#include<stdio.h>

typedef struct{
    float coef;
    int expon;
}Ploy;
int start[1000],finish[1000];
int avail;

void tail(Ploy *sor, int oldhead, int oldtail, int newhead, int newdtail){   //來源、(舊的頭尾)、(新的頭尾)
    while((oldhead <= oldtail) && (newhead <= newdtail)){
        if(sor[oldhead].expon < sor[newhead].expon){
            sor[avail].expon = sor[newhead].expon;
            sor[avail].coef = sor[newhead].coef;
            avail++, newhead++;
        }
        else if(sor[oldhead].expon > sor[newhead].expon){
            sor[avail].expon = sor[oldhead].expon;
            sor[avail].coef = sor[oldhead].coef;
            avail++, oldhead++;
        }
        else{
            sor[avail].coef = (sor[oldhead].coef+sor[newhead].coef);
            sor[avail].expon = sor[oldhead].expon;
            avail++, oldhead++, newhead++;
        }

    }
    while(newhead <= newdtail){                                          //剩下新的
        sor[avail].expon = sor[newhead].expon;
        sor[avail].coef = sor[newhead].coef;
        avail++, newhead++;
    }
    while(oldhead <= oldtail){                                          //剩下舊的
        sor[avail].expon = sor[oldhead].expon;
        sor[avail].coef = sor[oldhead].coef;
        avail++, oldhead++;
    }
}   

int main(){
    int N,C=0,E=0,COM=0;                    //COM = 輸入總項數
    int MAX=0;                              //總多項式數
    Ploy term[10000];                         //來源
    while(scanf("%d",&N) != EOF){           //輸入資料
        start[MAX] = COM;
        COM += N;
        finish[MAX] = COM-1;
        MAX ++;
        for (int a=0;a<N;a++){
            scanf("%f",&term[C].coef);
            C ++;
        }
        for (int b=0;b<N;b++){
            scanf("%d",&term[E].expon);
            E ++;
        }
    }

    //Debug
    // for(int i = 0; i<COM; i++){                          //印輸入保存結果
    //     printf("%f, %d\n", term[i].coef, term[i].expon);
    // }
    // for(int i = 0; i<MAX; i++){                          //開頭結束保存
    //     printf("(%d, %d)\n", start[i], finish[i]);
    // }

    avail=COM;                                              //答案(尾巴、頭)

    int ansHead = avail;
    tail(term, start[0], finish[0], start[1], finish[1]);

    for(int i = 2; i<MAX; i++){
        ansHead = avail;
        tail(term, start[i], finish[i], COM, (avail-1));
        COM = ansHead;
    }

    printf("%d\n", (avail-ansHead));
    for(int i = ansHead; i<avail; i++){                     //答案係數
        printf("%f ", term[i].coef);
    }
    printf("\n");
    for(int i = ansHead; i<avail; i++){                     //答案次方
        printf("%d ", term[i].expon);
    }
    printf("\n");
    // printf("%d, %d\n", degree, avail);                   //Debug

    /*
    printf("%d\n",degree);
    for (int a=0;a<degree;a++){
      printf("%f ",term[COM+a].coef);
    }
    printf("\n");
    for (int a=0;a<degree;a++){
      printf("%d ",term[COM+a].expon);
    }
    */

    return 0;
}


/*
2
2 1
3 1
2
3 1 
2 1 
*/

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
*/

/*
3
3 6 4
3 2 0
3
6 9 7
2 1 0
1
6
10
3
5 7 9
1000 5 0
*/