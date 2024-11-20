# include <bits/stdc++.h>
using namespace std;

class node{
public:
    int data;
    node *next;
    node(int data=0, node *next = nullptr){
        this->data = data;
        this->next = next;
    }
};

class myList{
public:
    node *head;
    node *tail;
    myList(node *head = nullptr, node *tail = nullptr){
        this->head = head;
        this->tail = tail;
    }
    void push(node *node);
};

void myList::push(node *node){
    if(this->head == nullptr){
        this->head = node;
        this->tail = node;
    }
    else{
        this->tail->next = node;
        this->tail = node;
    }
    return;
}

node* travel_bst();

int main(void){
    node *now_pos = travel_bst();                      // 從答案頭開始印出所有資料
    while(now_pos){
        cout<<now_pos->data<<" ";
        now_pos = now_pos->next;
    }

    return 0;
}

node *travel_bst(){
    int non_zero{0}, cnt_non_zero{0};                   // 幾個非零值、目前有幾個值非零
    cin>>non_zero;                                      // 輸入非零值，與目前狀況比較
    myList ans;                                         // 存放答案(未知有多少值，動態放置)
    node *now_pos = nullptr;                            // 初始設定，連頭都沒有
    while(non_zero > cnt_non_zero){                     // 非零值相同即完成目的
        if(ans.head == nullptr){                        // 特例，只有第一次需要放頭
            int root{0};                                // 放入頭
            cin>>root;
            if (root) cnt_non_zero++;
            ans.push(new node(root));

            int rl{0};                                  // 放入頭的左子點
            cin>>rl;
            if (rl) cnt_non_zero++;                     // 可能放入非零，需判斷是否非零值+1
            ans.push(new node(rl));

            int rr{0};                                  // 放入頭的右子點   
            cin>>rr;
            if (rr) cnt_non_zero++;                     // 可能放入非零，需判斷是否非零值+1
            ans.push(new node(rr));

            now_pos = ans.head->next;                   // 初始設定後，第一層結束，應該從第二層開始
        }
        else{
            int data{0};                                // 讀入下一層 頭 的值
            cin>>data;
            start:                                      // 當值與頭不同，不應該在讀入下一個頭，應該等到值與頭相同的點加入左右子點
            if(data == now_pos->data){                  // 如果值與頭一樣，表示接下來兩個值分別為頭的左右子點
                int rl{0};
                cin>>rl;
                if (rl) cnt_non_zero++;
                ans.push(new node(rl));

                int rr{0};
                cin>>rr;
                if (rr) cnt_non_zero++;
                ans.push(new node(rr));

                now_pos = now_pos->next;                // 此點判斷完畢，接續下一個點
            }
            else{                                       // 值與頭不同，表示接下來兩個值為頭的左右子樹為空(補零)
                ans.push(new node(0));
                ans.push(new node(0));

                now_pos = now_pos->next;                // 此點判斷完畢，接續下一個點
                goto start;
            }
        }
    }
    return ans.head;
}

////////////////////////////////////
/*
6
9 8 7
7 11 0
11 4 2
*/

/*
9 8 7 0 0 11 0 0 0 0 0 4 2
*/
////////////////////////////////////
/*
8
3 7 6
7 8 4
8 7 0
4 5 3
*/

/*
3 7 6 8 4 0 0 7 0 5 3
*/
////////////////////////////////////
/*
3
7 0 3
3 0 6
*/

/*
7 0 3 0 0 0 6
*/
////////////////////////////////////