# include <bits/stdc++.h>
using namespace std;

void print_matrix(int**, int, int);
int** Fast_Transpose(int**);
int** read_matrix();

int main(void){
    int in_row{0}, in_col{0};
    int **sor = read_matrix();                                      // input matrix source
    int valueNumber = sor[0][2];

    int **TransMatrixTable = Fast_Transpose(sor);                   // get Transpose Matrix table

    // cout<<endl<<"Transpose matrix table:"<<endl;                    // print transpose matrix
    print_matrix(TransMatrixTable, valueNumber+1, 3); 


    for (int i = 0; i<in_row; i++){                                 // avoid memory leak
        delete[] sor[i];
    }
    delete sor;
    for(int i = 0; i<valueNumber+1; i++){
        delete[] TransMatrixTable[i];
    }
    delete TransMatrixTable;
    return 0;
}



void print_matrix(int** mat, int row, int col){
    for (int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
}

int** read_matrix(){                                              // 呼叫指標傳陣列           
    int row{0}, col{0}, value{0};   
    cin>>row>>col>>value;
    int **mat = new int*[value+1];
    for(int i = 0; i<value+1; i++){
        mat[i] = new int[3];
    }
    mat[0][0] = row, mat[0][1] = col, mat[0][2] = value;
    for(int i = 1; i<=mat[0][2]; i++){                           // 讀入非零矩陣值
        cin>>row>>col>>value;
        mat[i][0] = row, mat[i][1] = col, mat[i][2] = value;
    }
    return mat;
}

int** Fast_Transpose(int** source){
    int row = source[0][0], col = source[0][1], non_zero_number{source[0][2]};

    int *row_NonZero_num = new int[col];                        // The non zero number of each (original)cols/(ans)rows
    int *start_pos = new int[col];                              // The start position of (original)col/(ans)rows

    int **ans = new int*[non_zero_number+1];                    // The result matrix's table
    for(int i = 0; i < non_zero_number+1; i++){
        ans[i] = new int[3];                                    // The result matrix's table
    }

    ans[0][0] = col, ans[0][1] = row, ans[0][2] = non_zero_number;

    if(non_zero_number > 0){                                    // Sure that there are nonzero numbers in matrix
        for(int i = 0; i<col; i++){                             // initialize, 因為可能有某列真的沒有任何大於零的數字
            row_NonZero_num[i] = 0;
        }
        for(int i = 1; i<non_zero_number+1; i++){
            row_NonZero_num[source[i][1]]++;                    // count each (ans)row's nonzero number from source matrix's column -> answer matrix's row
        }
        start_pos[0] = 1;                                       // 因為 table 從第1列才開始放資料
        for(int i = 1; i<col; i++){
            start_pos[i] = start_pos[i-1]+row_NonZero_num[i-1]; // record start position for answer row
        }

        // debug
        // for(int i = 0; i<col; i++){
        //     cout<<row_NonZero_num[i]<<" ";
        // }
        // cout<<endl;
        // for(int i = 0; i<col; i++){
        //     cout<<start_pos[i]<<" ";
        // }

        for(int i = 1; i<non_zero_number+1; i++){
            int now_row = start_pos[source[i][1]]++;            // 拿出答案列中，開始出現非零數字的開頭
            ans[now_row][0] = source[i][1];                     // 填入 原始行 至 答案列
            ans[now_row][1] = source[i][0];                     // 填入 原始列 至 答案行
            ans[now_row][2] = source[i][2];                     // 填入 原始值
        }
    }

    delete[] row_NonZero_num;
    delete[] start_pos;
    return ans;
}

/*
6 6 8 
0 0 15
0 3 22
0 5 -15
1 1 11
1 2 3 
2 3 -6
4 0 91
5 2 28
*/