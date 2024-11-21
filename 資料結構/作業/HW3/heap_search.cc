# include <bits/stdc++.h>
using namespace std;

class node{
public:
    int data;
    node *left;
    node *right;
    node(int data=0, node *left = nullptr, node *right = nullptr);
};

node::node(int data, node *left, node *right){
    this->data = data;
    this->left = left;
    this->right = right;
}

node *get_heap();
bool dfs(int target = 0, node *root = nullptr);
void print(node *root = nullptr);

int main(void){
    node *root = get_heap();                                        // 取得一棵樹
    cout<<"source tree : ";
    print(root);                                                    // 印出heap
    cout<<endl;
    cout<<"target : ";
    int target{0}; cin>>target;                                     // 要找的數字
    cout<<"Result : "<<dfs(target, root)<<endl;                     // 判斷是否有找到
    return 0;
}

node *get_heap(){
    node *root = new node(100);

    root->left = new node(64);
    root->right = new node(87);

    root->left->left = new node(32);
    root->left->right = new node(56);
    root->right->left = new node(16);
    root->right->right = new node(48);

    root->left->left->left = new node(7);
    root->left->left->right = new node(16);
    root->left->right->left = new node(47);
    root->left->right->right = new node(40);

    return root;
}
///////////樹的形狀///////////
/*
          100
     64        87
 32      56  16  48
7  16  47  40
*/
///////////樹的形狀///////////

bool dfs(int target, node *root){                                   // (1 有 ，0 沒有)
    if(root == nullptr) return false;
    if(root->data == target) return true;
    return dfs(target, root->left) || dfs(target, root->right);
}

void print(node *root){                                             // inorder(中序)
    if(root == nullptr) return;
    print(root->left);
    cout<<root->data<<" ";
    print(root->right);
    return;
}