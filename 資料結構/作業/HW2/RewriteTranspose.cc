# include <bits/stdc++.h>
using namespace std;

int** get_matrix(int, int);
void print_matrix(int**, int, int);
int cnt_non_zero(int**, int, int);
int** get_table(int**, int, int, int);
int** Fast_Transpose(int**);
int** table_to_matrix(int**);

int main(void){
    int in_row{0}, in_col{0};
    cin>>in_row>>in_col;
    int **sor = get_matrix(in_row, in_col);                         // input matrix source
    int valueNumber = cnt_non_zero(sor, in_row, in_col);            // count not zero values

    int **table = get_table(sor, in_row, in_col, valueNumber);      // create Fast_Matrix_Transpose table

    // cout<<"Original matrix："<<endl;                             // debug
    // print_matrix(sor, in_row, in_col);                           // print origin matrix source--debug
    // cout<<endl<<"Original table："<<endl;                        // debug
    // print_matrix(table, valueNumber+1, 3);                       // print Fast_Matrix_Transpose table--debug

    int **TransMatrixTable = Fast_Transpose(table);                 // get Transpose Matrix table

    cout<<endl<<"Transpose matrix table:"<<endl;                   // print transpose matrix
    print_matrix(TransMatrixTable, valueNumber+1, 3); 

    int **TransMatrix = table_to_matrix(TransMatrixTable);
    cout<<endl<<"Transpose matrix:"<<endl;
    print_matrix(TransMatrix, TransMatrixTable[0][0], TransMatrixTable[0][1]);


    for (int i = 0; i<in_row; i++){                                 // avoid memory leak
        delete[] sor[i];
    }
    delete sor;
    for (int i = 0; i<valueNumber+1; i++){
        delete[] table[i];
    }
    delete table;
    for(int i = 0; i<valueNumber+1; i++){
        delete[] TransMatrixTable[i];
    }
    delete TransMatrixTable;
    for(int i = 0; i<in_col; i++){
        delete[] TransMatrix[i];
    }
    delete TransMatrix;
    return 0;
}


int** get_matrix(int row, int col){
    int **sor = new int*[row];
    for(int i = 0; i<row; i++){
        sor[i] = new int[col];
        for(int j = 0; j<col; j++){
            cin>>sor[i][j];
        }
    }
    return sor;
}

void print_matrix(int** mat, int row, int col){
    for (int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
}

int cnt_non_zero(int** mat, int row, int col){
    int cnt{0};
    for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            if(mat[i][j]!= 0) cnt++;
        }
    }
    return cnt;
}

int** get_table(int** sor, int in_row, int in_col, int valueNumber){
    int **table = new int*[valueNumber+1];                         // create Fast_Matrix_Transpose table
    for(int i = 0; i<valueNumber+1; i++){
        table[i] = new int[3];
    }

    table[0][0] = in_row;
    table[0][1] = in_col;
    table[0][2] = valueNumber;
    int row_cnt = 1;                                               // count row_cnt for table
    for(int i = 0; i<in_row; i++){
        for(int j = 0; j<in_col; j++){
            if(sor[i][j] != 0){
                table[row_cnt][0] = i;
                table[row_cnt][1] = j;
                table[row_cnt][2] = sor[i][j];
                row_cnt++;
            }
        }
    }
    return table;
}

int** Fast_Transpose(int** source){
    int row = source[0][0], col = source[0][1], non_zero_number{source[0][2]};

    int *row_NonZero_numADDstart_pos = new int[2*col];          // The non zero number of each (original)cols/(ans)rows ADD start position(original)col/(ans)rows

    int **ans = new int*[non_zero_number+1];                    // The result matrix's table
    for(int i = 0; i < non_zero_number+1; i++){
        ans[i] = new int[3];                                    // The result matrix's table
    }

    ans[0][0] = col, ans[0][1] = row, ans[0][2] = non_zero_number;

    if(non_zero_number > 0){                                    // Sure that there are nonzero numbers in matrix
        for(int i = 0; i<col; i++){                             // initialize, 因為可能有某列真的沒有任何大於零的數字
            row_NonZero_numADDstart_pos[i] = 0;
        }
        for(int i = 1; i<non_zero_number+1; i++){
            row_NonZero_numADDstart_pos[source[i][1]]++;        // count each (ans)row's nonzero number from source matrix's column -> answer matrix's row
        }
        row_NonZero_numADDstart_pos[col] = 1;                   // 因為 table 從第1列（合併後的陣列從第col列開始記錄 非零數字開頭）才開始放資料
        for(int i = 1; i<col; i++){
            row_NonZero_numADDstart_pos[col+i] = row_NonZero_numADDstart_pos[col+i-1]+row_NonZero_numADDstart_pos[i-1]; // record start position for answer row
        }

        //debug
        // cout<<"Debug"<<endl;
        // for(int i = 0; i<col; i++){
        //     cout<<row_NonZero_numADDstart_pos[col+i]<<" ";
        // }
        // cout<<endl;

        for(int i = 1; i<non_zero_number+1; i++){
            int now_row = row_NonZero_numADDstart_pos[source[i][1]+col]++;            // 拿出答案列中，開始出現非零數字的開頭
            ans[now_row][0] = source[i][1];                                           // 填入 原始行 至 答案列
            ans[now_row][1] = source[i][0];                                           // 填入 原始列 至 答案行
            ans[now_row][2] = source[i][2];                                           // 填入 原始值
        }
    }

    delete[] row_NonZero_numADDstart_pos;
    return ans;
}

int** table_to_matrix(int** table){
    int **matrix = new int*[table[0][0]];
    for(int i = 0; i<table[0][0]; i++){
        matrix[i] = new int[table[0][1]];
    }
    for(int i = 0; i<table[0][0]; i++){
        for(int j = 0; j<table[0][1]; j++){
            matrix[i][j] = 0;
        }
    }
    for(int i = 1; i<table[0][2]+1; i++){
        matrix[table[i][0]][table[i][1]] = table[i][2];
    }
    return matrix;
}

/////////////////////////////////////////////////////////測試資料一
/*
2 3
3 0 1
4 5 6
*/

/*                                                       轉至後矩陣表
3 2 5 
0 0 3 
0 1 4 
1 1 5 
2 0 1 
2 1 6
*/

/*                                                       轉至後矩陣
3 4 
0 5 
1 6
*/

/////////////////////////////////////////////////////////測試資料二

/*
6 6
15 0 0 22 0 -15
0 11 3 0 0 0 
0 0 0 -6 0 0
0 0 0 0 0 0 
91 0 0 0 0 0 
0 0 28 0 0 0
*/

/*                                                       轉至後矩陣表
6 6 8 
0 0 15 
0 4 91
1 1 11
2 1 3
2 5 28
3 0 22
3 2 -6
5 0 -15
*/

/*                                                       轉至後矩陣
15 0 0 0 91 0 
0 11 0 0 0 0
0 3 0 0 0 28
22 0 -6 0 0 0
0 0 0 0 0 0
-15 0 0 0 0 0
*/

/////////////////////////////////////////////////////////測試資料三

/*
2 2 
3 6 
0 4 
*/

/*                                                       轉至後矩陣表
2 2 3
0 0 3
1 0 6
1 1 4
*/

/*                                                       轉至後矩陣
3 0 
6 4
*/

/////////////////////////////////////////////////////////////////////