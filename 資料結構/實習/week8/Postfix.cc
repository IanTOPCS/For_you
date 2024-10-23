# include <bits/stdc++.h>
using namespace std;

class Node{
public:
    string value;
    Node *next;
    Node(string value="0", Node *next = nullptr);
};

Node::Node(string value, Node *next){
    this->value = value;
    this->next = next;
}

class myStack{
public:
    Node *top;                          // 指到 linked list 的最前面當作top
    myStack();
    ~myStack();
    void push(Node *node = nullptr);
    void pop();
    void print();
    string getTop();
};

myStack::~myStack(){
    this->top = nullptr;
}

string myStack::getTop(){
    if((this->top) == nullptr) return "-1";
    return this->top->value;
}

void myStack::print(){
    Node *temp = this->top;
    while(temp->value != "EOS"){
        cout<<temp->value<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

myStack::myStack(){
    this->top = nullptr;
}

void myStack::push(Node *node){
    node->next = this->top;
    this->top = node;
}

void myStack::pop(){
    if(this->top == nullptr) return;
    Node *temp = this->top;
    this->top = this->top->next;
    delete temp;
}

myStack postfix();
void deal_in_quote(myStack&, myStack&);
bool compare(string, string);
int eval(myStack&);

int main(void){

    myStack ans_postfix = postfix();
    ans_postfix.print();
    int ans = eval(ans_postfix);
    cout<<ans<<endl;

    return 0;
}

myStack postfix(){
    myStack source_tmp, source, oper, ans_tmp, ans;
    string input{""};
    source.push(new Node("EOS"));                                                               // 用來當作結束符號
    ans_tmp.push(new Node("EOS"));                                                              // 用來當作結束符號
    source_tmp.push(new Node("EOS"));                                                           // 用來當作結束符號
    ans.push(new Node("EOS"));                                                                  // 用來當作結束符號
    while(cin>>input){
        if(input == "\0") break;                                                                // 不可以塞入結束字串符號（與題目不符），且此為逆序
        source_tmp.push(new Node(input));
    }
    while(source_tmp.getTop() != "EOS"){                                                        // 變成正常順序
        source.push(new Node(source_tmp.getTop()));
        source_tmp.pop();
    }
    while(source.getTop() != "EOS"){
        string now_token = source.getTop();                                                     // 另現在拿到的東西為 now_token
        if((now_token >= "0") && (now_token <= "9")) ans_tmp.push(new Node(now_token));         // 如果是數字就馬上存起來
        else if(now_token == "("){
            deal_in_quote(source, ans_tmp);                                                     // 可能有多層括號
            continue;                                                                           // 遇到括號，保證後一個必是符號，不可以pop，應該從頭判斷
        }
        else{
            if(oper.top == nullptr) oper.push(new Node(now_token));                             // 空的表示無法比較運算子優先順序，直接放
            else{
                bool flag = compare(oper.getTop(), now_token);                                  // 比較運算子優先順序（true：馬上拿出來運算/ false：繼續放）
                if(flag == true){
                    ans_tmp.push(new Node(oper.getTop()));                                      // 運算子優先，馬上拿出來運算
                    oper.pop();                                                                 // 先算，放進答案中
                    continue;                                                                   // 可能還有需要比較的運算子，不可pop、無腦放
                }
                else oper.push(new Node(now_token));                                            // 繼續放

            }
        }

        source.pop();                                                                           // 關注下一刻

        // debug
        // cout<<"now_token: "<<endl;                                                   
        // ans.print();
        // cout<<endl;
    }
    while(oper.top != nullptr){                                                                 // 此答案違逆序
        ans_tmp.push(new Node(oper.getTop()));          
        oper.pop();
    }
    while(ans_tmp.getTop() != "EOS"){                                                           // 變成正常順序
        ans.push(new Node(ans_tmp.getTop()));
        ans_tmp.pop();
    }
    return ans;
}

void deal_in_quote(myStack& source, myStack& ans){
    source.pop();                                                                               // 拿掉左括號
    myStack in_quote_operator;
    while(source.getTop() != ")"){
        string now_token = source.getTop();
        if(now_token == "("){
            deal_in_quote(source, ans);                                                         // 交給下一個我
            continue;                                                                           // 括號結束，後一個保證必為符號，不可以pop
        } 
        else if((now_token >= "0") && (now_token <= "9")) ans.push(new Node(now_token));        // 如果是數字就馬上存起來
        else{
            if(in_quote_operator.top == nullptr) in_quote_operator.push(new Node(now_token));   // 空的表示無法比較運算子優先順序，直接放
            else{
                bool flag = compare(in_quote_operator.getTop(), now_token);                     // 比較運算子優先順序（true：馬上拿出來運算/ false：繼續放）
                if(flag == true){
                    ans.push(new Node(in_quote_operator.getTop()));                             // 拿出來運算
                    in_quote_operator.pop();                                                    // 此刻運算元處理完畢
                    continue;                                                                   // 可能還有需要比較的運算子，不可以pop、無腦放   
                }
                else in_quote_operator.push(new Node(now_token));                               // 繼續放
            }
        }
        source.pop();                                                                           // 此刻的token已經處理完畢
    }
    source.pop();                                                                               // 拿掉右括號
    while(in_quote_operator.top != nullptr){                                                    // 括號處理完，將（可能有剩下的）運算子塞回答案
        ans.push(new Node(in_quote_operator.getTop()));
        in_quote_operator.pop();
    }
    return;
}

bool compare(string in_stack, string now_oper){
    string order[5] = {"+", "-", "*", "/", "%"};
    int order_num[5] = {1, 1, 2, 2, 3};
    int in_stack_order = 0, now_oper_order = 0;
    for(int i = 0; i < 5; i++){
        if(order[i] == in_stack) in_stack_order = order_num[i];
        if(order[i] == now_oper) now_oper_order = order_num[i];
    }
    if(in_stack_order >= now_oper_order) return true;                                           // 在stack裡的優先序比較大，應該拿出來運算
    else return false;                                                                          // 優先序較stack裡的大，繼續放
}

int eval(myStack &source){
    int front_num{0}, back_num{0};
    myStack num;
    while(source.getTop() != "EOS"){
        string now_token = source.getTop();
        if((source.getTop() >= "0") && (source.getTop() <= "9")){                               // 如果是數字，應該放入堆疊，等待被運算
            num.push(new Node(source.getTop()));
        }
        else{
            back_num = stoi(num.getTop());                                                      // 最後放進去的應為運算中的後者（要轉type）
            num.pop();
            front_num = stoi(num.getTop());                                                     // 先放進去的應為運算中的先者（要轉type）
            num.pop();
            if(now_token == "+"){
                num.push(new Node(to_string(front_num + back_num)));                            // 計算結果當作新的運算元存入stack（轉type符合設定）
            }
            else if(now_token == "-"){
                num.push(new Node(to_string(front_num - back_num)));
            }
            else if(now_token == "*"){
                num.push(new Node(to_string(front_num * back_num)));
            }
            else if(now_token == "/"){
                num.push(new Node(to_string(front_num / back_num)));
            }
            else if(now_token == "%"){
                num.push(new Node(to_string(front_num % back_num)));
            }
        }
        source.pop();                                                                           // 不是丟掉運算子就是運算元
    }
    return stoi(num.getTop());                                                                  // 回傳字串stack中最後的數字（要轉type）
}


////////////////////////////////////////
/*
8 / 4 - 3 + 5 * 2 - 6 * 7
*/

/*
8 4 / 3 - 5 2 * + 6 7 *
-33
*/
////////////////////////////////////////
/*
1 * ( 2 + 3 ) * 4
*/

/*
1 2 3 + * 4 *
20
*/
/////////////////////////////////////////
/*
1 + 2 * 3
*/

/*
1 2 3 * +
7
*/
/////////////////////////////////////////
/*
9 + ( ( 1 + 2 ) * ( 3 * 4 ) + 7 ) / 5
*/

/*
9 1 2 + 3 4 * * + 7 * 5 /+
17
*/
