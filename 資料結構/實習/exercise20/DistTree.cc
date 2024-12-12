# include <bits/stdc++.h>
using namespace std;

# define SIZE 1000

// 完整輸入
int sor[SIZE][SIZE]{{0}};

// 拿到所有完整輸入
int get_sor();
// 預計從sch1點到sch2點
int sch1{0}, sch2{0};
// 存根走到sch1、根走到sch2路徑
int sch1_lst[SIZE]{0}, sch2_lst[SIZE]{0};
void dfs(int tar, int row, int deep, int*);
int dist();

int main(void){
    int root = get_sor();
    dfs(sch1, root, 1, sch1_lst);
    dfs(sch2, root, 1, sch2_lst);
    cout<<dist()<<endl;

    // debug 印出矩陣
    // for(int i = 0; i<11; i++){
    //     for(int j = 0; j<11; j++){
    //         cout<<sor[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    // debug 印出路徑
    // for(int i = 0; i<5; i++){
    //     cout<<sch1_lst[i]<<" ";
    // }
    // cout<<endl;
    // for(int i = 0; i<5; i++){
    //     cout<<sch2_lst[i]<<" ";
    // }
    // cout<<endl;

    return 0;
}

int get_sor(){
    int rt{0}; cin>>rt;
    int pt{0}, chd{0};

    int tmp[SIZE][2]{{0}};
    int index{0};

    // 初始化
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            sor[i][j] = -1;
        }
        for(int j = 0; j<2; j++){
            tmp[i][j] = -1;
        }
        sch1_lst[i] = -1;
        sch2_lst[i] = -1;
    }
    sch1_lst[0] = rt;
    sch2_lst[0] = rt;
    
    // 輸入全吃
    while(cin>>pt>>chd){
        tmp[index][0] = pt;
        tmp[index][1] = chd;
        index++;
    }

    // 尋找的兩點(最後的兩個輸入)
    sch1 = pt, sch2 = chd;          

    for(int i = 0; i<(index-1); i++){
        for(int j = 0; j<SIZE; j++){
            if(sor[tmp[i][0]][j] == -1){
                sor[tmp[i][0]][j] = tmp[i][1];
                break;
            } 
        }
    }
    return rt;
}

void dfs(int target, int row, int deep, int *ans){
    for(int i = 0; i<SIZE; i++){
        if(sor[row][i] == -1) return;
        if(sor[row][i] != -1) ans[deep] = sor[row][i];
        if(ans[deep] == target){
            for(int j = deep+1; j<SIZE; j++) ans[j] = -1;
            return;
        } 
        dfs(target, sor[row][i], deep+1, ans);
    }
}

int dist(){
    int ans{0};
    for(int i = 0; i<SIZE; i++){
        // 走完了，跳出
        if(sch1_lst[i] == -1 && sch2_lst[i] == -1) break;
        // 一個沒走完，+1
        else if(sch1_lst[i] == -1 || sch2_lst[i] == -1) ans += 1;
        // 兩個走不同路，+2
        else if(sch1_lst[i] != sch2_lst[i]){
            ans += 2;
        }
    }
    return ans;
}

///////////
/*
0
0 3
0 1
1 2
1 4
1 5
3 6
3 7
3 4
*/
/*
3
*/
///////////
/*
9
9 10
9 3
10 7
10 8
3 6
3 1
1 4
1 5
5 3
*/
/*
2
*/
///////////