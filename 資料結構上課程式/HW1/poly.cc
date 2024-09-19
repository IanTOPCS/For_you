# include <bits/stdc++.h>
using namespace std;

double honor(double*, int, double);

int main(void){
    int degree{0};                                      //輸入多項是最高項次方
    cin>>degree;
    double poly[degree+1] = {0};                        //包括常數項，故開出+1空間
    for(int i = 0; i<=degree; i++){
        cin>>poly[i];
    }
    double tar{0};                                      //令出多項式x要帶入的數字
    cin>>tar;
    double total = honor(poly, degree, tar);            //依公式算答案
    cout<<total<<endl;
    return 0;
}

double honor(double *poly, int degree, double tar){
    double ans = poly[degree];                          //令答案為最高項係數
    for(int i = degree-1; i>=0; i--){                   //只需做最高係數次
        ans = ans*tar + poly[i];                        //將答案*x，再加低一次的係數
    }
    return ans;
}

/*
2
2 3 5
2
*/