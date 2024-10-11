# include <bits/stdc++.h>
using namespace std;

int** get_matrix(int, int);
void print_matrix(int**, int, int);
int cnt_non_zero(int**, int, int);
int** get_table(int**, int, int, int);
int** Fast_Transpose(int**);
int** table_to_matrix(int**);
int** multi_matrix(int**, int**);
void storeSum(int**, int*, int, int, int*);

int main(void){
    int left_matrix_row{0}, left_matrix_col{0};
    cin>>left_matrix_row>>left_matrix_col;
    int **leftMatrix = get_matrix(left_matrix_row, left_matrix_col);                                 // input left matrix source
    int leftValueNumber = cnt_non_zero(leftMatrix, left_matrix_row, left_matrix_col);                // count not zero values
    int **leftTable = get_table(leftMatrix, left_matrix_row, left_matrix_col, leftValueNumber);      // create left Fast_Matrix table

    // debug
    // cout<<endl<<"The left matrix table is:"<<endl;
    // print_matrix(leftTable, leftValueNumber+1, 3);

    int right_matrix_row{0}, right_matrix_col{0};
    cin>>right_matrix_row>>right_matrix_col;
    int **rightMatrix = get_matrix(right_matrix_row, right_matrix_col);                              // input right matrix source
    int rightValueNumber = cnt_non_zero(rightMatrix, right_matrix_row, right_matrix_col);            // count not zero values
    int **rightTable = get_table(rightMatrix, right_matrix_row, right_matrix_col, rightValueNumber); // create right Fast_Matrix table

    // debug
    // cout<<endl<<"The right matrix table is:"<<endl;
    // print_matrix(rightTable, rightValueNumber+1, 3);

    int **multiMatrixTable = multi_matrix(leftTable, rightTable);                                    // create product Fast_Matrix table

    cout<<endl<<"The product of the two matrices table is:"<<endl;
    print_matrix(multiMatrixTable, multiMatrixTable[0][2]+1, 3);

    int **multiMatrix = table_to_matrix(multiMatrixTable);                                             // create product matrix
    cout<<endl<<"The product of the two matrices is:"<<endl;
    print_matrix(multiMatrix, multiMatrixTable[0][0], multiMatrixTable[0][1]);

    for(int i = 0; i<left_matrix_row; i++){                                                             // avoid memory leak
        delete[] leftMatrix[i];
    }
    delete leftMatrix;
    for(int i = 0; i<leftValueNumber+1; i++){
        delete[] leftTable[i];
    }
    delete leftTable;
    for(int i = 0; i<right_matrix_row; i++){
        delete[] rightMatrix[i];
    }
    delete rightMatrix;
    for(int i = 0; i<rightValueNumber+1; i++){
        delete[] rightTable[i];
    }
    delete rightTable;
    int multiNonZeroNum = multiMatrixTable[0][2];
    for(int i = 0; i<multiNonZeroNum; i++){
        delete[] multiMatrixTable[i];
    }
    delete multiMatrixTable;
    for(int i = 0; i<left_matrix_row; i++){
        delete[] multiMatrix[i];
    }
    delete multiMatrix;

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

int** multi_matrix(int** left, int** right){
    int **ans = new int*[(left[0][0]*right[0][1])+1];                       // 動態答案矩陣
    for(int i = 0; i<(left[0][0]*right[0][1])+1; i++){
        ans[i] = new int[right[0][1]];
    }
    ans[0][0] = left[0][0], ans[0][1] = right[0][1];

    int now_col{0}, ans_non_zero_num{0};
    int row_begin{1}, now_row{left[1][0]}, multiple_sum{0};

    int **trans_right = Fast_Transpose(right);              // get right matrix's Transpose Matrix table

    for(int row = 1; row<=left[0][2];){                     // go around by each row data of left matrix
        now_col = trans_right[1][0];                        // 新的一列作運算一定是從右矩陣的第一筆非零資料
        for(int col = 1; col<=right[0][2];){                // go around by each col data of right matrix
            if(row > left[0][2]) row = row_begin;           // 左矩陣已經不可能有資料了（左矩陣最後一列*右矩陣行 會超出 row 範圍）
            if(left[row][0] != now_row){                    // 左矩陣已經做完此列了，不可能改變此結果格答案，但右矩陣並不一定移動到下一行（即左矩陣0*右矩陣行資料）
                storeSum(ans, &ans_non_zero_num, now_row, now_col, &multiple_sum);
                row = row_begin;                            // 繼續同行乘下一列
                while(trans_right[col][0] == now_col){      // 移動至下一列資料
                    col++;
                    if(col > right[0][2]) break;            // 右矩陣已經不可能有資料了
                }
                if(col > right[0][2]) break;                // 右矩陣已經不可能有資料了（ 接 跳出while的）
                now_col = trans_right[col][0];              // 改變關注的行
            }
            else if(trans_right[col][0] != now_col){        // 右矩陣已經做完此行了（已經移動到下一行），不可能改變此結果格答案，但左矩陣要回到此列的開始處繼續乘上下一行
                storeSum(ans, &ans_non_zero_num, now_row, now_col, &multiple_sum);
                row = row_begin;
                now_col = trans_right[col][0];              // 行會藉由 for col 跳出，不必判斷
            }
            else{
                if(left[row][1] < trans_right[col][1]){                         // 左矩陣格位置比右矩陣格位置小，左矩陣要移動到下一格
                    row++;
                }
                else if(left[row][1] == trans_right[col][1]){                   // 只有左矩陣格與右矩陣同格（轉置過後的右矩陣），才能相乘
                    multiple_sum += left[row++][2] * trans_right[col++][2];
                }
                else if(left[row][1] > trans_right[col][1]){                    // 左矩陣格位置比右矩陣格位置大，右矩陣要移動到下一格
                    col++;
                }
            }
        }
        if(row > left[0][2]){                                                   // 最後一列最後一行做完，存入結果，跳出
            storeSum(ans, &ans_non_zero_num, now_row, now_col, &multiple_sum);
            break;                                                              // 左矩陣已經不可能有資料了
        } 
        while(left[row][0] == now_row){                                         // 移動至下一列
            row++;
            if(row > left[0][2]) break;                                         // 左矩陣已經不可能有資料了
        }
        if(row > left[0][2]) break;                                             // 左矩陣已經不可能有資料了（接 while 跳出的）
        storeSum(ans, &ans_non_zero_num, now_row, now_col, &multiple_sum);
        now_row = left[row][0];
        row_begin = row;
    }

    for(int i = 0; i<right[0][2]+1; i++){
        delete[] trans_right[i];
    }
    delete trans_right;

    ans[0][2] = ans_non_zero_num;
    return ans;
}

void storeSum(int **source, int *non_zero_num, int row, int col, int *sum){
    if(*sum){
        source[++(*non_zero_num)][0] = row;
        source[*non_zero_num][1] = col;
        source[*non_zero_num][2] = *sum;
        *sum = 0;
    }
}

////////////////////////////////////////////
/*
3 2
-27 6
82 0
109 -64
2 3
21 27 0
5 0 -71
*/

/*
-537 -729 -426
1722  2214 0
1969 2943 4544
*/

/////////////////////////////////////////////
/*
3 2
1 1
1 1
1 1
2 3
1 1 1
1 1 1
*/

/*
2 2 2
2 2 2
2 2 2
*/

//////////////////////////////////////////////
/*
1 1
5
1 1
6
*/

/*
30
*/
