# include <bits/stdc++.h>
using namespace std;

class node{
public:
    int data;
    node *left;
    node *right;
    node(int data=0, node *left = nullptr, node *right = nullptr){
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

class data_stack{
public:
    node *data;
    data_stack *next;
    data_stack(node *data, data_stack *next = nullptr){
        this->data = data;
        this->next = next;
    }
};

class myStack{
public:
    data_stack *top;
    myStack(){
        this->top = nullptr;
    }
    void push(data_stack *node = nullptr){
        node->next = this->top;
        this->top = node;
    }
    void pop(){
        if(this->top == nullptr) return;
        data_stack *temp = this->top;
        this->top = this->top->next;
        delete temp;
    }
};

node* show_tree();                                                      // 生出一棵 binary search tree
void dfs(node*);                                                        // 對照組
void iter_dfs(node*);                                                   // 實驗組

int main(void){
    system("chcp 65001");                                               // Windows 中文亂碼
    node *root = show_tree();                                           // 手動生出一棵樹

    cout<<"對照組："<<" ";
    dfs(root);                                                          // 必定對的(會寫的)
    cout<<endl;

    cout<<"實驗組："<<" ";
    iter_dfs(root);                                                     // 不太會的
    cout<<endl;

    return 0;
}

node* show_tree(){
    node *root = new node(87);

    node *tmp = root;

    tmp->left = new node(43);
    tmp->right = new node(99);

    tmp->left->left = new node(21);
    tmp->left->right = new node(54);
    tmp->right->left = new node(70);
    tmp->right->right = new node(100);

    return root;
}
/////////樹的形狀/////////
/*
      87
  43      99
21  54  70  100
*/
/////////樹的形狀/////////

void dfs(node *root){
    if(root == nullptr) return;                                         // 走到底，往回
    dfs(root->left);                                                    // 向左   
    dfs(root->right);                                                   // 向右
    cout<<root->data<<" ";                                              // 接收到往回訊號，印出此格，在回到上一個狀態
    return;
}

void iter_dfs(node *root){
    myStack s;                                                          // 存放狀態
    s.push(new data_stack(root));                                       // 從root開始
    while(s.top != nullptr){                                            // 如果 root 已經結束，就結束
        node *now = s.top->data;                                        // 更新狀態
        if((now->left == nullptr) && (now->right == nullptr)){          // 當左右都沒有子樹時，印出值，回到上一狀態
            cout<<now->data<<" ";
            s.pop();
        }

        if(now->right != nullptr){                                      // 約定先向左，左子樹應該為stack上方，又子樹應該為stack下方，下方的先放
            s.push(new data_stack(now->right));                         // 放入右子樹
            now->right = nullptr;                                       // 打斷父節點左連結(還有右連結，故可以繼續走而不會印出)
        }

        if(now->left != nullptr){
            s.push(new data_stack(now->left));                          // 放入左子樹
            now->left = nullptr;                                        // 打斷父節點右連結(已經成為單一節點，符合左右子樹為空，印出內容)
        }
    }
    return;
}