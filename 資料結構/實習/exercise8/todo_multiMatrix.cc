# include <bits/stdc++.h>
using namespace std;

void print_matrix(int**, int, int);
int** Fast_Transpose(int**);
int** multi_matrix(int**, int**);
void storeSum(int**, int*, int, int, int*);
int** read_matrix();

int main(void){
    int** leftTable = read_matrix();
    int leftValueNumber = leftTable[0][2];

    int** rightTable = read_matrix();
    int rightValueNumber = rightTable[0][2];

    int **multiMatrixTable = multi_matrix(leftTable, rightTable);                                    // create product Fast_Matrix table

    // cout<<endl<<"The product of the two matrices table is:"<<endl;
    print_matrix(multiMatrixTable, multiMatrixTable[0][2]+1, 3);

    for(int i = 0; i<leftValueNumber+1; i++){
        delete[] leftTable[i];
    }
    delete leftTable;
    for(int i = 0; i<rightValueNumber+1; i++){
        delete[] rightTable[i];
    }
    delete rightTable;
    int multiNonZeroNum = multiMatrixTable[0][2];
    for(int i = 0; i<multiNonZeroNum+1; i++){
        delete[] multiMatrixTable[i];
    }
    delete multiMatrixTable;

    return 0;
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

void print_matrix(int** mat, int row, int col){
    for (int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
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

///////////////
/*
2 3 2
0 0 15
1 2 3
3 4 3
1 1 1
1 2 -1
2 2 3
*/

/*
2 4 1 
1 2 9
*/
//////////////