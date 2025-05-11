# include <bits/stdc++.h>
using namespace std;

class matrix{
public:
    int row;
    int col;
    matrix(int row, int col);
};

matrix::matrix(int row = 0, int col = 0){
    this->row = row;
    this->col = col;
}

int main(void){
    vector<matrix> source;
    int matrixNum{0}; cin>>matrixNum;
    for(int i = 0; i<matrixNum; i++){
        matrix tmp;
        cin>>tmp.row>>tmp.col;
        source.push_back(tmp);
    }
    vector<vector<long long>> multipleTime(matrixNum, vector<long long>(matrixNum, 0));
    for(int i = 0; i<matrixNum; i++){
        multipleTime[i][(long long)i] = 0;
    }
    for(int i = 1; i<matrixNum; i++){
        for(int j = 0; j<matrixNum-i; j++){
            multipleTime[j][(long long)(j+i)] = LLONG_MAX;
            for(int k = j; k<j+i; k++){
                multipleTime[j][(long long)(j+i)] = min(multipleTime[j][(long long)(j+i)], multipleTime[j][(long long)k] + multipleTime[(long long)(k+1)][(long long)(j+i)] + source[j].row*source[k].col*source[j+i].col);
            }
        }
    }
    cout<<multipleTime[0][(long long)(matrixNum-1)]<<endl;
    return 0;
}