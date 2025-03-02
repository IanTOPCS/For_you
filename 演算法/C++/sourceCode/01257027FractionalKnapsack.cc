# include <bits/stdc++.h>
using namespace std;

class valPerW{
public:
    double value;
    double weight;
    valPerW(double value = 0, double weight = 0);
};

valPerW::valPerW(double value, double weight){
    this->value = value;
    this->weight = weight;
}

double maxVal(valPerW *myPac = nullptr, int num = 0, double canW = 0);

int main(void){
    int num{0}; cin>>num;
    double canW{0}; cin>>canW;
    valPerW *myPack = new valPerW[num];
    for(int i = 0; i<num; i++){
        double val{0}, w{0}; cin>>val>>w;
        myPack[i] = valPerW(val, w);
    }
    cout<<fixed<<setprecision(6)<<maxVal(myPack, num, canW)<<"\n";
    delete[] myPack;
    return 0;
}

double maxVal(valPerW *myPac, int num, double canW){
    sort(myPac, myPac+num, [](valPerW a, valPerW b){return (a.value/a.weight)>(b.value / b.weight);});
    double ansVal{0};
    for(int i = 0; i<num; i++){
        if(canW >= myPac[i].weight){
            ansVal += myPac[i].value;
            canW -= myPac[i].weight;
        }
        else{
            ansVal += (myPac[i].value * canW / myPac[i].weight);
            canW = 0;
            break;
        }
    }
    return ansVal;
}