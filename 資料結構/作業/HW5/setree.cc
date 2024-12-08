# include <bits/stdc++.h>
using namespace std;

class node{
public:
    string data;
    node* left;
    node* right;
    node(string data=0, node* left = nullptr, node* right = nullptr);
};

node::node(string data, node* left, node* right){
    this->data = data;
    this->left = left;
    this->right = right;
}

node *get_tree();
void inorder(node *root);
void preorder(node *root);
void postorder(node *root);
void levelorder(node *root);

int main(void){
    node *root = get_tree();
    cout<<"inorder : "; inorder(root); cout<<endl;
    cout<<"preorder : "; preorder(root); cout<<endl;
    cout<<"postorder : "; postorder(root); cout<<endl;
    cout<<"levelorder : "; levelorder(root); cout<<endl;
    return 0;
}

node* get_tree(){
    node *root = new node("A");
    root->left = new node("B");
    root->right = new node("C");
    root->left->left = new node("D");
    root->left->right = new node("E");
    root->right->left = new node("F");
    root->right->right = new node("G");
    root->left->left->left = new node("H");
    root->left->left->right = new node("J");
    return root;
}

void inorder(node *root){
    if(root == nullptr) return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
    return;
}

void preorder(node *root){
    if(root == nullptr) return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
    return;
}

void postorder(node *root){
    if(root == nullptr) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
    return;
}

void levelorder(node *root){
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node *tmp = q.front(); q.pop();
        cout<<tmp->data<<" ";
        if(tmp->left) q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
    }
    return;
}