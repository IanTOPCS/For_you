# include <bits/stdc++.h>
using namespace std;

class node{
public:
    bool leftThread;
    node* left;
    int data;
    node* right;
    bool rightThread;
    node(bool leftThread = false, node* left = nullptr, int data = 0, node* right = nullptr, bool rightThread = false);
};

node::node(bool leftThread, node* left, int data, node* right, bool rightThread){
    this->leftThread = leftThread;
    this->left = left;
    this->data = data;
    this->rightThread = rightThread;
    this->right = right;
};

node* insucc(node *now){
    node *tmp = now->right;                                         // 建樹保證有右子點
    while(!tmp->leftThread){                                        // 走到最左樹葉
        tmp = tmp->left;
    }
    tmp->right->leftThread = true;                                  // 避免死循環，將父節點的左子樹判斷改成 沒有左子樹
    return tmp;
}

void travelInorder(node *root){
    node *tmp = root;
    while(1){
        tmp = insucc(tmp);                                          // 拿到下一個
        if(tmp == root) break;                                      // 引線二元樹 最開頭特性(右節點循環為自己)
        cout<<tmp->data<<" ";
    }
    return;
}

node* get_tree();
void insertLeft(node *parent = nullptr, node *child = nullptr);
node *get_item(node *parent, node *child);

int main(void){
    node *root = get_tree();
    node *new_node = new node(false, nullptr, 10, nullptr, false);
    insertLeft(root->left->left, new_node);
    travelInorder(root);
    return 0;
}

node* get_tree(){                                                 // 建引線二元樹
    node *root = new node(false, nullptr, -1, nullptr, false);
    root->right = root;
    root->left = new node(false, nullptr, 7, nullptr, false);     // 真正的樹根 

    root->left->left = new node(false, nullptr, 6, root->left, true);
    root->left->right = new node(true, root->left, 9, root, true);

    root->left->left->left = new node(false, nullptr, 4, nullptr, false);
    
    root->left->left->left->left = new node(true, root, 2, root->left->left->left, true);
    root->left->left->left->right = new node(true, root->left->left->left, 3, root->left->left, true);
    return root;
}

/////////////// 樹的形狀 ///////////////
/*
      -1
       7
    6     9
  4  
2   3      
*/
/////////////// 樹的形狀 ///////////////

void insertLeft(node *parent, node *child){
    child->left = parent->left;                                 // 接上父節點子樹
    child->leftThread = parent->leftThread;                     // 接上父節引線
    child->right = parent;                                      // 接上引線(方便找下一個節點)
    child->rightThread = true;                                  // 接上右引線
    parent->left = child;                                       // 接上子樹
    parent->leftThread = false;                                 // 因為接上子樹，判斷改成有左子樹 
    if (!child->leftThread){
        node *tmp = get_item(parent, child);                    // 取得下一個節點(最靠近左子樹根的右樹葉)
        tmp->right = child;
    }
    return;
}

node* get_item(node *parent, node *child){                      // 尋找原指向父親的節點，
    node *tmp = child->left;                                    // 默認下一個接在左節點，所以第一點不用判斷
    while(!tmp->rightThread){                                   // 第一個右節點一定接到原父節點，找第一個右樹葉
        tmp = tmp->right;
    }
    return tmp;
}

/*
2 4 3 10 6 7 9
*/