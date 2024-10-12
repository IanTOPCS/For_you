# include <bits/stdc++.h>
using namespace std;

# define MAX_TERMS 101
class term{
public:
    int row;
    int col;
    int value;
    term();
};

term::term(){
    this->row = 0;
    this->col = 0;
    this->value = 0;
}

void read_matrix(term*);
void print_matrix(term*);
void search(term*, int);

int main(void){                                                     // 規定格式

    term mat[MAX_TERMS];
    read_matrix(mat);
    print_matrix(mat);
    search(mat, 2);
    search(mat, -2);

    return 0;
}

void read_matrix(term *mat){                                         // 呼叫指標傳陣列           
    int row{0}, col{0}, value{0};   
    cin>>row>>col>>value;
    mat[0].row = row, mat[0].col = col, mat[0].value = value;
    for(int i = 1; i<=mat[0].value; i++){                           // 讀入非零矩陣值
        cin>>row>>col>>value;
        mat[i].row = row, mat[i].col = col, mat[i].value = value;
    }
}

void print_matrix(term *mat){
    int **matrix = new int*[mat[0].row];                            // 動態產生矩陣容量
    for(int i = 0; i<mat[0].row; i++){
        matrix[i] = new int[mat[0].col];
    }
    for(int i = 0; i<mat[0].row; i++){                              // 初始化矩陣
        for(int j = 0; j<mat[0].col; j++){
            matrix[i][j] = 0;
        }
    }
    for(int i = 1; i<=mat[0].value; i++){                           // 將非零值填入矩陣
        matrix[mat[i].row][mat[i].col] = mat[i].value;
    }

    //debug
    // cout<<endl<<"Ans:"<<endl;

    for(int i = 0; i<mat[0].row; i++){                              // 顯示矩陣
        for(int j = 0; j<mat[0].col; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i = 0; i<mat[0].row; i++){                              // Avoid memory leak
        delete[] matrix[i];
    }
    delete matrix;
}

void search(term *mat, int value){
    bool flag{false};                                               // 決定是否找到
    for(int i = 1; i<=mat[0].value; i++){                           // 遍歷非零矩陣
        if(mat[i].value == value){
            flag = true;
        }
    }
    if(flag){                                                       // 找到，根據格式輸出
        cout<<"1"<<endl;
    }
    else{
        cout<<"-1"<<endl;                                           // 未找到，根據格式輸出
    }
}

////////////////////////////////////////給定測試資料
/*
2 3 4 
0 0 1
0 1 3
1 1 -1
1 2 2 
*/

/*
1 3 0
0 -1 2
1
-1
*/
////////////////////////////////////////