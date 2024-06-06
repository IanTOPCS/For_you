期末程設

---

Class and Objects

----

關於如果有member variable是以指標形式出現，該如何書寫
```
#include <bits/stdc++.h>
using namespace std;

class Rect{
private:
public://main可以直接改值
    int len;
    int *wid;//調皮
    Rect(int, int*);//參數型態記得改
    void show();
};

Rect::Rect(int len = 0, int *wid = nullptr){//第二個參數先指到空的位置
    this->len = len;
    this->wid = wid;
}

void Rect::show(){
    cout<<"Len : "<<(this->len)<<endl;
    cout<<"Wid : "<<*(this->wid)<<endl;//印出數值記得以"*"取值
}

int main(void){
    Rect sor;//創造物件
    sor.len = 6;//改變物件值
    sor.wid = new int(8);//指標指到無名的整數型態空間
    sor.show();
    return 0;
}
```
 
----

寫出copy construct，以取代default copy constructor
```
#include <bits/stdc++.h>
using namespace std;

class Rect{
private:
public:
    int len;
    int *wid;
    Rect(int, int*);//難度up up
    void show();
    Rect(const Rect&);//參數記得是取參數本身而非複製一份參數（以reference 的方式，也可稱之為共用同一個地址的變數）
};

Rect::Rect(int len = 0, int *wid = nullptr){
    this->len = len;
    this->wid = wid;
}

void Rect::show(){
    cout<<"Len : "<<(this->len)<<endl;
    cout<<"Wid : "<<*(this->wid)<<endl;
}

Rect::Rect(const Rect& sor){
    this->len = sor.len + 2;//本身是啥型態就對應啥型態，最後加上點東西確保真的有用到我寫的copy constructor
    this->wid = new int(*(sor.wid) +2);//因為是指標，指到新另出來的無名同型態空間，並加上點確認有改變的小新機W
}

int main(void){
    Rect sor;//創造第一個
    sor.len = 6;
    sor.wid = new int(8);
    
    Rect sor2 = sor;//啟動copy constructor

    sor.show();
    cout<<endl;
    sor2.show();
    cout<<endl;
    return 0;
}
```

----

使用高級串接技能：Method chaining
```
#include <bits/stdc++.h>
using namespace std;

class Rect{
private:
    int len;
    int wid;
public:
    Rect(int, int);
    Rect& setlen(int);
    Rect& setwid(int);
    void show();
};

void Rect::show(){
    cout<<"Len : "<<(this->len)<<endl<<"Wid : "<<(this->wid)<<endl;
}

Rect::Rect(int len = 0, int wid = 0){
    this->len = len;
    this->wid = wid;
}

Rect& Rect::setlen(int len){
    this->len = len;
    return *this;
}

Rect& Rect::setwid(int wid){//關注回傳值是回傳自己（以變數的形式）
    this->wid = wid;
    return *this;//this為指到自己的指標，指到的值就是自己
}

int main(void){
    Rect sor(1, 2);
    sor.show();

    sor.setlen(6).setwid(8);
    //Method chaining，連續啟動同一個class的member function
    //即自己setlen後再用自己的名義啟動setwid（因為是變數，所以用"."呼叫）
    cout<<endl;
    sor.show();
    
    return 0;
}
```

---

Inheritance（繼承）

<ul>
    <p>四個不可以繼承的東西</p>
    <li>constructor 和 destructor</li>
    <li>Operator overloading 的'='
        <strong>只有等於不可以</strong>
    </li>
</ul>

----

奇妙繼承規則：

|形式|具體|
|---|----|
|public|任何人都可以訪問、存取，包括main（main為外人），故多作為外人查看、修改本身class創造的object中protected與private資料|
|protected|只有自己、繼承的子類別可以訪問，外人不可以訪問、存取|
|private|僅限自己可以訪問、修改，子類別無論以何種形式繼承皆無法訪問修改|

----

個別介紹

----

|隨便沒有限制|以public方式繼承|
|------|------|
|**父類別（原本形式）** |**子類別（繼承後形式）**|
|public|public|
|protected|protected|
|private|**不接受訪問、存取**|

<hr>

練習使用public的繼承
```
#include <bits/stdc++.h>
using namespace std;

class shape{//父類別
public:
    double area;
    void show();
};

void shape::show(){
    cout<<(this->area)<<endl;
}

class circle:public shape{//子類別（circle），以public的方式繼承父類別（shape）
public:
    double radius;
};

int main(void){
    circle object;//創造子類別物件
    
    object.radius = 2.0;//main（外人）使用物件public member variable
    
    object.area = (object.radius * object.radius * acos(-1));
    //外人使用物件父類別public member variable
    //小知識~acos(-1) = 3.14159....
    
    object.show();
    return 0;
}
```

----

|隨便沒有限制|以protected方式繼承|
|------|------|
|**父類別（原本形式）** |**子類別（繼承後形式）**|
|public|**protected**|
|protected|protected|
|private|不接受訪問、存取|

----

|隨便沒有限制|以private方式繼承|
|------|------|
|**父類別（原本形式）** |**子類別（繼承後形式）**|
|public|**private**|
|protected|**private**|
|private|不接受訪問、存取|

----

以public繼承會怎樣：父類的public是我的public，父類的protected是我的protected

以protected繼承會怎樣：父類的public是我的protected，父類的protected是我的protected

以private繼承會怎樣：父類的public是我的private，父類的protected是我的private

**三種形式繼承private皆無權力訪問、修改**

```
#include <bits/stdc++.h>
using namespace std;

class shape{//父類別
public:
    int pub_member;
protected:
    int pro_member;
private:
    int pri_member;
};

class circle: public shape{//子類別以public方式繼承
public://設成public外人（main）才有權利訪問、存取
    void accessPub();//以此形式繼承（public）可以訪問父類別public
    void accessPro();//以此形式繼承（protected）可以訪問父類別protected
    // void accessPri();//以此形式繼承（private）無法訪問、存取
};

void circle::accessPub(){
    pub_member = 5;
    cout<<"OK and pubtected number is "<<pub_member<<endl;
}

void circle::accessPro(){
    pro_member = 6;
    cout<<"OK and protected number is "<<pro_member<<endl;
}

// void circle::accessPri(){//無權訪問父類private
//     pro_member = 7;
//     cout<<"OK and pritected number is "<<pri_member<<endl;
// }

int main(void){
    circle c;
    
    c.accessPub();//外人可使用類別public所有變數、函數
    cout<<endl;
    
    c.accessPro();
    cout<<endl;

    // c.accessPri();
    // cout<<endl;

    return 0;
}
```

---

建構子（constructor）
當有人用此class建構物件，自動呼叫

----

如果父類有建構子，子類繼承後會怎樣
（注意：只是呼叫父類建構子，並不是繼承，建構子不可以繼承）

新玩意：父類建構子protected也可以被呼叫
（一般為外人main建構物件，因為屬於外人，所以建構子多為public）

```
#include <bits/stdc++.h>
using namespace std;

class shape{
protected://有點神奇
    double area;
    shape();
};

shape::shape(){
    cout<<"Shape created"<<endl;
}

class circle: public shape{
public:
    double radius;
    circle();
};

circle::circle(){
    cout<<"Circle created"<<endl;
}

int main(void){
    circle c;
    return 0;
}

//ans:
//Shape created            父類先執行，stack最上層
//Circle created           父類執行完，換自己
```

到最底層後慢慢吐出結果，有如遞迴，最深處的會先pop出stack後執行上一層

----

值得注意的小錯誤：如果父類沒有default constructor
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    double area;
    shape(int);//關注重點
};

shape::shape(int area){//沒錯~只有一個參數版的constructor呦
    this->area = area;
    cout<<(this->area)<<" Parent class is ok ~"<<endl;
}

class circle: public shape{
public:
    double redius;
    // circle();
    circle(): shape(5){//代理建構子
        this->redius = 7;
        cout<<(this->redius)<<" Child class is ok ~"<<endl;
    };
};

// circle::circle(){//不可以用~因為會對應到default father constructor，但default被消失了（自己寫constructor後，default即失效）
//     this->redius = 0;
//     cout<<(this->redius)<<" Child class is ok ~"<<endl;
// }

int main(void){
    circle c;
    return 0;
}

//ans：
//5 Parent class is ok ~
//7 Child class is ok ~
```

樣板2
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    double area;
    shape(int);
};

shape::shape(int area){
    this->area = area;
    cout<<(this->area)<<" Parent class is ok ~"<<endl;
}

class circle: public shape{
public:
    static double redius;//試試看static會怎樣
    // circle();
    circle(): shape(this->redius){
        this->redius = 7;
        cout<<(this->redius)<<" Child class is ok ~"<<endl;
    }
};

double circle::redius = 6;//static定義只能在外面呦

// circle::circle(){
//     this->redius = 0;
//     cout<<(this->redius)<<" Child class is ok ~"<<endl;
// }

int main(void){
    circle c;
    return 0;
}

//ans：
//6 Parent class is ok ~
//7 Child class is ok ~

```

---

copy constructor
當兩個相同class創造的object使用=時，該怎麼操作

----

重點：如果父類別有copy constructor就會使用父類，
剩下沒有的部分自己使用default copy constructor （於自己沒有寫copy constructor時）
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    int x;
    shape(){}
    shape(const shape&);//告訴我創造同類物件時，如果要複製同類物件該如何複製
};

shape::shape(const shape& sor){//確認有動作
    this->x = (sor.x + 2);
}

class circle: public shape{
public:
    int y;
};

int main(void){
    circle c1;
    c1.x = 10;
    c1.y = 20;

    // circle c2 = c1;           //與下相同
    circle c2(c1);               //與上相同
    
    cout<<"c1 = "<<c1.x<<" "<<c1.y<<endl;
    cout<<"c2 = "<<c2.x<<" "<<c2.y<<endl;
    return 0;
}
```

----

如果我自己也定義了copy constructor那會怎樣
：當同類物件在創造時使用'='會執行自己copy constructor，不會跟父類別有關係
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    int x;
    shape(){}
    shape(const shape&);
};

shape::shape(const shape& sor){
    this->x = (sor.x + 2);
}

class circle: public shape{
public:
    int y;
    circle(){}
    circle (const circle&);
};

circle::circle(const circle& sor){
    this->x = (sor.x + 3);
}

int main(void){
    circle c1;
    c1.x = 10;
    c1.y = 20;

    // circle c2 = c1;
    circle c2(c1);
    
    cout<<"c1 = "<<c1.x<<" "<<c1.y<<endl;
    cout<<"c2 = "<<c2.x<<" "<<c2.y<<endl;
    return 0;
}

```
ans：
![image](https://hackmd.io/_uploads/SJdaagqf0.png)
可知在自己寫了copy constructor後，沒寫到的就是亂給值，除非其變數以static定義值
（原理：static屬於class而非object，以static令出的變數只有一個記憶體空間）

像這樣
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    int x;
    shape(){}
    shape(const shape&);
};

shape::shape(const shape& sor){
    this->x = (sor.x + 2);
}

class circle: public shape{
public:
    static int y;
    circle(){}
    circle (const circle&);
};

int circle::y = 200;

circle::circle(const circle& sor){
    this->x = (sor.x + 3);
}

int main(void){
    circle c1;
    c1.x = 10;
    c1.y = 20;     //覆蓋掉200

    // circle c2 = c1;
    circle c2(c1);
    
    cout<<"c1 = "<<c1.x<<" "<<c1.y<<endl;
    cout<<"c2 = "<<c2.x<<" "<<c2.y<<endl;
    return 0;
}

//ans：
//c1 = 10 20
//c2 = 13 20
```


模板2
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    int x;
    shape(){}
    shape(const shape&);
};

shape::shape(const shape& sor){
    this->x = (sor.x + 2);
}

class circle: public shape{
public:
    int y;
    circle(){}
    circle (const circle&);
};

circle::circle(const circle& sor){
    this->x = (sor.x + 3);
    this->y = (sor.y + 3);
}

int main(void){
    circle c1;
    c1.x = 10;
    c1.y = 20;

    // circle c2 = c1;
    circle c2(c1);
    
    cout<<"c1 = "<<c1.x<<" "<<c1.y<<endl;
    cout<<"c2 = "<<c2.x<<" "<<c2.y<<endl;
    return 0;
}

//ans：
//c1 = 10 20
//c2 = 13 23
```

----

遮蔽效應：shadow
如果父類與子類有同名變數怎麼辦
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    int x;
};

class circle: public shape{
public:
    double x;
    void showx();
};

void circle::showx(){
    cout<<x<<endl;
    cout<<shape::x<<endl;//因為繼承，可以訪問父類同名變數，以此方式說明指定事父類變數而非我自己的
}

int main(void){
    circle c;
    c.x = 8.7;//我自己是double型態
    c.shape::x = 8.7;//父類別是int型態，所以存入值應為8
    c.showx();
    return 0;
}
//ans：
//circle::x = 8.7
//shape::x = 8
```

比較觀念
訪問class中static變數
觀念：（static在runtime就被建立，無關於物件是否創建，地址永遠不變）
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    static int x;//注意我
};
int shape::x = 0;//在外面初始化，這是規定

class circle: public shape{
public:
    double x;
    void showx();
};

void circle::showx(){
    cout<<x<<endl;
    cout<<shape::x<<endl;
}

int main(void){
    circle c;
    c.x = 8.7;
    shape::x = 8.7;//直接訪問class中static變數
    c.showx();
    return 0;
}
```

---

Member function
（此章著重於複寫override的發生）

----

當子類與父類有同名函數，發生覆寫，只有子類會被執行，
可以理解為子類優先級高於父類
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    double area;
    void draw();
};

void shape::draw(){
    cout<<"Drawing a shape"<<endl;
}

class circle: public shape{
public:
    double reaius;
    void draw();
};

void circle::draw(){
    cout<<"Drawing a circle"<<endl;
}

int main(void){
    circle c;
    c.draw();
    c.shape::draw();//指定要選擇從父類繼承的同名函數
    return 0;
}

//ans：
Drawing a circle
Drawing a shape
```

---

Polymorphism（多形）
重點：一定只能以指標實現

|Compile time polymorphism|Runtime polymorphism|
|-------------------------|--------------------|
|Function overloading 函數多載|Virtual function 虛擬函式|
|Operator overloading 運算子多載||

<hr>

<ol>
    <li>
        <strong>Compile time polymorphism</strong>
    </li>
    <ul>
        <li>
            Function overloading：
            參數個數不同 或 相同參數個數但型態不同的<strong>同名函示</strong>
        </li>
        <li>
            Operator overloading：
            以相同運算子賦與更多自訂義的功能
        </li>
    </ul>
    <li>
        <strong>Runtime polymorphism</strong>
    </li>
    <ul>
        <li>
            Virtual function：
            以父類別創造指標，指向子類別同名函式
        </li>
    </ul>
</ol>

----

基礎版：子類與父類有同名函式
觀念：子類override父類同名函式
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    int x = 3;
    void show();
};
void shape::show(){
    cout<<"Shape x: "<<x<<endl;
}

class circle: public shape{
public:
    int x = 5;
    void show();
};
void circle::show(){
    cout<<"Circle x: "<<x<<endl;
}

int main(void){
    circle *c = new circle();//多行必用指標
    c->show();//呼叫同名函式，此時子類override父類同名函
    shape* s = new shape();
    s->show();//父類自己呼叫自己有的函示
    return 0;
}

//ans：
//Circle x: 5
//Shape x: 3
```

----

進階觀念：以父類指標指向子類物件
重點：**只有父類可以指向子類，子類不可以指向父類**
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    int x = 3;
    void show();
};
void shape::show(){
    cout<<"Shape x: "<<x<<endl;
}

class circle: public shape{
public:
    int x = 5;
    void show();
};
void circle::show(){
    cout<<"Circle x: "<<x<<endl;
}

int main(void){
    shape* s = new circle();//父類指向子類
    s->show();//此時指標型態為父類，啟動父類自己函示
    ((circle*)s)->show();//轉型成子類型態，以子類override父類同名函式
    return 0;
}

// ans:
// shape x: 3
// Circle x: 5
```

----

Virtual function
噁心新觀念

----

正確的寫法
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    virtual double area();//我不一樣呦
    //被呼叫後發現為virtual function所以自動對應到相應的子類別同名函式
};

double shape::area(){
    return 0;
}

class circle: public shape{
public:
    double radius;
    double area();
};

double circle::area(){
    return acos(-1)*radius*radius;
}

class squre: public shape{
public:
    double side;
    double area();
};

double squre::area(){
    return side*side;
}

double getArea(shape* s){
    return s->area();//呼叫父類別
}

int main(void){
    circle c;
    c.radius = 5;
    cout << "Area of circle is: " << getArea(&c)<< endl;

    squre s;
    s.side = 6;
    cout<< "Area of square is: " << getArea(&s)<< endl;

    return 0;
}
//ans：
//Area of circle is: 78.5398
//Area of square is: 36
```

模板2 （比較學習
為何錯誤？
```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    double area();//我不一樣呦
    //被呼叫後發現非virtual function，又型態為父類，未經轉型，故啟動自己函示
};

double shape::area(){
    return 0;
}

class circle: public shape{
public:
    double radius;
    double area();
};

double circle::area(){
    return acos(-1)*radius*radius;
}

class squre: public shape{
public:
    double side;
    double area();
};

double squre::area(){
    return side*side;
}

double getArea(shape* s){
    return s->area();//此時呼叫父類別
}

int main(void){
    circle c;
    c.radius = 5;
    cout << "Area of circle is: " << getArea(&c)<< endl;

    squre s;
    s.side = 6;
    cout<< "Area of square is: " << getArea(&s)<< endl;

    return 0;
}
//ans：
//Area of circle is: 0
//Area of square is: 0
```

----

最終解：pure virtural function

>觀念：有著pure virtural function的class無法產生物件
且繼承的子類一定要實作父類別所有的pure virtual function否則也無法產稱物件

```
#include <bits/stdc++.h>
using namespace std;

class shape{
public:
    virtual double area() = 0;    //我不一樣呦
};

class circle: public shape{
public:
    double radius;
    double area();
};

double circle::area(){
    return acos(-1)*radius*radius;
}

class squre: public shape{
public:
    double side;
    double area();
};

double squre::area(){
    return side*side;
}

int main(void){
    shape *target = nullptr;//以父類別產生指標

    target = new circle();//父類別指標指向子類別創造的無名物件
    ((circle* )target)->radius = 5;//父類別不具此member variable，要記得轉型
    cout << "Area of circle is: " << target->area()<< endl;
    //以父類別指標呼叫pure virtual function會對應到子類別同名函式

    delete target;//避免memery leak

    target = new squre();
    ((squre* )target)->side = 6;
    cout<< "Area of square is: " << target->area()<< endl;

    return 0;
}

//ans：
//Area of circle is: 78.5398
//Area of square is: 36
```

---

Operator Overloading
運算子重載
觀念：operator 為一個 function

重點：不可以對基本型態做operator overloading

重點：不可多載的運算子
|長相|功用|
|---|----|
|::|範圍解析|
|.|	成員選取|
|sizeof|問多大|
|.\*|成員指標選取|
|?:|條件|
|#|前置處理器轉換成字串|
|##|前置處理器串連|

----

**絕對不可以<mark>對基本型態做運算子重載</mark>**
以下說明，這是錯誤的code：假設對基本型態（int）做operator overloading會怎樣
**參數中至少一者為自己定義的class創造的object或列舉eumerated類型才行**

```
#include <bits/stdc++.h>
using namespace std;

int operator+(int a, int b){//兩個參數都是基本型態，不可以的操作
    return (a+b+1);
}

int main(void){
    int a {0}, b{3};
    cout << a+b << endl;//a與b兩者皆為基本型態，基本型態運算已定，不可以重載
    return 0;
}
```
![image](https://hackmd.io/_uploads/BJHaKSjGA.png)
說明：因為是a與b啟動operator+，而a與b是基本型態，不可以做
<hr>
相對而言，正確的寫法

```
#include <bits/stdc++.h>
using namespace std;

class module{
private:
    int x;
    int y;
public:
    module(int, int);
    module operator+(const module&)const;
    void print()const;
    module(const module&);
};

module::module(const module& other){
    this->x = other.x;
    this->y = other.y;
}

module::module(int a = 0, int b = 0){
    this->x = a;
    this->y = b;
}

module module::operator+(const module& other)const{
    return module((this->x + other.x), (this->y + other.y));
}//定義兩個object相加，回傳無名物件

void module::print()const{
    cout<<"x = "<<(this->x)<<endl;
    cout<<"y = "<<(this->y)<<endl;
}
int main(void){
    module m1(2, 3);
    module m2(4, 5);
    module m3(6, 7);
    module m4 = m1 + m2 + m3;//兩個物件相加，非基本型態
    //加完使用copy constructor將兩個object連接
    m4.print();
    return 0;
}
```
<h4>以結果而言：</h4>

產生6個物件，兩個無名的物件（用在m1+m2+m3），四個有名字的物件

<h4>小細節：</h4>

因為相加，不會想要改到傳進去的東西，故最好是造一個新的物件等於兩者相加的結果，雖然比較占記憶體，但較為合理

----

小於的比較
```
#include <bits/stdc++.h>
using namespace std;

class rect{
public:
    double len;
    double wid;
    bool operator<(const rect& )const;
};

bool rect::operator<(const rect& sor) const{    //參數const：傳進來的參數是不會被改的
    複習~函示const，表示此函示保證不修改任何東西
    return ((this->len)*(this->wid))<(sor.len*sor.wid);
}

int main(void){
    rect r1;
    r1.len = 3, r1.wid = 3;
    rect r2;
    r2.len = 2, r2.wid = 5;
    if(r1<r2){//operator< is called here
        cout<<"rect1 < rect2"<<endl;
    }
    return 0;
}
```

----

<h4>
    一些奇怪的小知識增長了（懶惰鬼天地）
</h4>

```
#include <bits/stdc++.h>
using namespace std;
using namespace rel_ops;//偷吃步小方法，只要寫<和==就行

class rect{
public:
    double len;
    double wid;
    bool operator<(const rect&)const;
    bool operator==(const rect&)const;
    rect(double, double);
};

rect::rect(double l = 0, double w = 0){
    this->len = l;
    this->wid = w;
}

bool rect::operator<(const rect& other)const{
    return ((this->len)*(this->wid)) < ((other.len)*(other.wid));
}

bool rect::operator==(const rect& other)const{
    return ((this->len)*(this->wid)) == ((other.len)*(other.wid));
}

int main(void){
    rect r1(3, 4);
    rect r2(2, 4);
    if(r1 != r2) cout<<"We are not equal"<<endl;      //沒寫但可以運作
    if(r1 > r2) cout<<"r1 is greater than r2"<<endl;  //沒寫但可以運作
    return 0;
}
```

----

"非"怎麼書寫
```
#include <bits/stdc++.h>
using namespace std;

class cmp{
private:
    int inner;
public:
    cmp(int);
    bool operator!()const;
    void print()const;
};

cmp::cmp(int x = 0){
    this->inner = x;
}

bool cmp::operator!()const{     //如何描述反向
    if(inner > 0) return false; // true to false
    else return true;           // false to true
}

void cmp::print()const{
    if(!(*this)) cout<<"false to true"<<endl;  //針對物件反向，體現operator overloading
    else cout<<"true to false"<<endl;
}

int main(void){
    int num {0}; cin>>num;
    cmp tar(num);
    tar.print();
    return 0;
}
```

----

<h4>物件怎麼用陣列寫法</h4>

```
#include <bits/stdc++.h>
using namespace std;

class to_slice{
private:
    int num;
    vector<char> sor;
public:
    to_slice(int num);
    void cauculate();
    void print()const;
    char operator[](int)const;
};

to_slice::to_slice(int num = 0){
    this->num = num;
}

void to_slice::cauculate(){
    string target = to_string(this->num);
    for(int i = 0; i<target.size(); i++){
        sor.push_back(target[i]);
    }
}

char to_slice::operator[](int index)const{//第幾個index是甚麼內容
    assert((index >= 0) && (index < sor.size()));//阻擋取用
    return sor[index];//用原本就定義好的[]回傳
}

void to_slice::print()const{
    for(int i = 0; i<sor.size(); i++){
        cout<<(*this)[i]<<" ";//體現用物件的[]來取用，而不是用內建的[]~operator overloading
    }
    cout<<endl;
}

int main(void){
    int num{0}; 
    cin>>num;
    to_slice now(num);
    now.cauculate();
    now.print();
    int index{0}; 
    cin>>index;
    cout<<now[index]<<endl;//實現operator overloading
    return 0;
}
```

----

<h2>Method Chaining觀念運用</h2>
<h4>搞清楚operator=回傳有沒有reference的差別<br><br>
已每個地址確認過，GUN compiler就是如此</h4>

```
#include <bits/stdc++.h>
using namespace std;

class fun{
private:
    int num;
public:
    // fun operator=(const fun&);
    fun& operator=(const fun&); //回傳值有&
    fun(int num);
    void print()const;
};

fun::fun(int num = 0){
    this->num = num;
}

// fun fun::operator=(const fun& other){
//     this->num = other.num;
//     return *this; //回傳一個與自己相同的物件
// }

fun& fun::operator=(const fun& other){//回傳值有&
    this->num = other.num;
    return *this; //回傳一個與自己相同的物件
}

void fun::print()const{
    cout<<"num = "<<(this->num)<<endl;
}

int main(void){
    fun f1(10);
    f1.print(); //印出f1

    fun f2(20);
    f2.print(); //印出更改前的f2

    fun f3(30);
    f3.print();
    
    cout<<endl<<"f1 = f2 = f3"<<endl;
    f3 = f2 = f1;    //將f1的數值複製到f2
                     //如果operator=回傳值沒有&，即 f2 = f1 是做出與f1內容相同的新無名物件，再與f3做一次operator=，因為新物間內容與f1相同，所以將內容複製給f3也沒問題，只是又做了內容相同的新無名物件
                     //如果operator=回傳值有&，即 f2 = f1 回傳的是f2，因為f2值與f1相同，再與f3做operator=，f3就會與f2值相同，最後回傳f3
    cout<<"f1 : ";
    f1.print();
    cout<<"f2 : ";
    f2.print();
    cout<<"f3 : ";
    f3.print();
    return 0;
}
```

----

<h3>再再一次的Method Chaining觀念強調</h3>

<h4>如果沒有使用&會怎樣呢？</h4>

```
#include <bits/stdc++.h>
using namespace std;

class fun{
private:
    int len;
    int wid;
public:
    fun(int, int);
    fun setlen(int);
    fun setwid(int);
    void print();
};

void fun::print(){
    cout<<"Length: "<<(this->len)<<" and Width: "<<(this->wid)<<endl;
}

fun::fun(int len = 0, int wid = 0){
    this->len = len;
    this->wid = wid;
}

fun fun::setlen(int len){
    this->len = len;
    return *this;
}

fun fun::setwid(int wid){
    this->wid = wid;
    return *this;
}

int main(void){
    fun obj(5, 10);
    cout<<"Before : ";                   // Before : Length: 5 and Width: 10
    obj.print();                         //確認constructor有好好工作
    
    cout<<"After : ";
    obj.setlen(15).setwid(20).print();   // After : Length: 15 and Width: 20
                                         //雖印出結果正確，但因為setlen與setwid都不是回傳自己記憶體的參照（共用同一個記憶體空間的不同名變數），
                                         //以obj啟動setlen，正確改道obj物件的len，但回傳內容相同的無名物件，
                                         //其啟動setwid，再回傳與此無名物件內容相同的另一無名物件（len：15 wid：20），
                                         //最後以此無名物件啟動print，不回傳任何東西
    cout<<"Object inner ";
    obj.print();                         // Object inner Length: 15 and Width: 10
                                         //清楚呈現出obj只有len被改到
    
    return 0;
}
```

<hr>
<h4>那~如果有&又會怎樣呢</h4>

```
#include <bits/stdc++.h>
using namespace std;

class fun{
private:
    int len;
    int wid;
public:
    fun(int, int);
    fun& setlen(int);    //加上&
    fun& setwid(int);    //加上&
    void print();
};

void fun::print(){
    cout<<"Length: "<<(this->len)<<" and Width: "<<(this->wid)<<endl;
}

fun::fun(int len = 0, int wid = 0){
    this->len = len;
    this->wid = wid;
}

fun& fun::setlen(int len){    //回傳與自己記憶體相同的不同名變數
    this->len = len;
    return *this;
}

fun& fun::setwid(int wid){    //回傳與自己記憶體相同的不同名變數
    this->wid = wid;
    return *this;
}

int main(void){
    fun obj(5, 10);
    cout<<"Before : ";
    obj.print();                         //length 5 and width 10
    cout<<"After : ";
    obj.setlen(15).setwid(20).print();   //length 15 and width 20
                                         //以obj啟動setlen，回傳自己（共用記憶體空間的同名變數，就是我自己）
                                         //再用obj自己啟動setwid，回傳自己，
                                         //在再調用自己的print
    cout<<"Object inner ";
    obj.print();                         //length 15 and width 20
                                         //真的真的真的是改到自己呦
    return 0;
}
```

<hr>
<h4>非常不幸~笨笨的你看到這裡還不懂...乖乖用指標，啥都別想了</h4>

```
#include <bits/stdc++.h>
using namespace std;

class fun{
private:
    int len;
    int wid;
public:
    fun(int, int);
    fun* setlen(int);     //回傳指標，這裡指回傳自己的記憶體位置
    fun* setwid(int);     //回傳指標，這裡指回傳自己的記憶體位置
    void print();
};

void fun::print(){
    cout<<"Length: "<<(this->len)<<" and Width: "<<(this->wid)<<endl;
}

fun::fun(int len = 0, int wid = 0){
    this->len = len;
    this->wid = wid;
}

fun* fun::setlen(int len){   //我不一樣呦~
    this->len = len;
    return this;             //回傳指到自己的指標，意思是this指到我自己，this存的值就是自己的記憶體位置
}

fun* fun::setwid(int wid){
    this->wid = wid;
    return this;
}

int main(void){
    fun obj(5, 10);
    cout<<"Before : ";
    obj.print();                           //length 5 and width 10
    cout<<"After : ";
    obj.setlen(15)->setwid(20)->print();   //length 15 and width 20
                                           //以obj物件發動setlen，回傳自己記憶體位置，
                                           //此時是指標型態，指標存的值是自己的記憶體位置，用->調用自己setwid
                                           //此時依然是指標型態，調用自己print
                                           //最後不回傳任何東西結束這回合
    cout<<"Object inner ";
    obj.print();                           //length 15 and width 20
                                           //以物件型態obj調用print，不回傳任何東西
    return 0;
}
```

----

<h2>大統整</h2>

<h3>有無&會怎樣</h3>

|有&|沒有&|
|---|----|
|**回傳自己**<br>回傳與自己共用相同記憶體空間的不同名變數<br>在這裡傳進來的與回傳的都是相同名字|回傳與自己內容相同的**另一個無名物件**<br><mark>存在潛在風險</mark>，希望更改但未更改<br>**小心使用**|
<hr>
<h3>指標與非指標</h3>

>重拾觀念：指標就是變數，只是存的東西是**地址**

|變數型態|指標型態|
|-------|------|
|就直接創<br>int<br>float<br>double<br><mark>自己定的class</mark><br>...|即變數型態加上*|
|以**變數**取值<br>int a = 0;<br>a = 9;|以\*取值<br>int \*a = nullptr;<br>a = new int(9);<br>\*a = 87;|
|以&調取變數地址<br>int a = 3;<br>cout<<&a<<endl;|把自己當變數調取即可取道地址<br>int \*a = nullptr;<br>a = new int(9);<br>cout<<a<<endl;|

<h4>重點：當指標使用&與不使用&（取址的意思）是不同的呦</h4>

|使用&|不使用&|
|----|------|
|取到**指標本身**的地址<br>而非所存變數的地址|即取**所存變數的地址**|
| int \*a = nullptr;<br>a = new int(9);<br>cout<<&a<<endl;<br>&a是指標a的地址<br> |int \*a = nullptr;<br>a = new int(9);<br>cout<<a<<endl;<br>a是令出新空間的地址<br>|
<hr>

><h3>this是什麼？</h3>
>this是指到自己物件的指標
|存甚麼|調用方式|
|-----|-------|
|存自己地址|與**指標**相同|
<h3>
    所以~&this與this記憶體位置是不同的喔
</h3>

----

<h4>如何轉型物件</h4>

```
#include <bits/stdc++.h>
using namespace std;

class fun{
private:
    double number;
public:
    operator int();
    fun(double);
    fun(const fun&);
    void print();
};

fun::fun(double num = 0){
    this->number = num;
}

fun::fun(const fun& other){
    this->number = other.number;
}

fun::operator int(){
    return static_cast<int>(this->number);
}

void fun::print(){
    cout<<"Number : "<<(this->number)<<endl;
}

int main(void){
    fun f1(3.14);
    f1.print();
    fun f2 = int(f1)+3.14; //對物件進行轉型後為int + int，為基本型別，故不用operator+
                           //最後使用copy constructor複製一個新的物件給f2
    f2.print();

    return 0;
}
```

----

<h3>Function object（Functor）</h3>

>觀念：將class所創的物件如同function般呼叫
>即只要寫出名字（物件名）和參數（如同function用'()'包在一起）即可

```
#include <bits/stdc++.h>
using namespace std;

class roundArea{
public:
    double operator()(double, double);  //overloading () operator，使得类可以像函数一样被调用
    roundArea(){}                       //default constructor
    void calculate(double, double);
};

double roundArea::operator()(double r1, double r2){  //重點：因為overloading過()所以可以以物件呼叫
    return (acos(-1)*r1*r2);
}

void roundArea::calculate(double r1, double r2){
    double area = (*this)(r1, r2);     //物件调用() operator，實現function object的理念，把类看成function
    cout<<area<<endl;
}

int main(void){
    roundArea ans;         //以default constructor初始化ans
    ans.calculate(3, 4);   //调用calculate函数
    return 0;
}
```

---

<h3>
    Template 模板
</h3>

----

<p>
    <mark><strong>超級重要的細節</strong></mark>關於default value這回事
</p>

><h2>以下開始</h2>

<hr>

<p>最一般的，證明<mark>default value寫在定義就可以了</mark></p>
    
```
int add(int a = 0, int b = 0);  //default value 寫在定義

int main(void){
    cout<<add()<<endl;
}

int add(int a, int b){
    return (a+b);
}

ans: 0
```
<hr>
<p>進階~換成<mark>class</mark></p>

```
class myclass{
private:
    int num;
public:
    myclass(int num = 0);        //default value寫在定義
    int add(int input = 0);      //default value寫在定義
};

myclass::myclass(int num){       //不須重複default value
    this->num = num;
}

int myclass::add(int input){
    return ((this->num) + input);
}

int main(void){
    myclass sor;                //使用default value的建構子
    cout<<sor.add()<<endl;
    return 0;
}

ans: 0
```

<hr>

<p>
    <i>function template</i>再提升一下
</p>

```
template<typename T>
T add(T a = 0, T b = 0);            //於定義宣告default value

int main(void){
    int a{4}, b{6};
    cout<<add<int>()<<endl;         //使用default value的function template
    cout<<add<int>(a, b)<<endl;
    return 0;
}

template<typename T>
T add(T a, T b){                    //描述函示，不需要再寫default value
    return (a + b);
}

ans: 0
     10
```
<hr>
<h4>
    真的真的真的最後了
</h4>
<h2>
    <i>class template</i>
</h2>

```
#include <bits/stdc++.h>
using namespace std;

template<class T>
class myclass{
private:
    T num;
public:
    myclass(T num = 0);            //默認參數需要放在類別定義裡面
    T add(T input = 0);
};

template<class T>
myclass<T>::myclass(T num){
    this->num = num;
}

template<class T>
T myclass<T>::add(T input){
    return ((this->num) + input);
}

int main(void){
    myclass<int> sor;           //使用defalut value建構子
    cout<<sor.add()<<endl;      //使用default value 的 add函示

    myclass<double> sor2(1.2);  //替換default value，用同一個建構子建構
    cout<<sor2.add(2.3)<<endl;  //替換default value，用add函示加上2.3

    return 0;
}

```
<hr>
<h1>
    恭喜~~結束惹W
</h1>

<p>
    總結
</p>

|   |一般function|一般class|function template|class template|
|---|------------|--------|-----------------|--------------|
|default value<br>使用方式|1.於定義宣告<br>2.定義只宣告型態，待實際實現函示功能再給默認值|與一般function一樣，有兩種方式|<strong>只能在定義給默認值</strong>|<strong>只能在定義給默認值</strong>|

>統整：不要手賤將default value寫在實現function、member function的地方，要寫default value 一律在定義就寫好

----

<p>勤奮小學生手賤一波：Ｐ</p>

><i>question：</i>如果寫了function template，又不在定義寫default value，寫在實現函示的地方，會過嗎~？

```
template<typename T>
T add(T, T);                      //這裡不給default value就不要用default value

int main(void){
    int a{4}, b{6};
    cout<<add<int>()<<endl;         
    cout<<add<int>(a, b)<<endl;
    return 0;
}

template<typename T>
T add(T a = 0, T b = 0){           //不准這樣做         
    return (a + b);
}

```
><i>Answer：</i>就是不可以...你TM能不能乖一點，compiler就是看不懂你在幹啥

![image](https://hackmd.io/_uploads/r1-AmTNm0.png)

<h1>再再宣導：default value一律寫在定義</h1>

----

<h3>課堂PPT開始~</h3>
<hr>
<p>複習以前學過的Template（funtion template）</p>

```
#include <bits/stdc++.h>
using namespace std;

template<class T>
int mymin(T data[], int size){                 //接受任意型態陣列，並傳入自己大小
    int index {0};                             //最小值的索引   
    for(int i = 0; i<size; i++){
        if(data[i]<data[index]){
            index = i;
        }
    }
    return index;
}

int main(void){
    int sor1[]{68, 27, 32};
    double sor2[]{1.2, 3.4, 5.6, 7.8, 9.0};
    cout<<mymin<int>(sor1, 3)<<endl;           //指定模板未定義型態T為int型態
                                               //寫法：呼叫名字，寫出定義型態T，寫出函示需要參數
    cout<<mymin<double>(sor2, 5)<<endl;        //指定模板未定義型態T為double型態
    return 0;
}
```

----

<p>
    以前的<strong>變形</strong>
</p>
<p>
    <mark>知道參數可以不用限定typename及class</mark>
</p>

```
#include <bits/stdc++.h>
using namespace std;

template<class T, int num = 78> //給定template default value，注意num屬於template而非class
class fun{
public:
    fun(int count = 22);        //給定class template的constructor default value
    int count;
    void print();
};

template<class T, int num>
fun<T, num>::fun(int count){
    this->count = count;
}

template<class T, int num>
void fun<T, num>::print(){
    cout<<"Count: "<<count<<endl;
    cout<<"num: "<<num<<endl;           //class template中可以使用template的參數num與T
}

int main(void){
    fun<int> sor;               //使用class template 中帶有default value的constructor
    sor.print();                //使用class template的member function

    // cout<<sor.num<<endl;     //問出以下問題
    
    return 0;
}

ans:22
    78

```
<hr>
<p>既然class template可以使用template中的參數，那外人可不可以透過class訪問template參數</p>

```
#include <bits/stdc++.h>
using namespace std;

template<class T, int num = 78> //給定template default value，注意num屬於template而非class
class fun{
public:
    fun(int count = 22);        //給定class template的constructor default value
    int count;
    void print();
};

template<class T, int num>
fun<T, num>::fun(int count){
    this->count = count;
}

template<class T, int num>
void fun<T, num>::print(){
    cout<<"Count: "<<count<<endl;
    cout<<"num: "<<num<<endl;           //class template中可以使用template的參數num與T
}

int main(void){
    fun<int> sor;               //使用class template 中帶有default value的constructor

    cout<<sor.num<<endl;         //報錯!!!!!!!!!!!!!!!!!!!!!!!!
    return 0;
}
```
><h2><mark>就是不可以</mark>，非class中的member variable</h2>
![image](https://hackmd.io/_uploads/SJSVo6N7R.png)

----

>在class template<strong>不能做</strong>的事：將cin / cout寫在一行內

```
#include <bits/stdc++.h>
using namespace std;

template<class T, int size = 2>
class Stack{
private:
    int count;
    T buffer[size];
public:
    Stack(int count = 0);
    int push(T);
    T pop();
    void print();
};

template<class T, int size>
void Stack<T, size>::print(){
    cout<<"Stack: ";
    for(int i = 0; i<count; i++){
        cout<<buffer[i]<<" ";
    }
    cout<<endl<<"Count: "<<(this->count)<<endl;
}

template<class T, int size>
Stack<T, size>::Stack(int count){
    this->count = count;
}

template<class T, int size>
int Stack<T, size>::push(T value){
    if((count-1) > size) return -1;
    else buffer[count++] = value;
    return count;
}

template<class T, int size>
T Stack<T, size>::pop(){
    if(count == 0) throw "Stack is empty";  //已經沒有東西了，拋出錯誤
    return buffer[--count];
}

int main(void){
    Stack<int> sor;

    //測試第一部分輸出，此輸出符合需求
    cout<<"First index :"<<sor.push(4)<<endl;
    cout<<"Second index:"<<sor.push(5)<<endl;
    cout<<"Third index :"<<sor.push(6)<<endl;
    cout<<endl;

    //測試第二部分輸出，此輸出不符合需求，會於期望的輸出呈現完全相反
    // cout<<sor.push(4)<<endl<<sor.push(5)<<endl<<sor.push(6)<<endl;
    // cout<<endl;

    sor.print();
    cout<<endl;

    while(1){
        try{                        //嘗試，即一定會做的事
            auto value = sor.pop();  //因為這裡用class template，回傳無法預期的type故交給compiler判斷
            cout<<value<<endl;
        }
        catch(const char* error){
            cout<<"Error: "<<error<<endl; //接到錯誤拋出，印出接到的東西（丟出字串，故用字串型態接）
            break;
        }
    }

    return 0;
}
```
正確輸出： 
![image](https://hackmd.io/_uploads/S1WVgR47C.png)
<hr>

錯誤輸出：
![image](https://hackmd.io/_uploads/HJQ9zRV70.png)

>可以看出整個放進去的方式就不符合期待，所以<mark>template的cin，cout不要寫在一起</mark>，順序會不符期待

----

<p>class template</p>
<p>將上一個範例陣列型態改成class</p>

```
#include <bits/stdc++.h>
using namespace std;

template<class T, int size = 2>           //給定default size value
class Stack{
private:
    int count;
    T buffer[size];
public:
    Stack(int count = 0);                //給定default value
    int push(T);
    int pop();
    void print();
};

template<class T, int size>
void Stack<T, size>::print(){
    cout<<"Stack: ";
    for(int i = 0; i<count; i++){
        cout<<buffer[i].id<<" ";
    }
    cout<<endl<<"Count: "<<(this->count)<<endl;
}

template<class T, int size>
Stack<T, size>::Stack(int count){
    this->count = count;
}

template<class T, int size>
int Stack<T, size>::push(T value){
    if((count-1) > size) return -1;
    else buffer[count++] = value;
    return count;
}

template<class T, int size>
int Stack<T, size>::pop(){                        //改變回傳值為int，回傳物件中id
    if(count == 0) throw "Stack is empty";
    return (buffer[--count].id);
}

class car{
public:
    int id;
    car(int id = 0);
};

car::car(int id){
    this->id = id;
}

int main(void){
    car c1(4), c2(5), c3(6);
    Stack<car, 2> sor;

    cout<<sor.push(c1)<<endl;
    cout<<sor.push(c2)<<endl;
    cout<<sor.push(c3)<<endl;

    sor.print();
    cout<<endl;

    while(1){
        try{
            auto value = sor.pop();
            cout<<value<<endl;
        }
        catch(const char* error){
            cout<<"Error: "<<error<<endl;
            break;
        }
    }

    return 0;
}
```
符合期待輸出：
![image](https://hackmd.io/_uploads/HyvEuC4XR.png)

----

<h2><i>Template specialization</i> 模板特化</h2>

|  |function template<br> specialization|class template<br> specialization|
|--|-----------------------------|---------------------------------|
|區別|只引許存在<mark>完全特化</mark>|1.完全特化<br>2.部分特化|
|理由|function overloading與完全特化很像，寫法也比較簡單|沒有任何東西叫做class overloading，<br>但做的事情也是修改參數類型<br>（僅限修改參數type，不可以修改參數數量）|
<hr>

<p>一次學習class template 特化</p>

此範例：因為訪問指標與訪問指標內的值是不同的，故需要特別注意（特殊行為）

```
#include <bits/stdc++.h>
using namespace std;

template<class T, class U>         //General template
class compare{
private:
public:
    bool check(T , U);
};

template<class T, class U>
bool compare<T, U>::check(T a, U b){
    if(a == b) return true;
    else return false;
}

template<class T>                 //partial specialization template for int*（部分特化模板）
class compare<T, int*>{           //沿用原class template的 T type，但将 U 类型限定为 int*，實現部分特化
private:
public:
    bool check(T, int*);
};

template<class T>
bool compare<T, int*>::check(T a, int* b){
    if(a == *b) return true;
    else return false;
}

template<>                      //full specialization template for int*（全特化模板）
class compare<int*, int*>{      //將T 类型限定為 int*，且将 U 类型限定為 int*，實現全特化，即參數全部修改
private:
public:
    bool check(int*, int*);
};

bool compare<int*, int*>::check(int* a, int* b){
    if(*a == *b) return true;
    else return false;
}

int main(void){
    cout<<boolalpha;

    int i1{6}, i2{8}, i3{8};
    int *p1{&i1}, *p2{&i2}, *p3{&i3};
    
    compare<int, int> c1;                 //general template
    cout<<c1.check(i1, i2)<<endl;
    cout<<c1.check(i2, i3)<<endl;

    compare<int, int*> c2;                //partial specialization template 
    cout<<c2.check(i1, p2)<<endl;
    cout<<c2.check(i2, p3)<<endl;

    compare<int*, int*> c3;                //full specialization template 
    cout<<c3.check(p1, p2)<<endl;
    cout<<c3.check(p2, p3)<<endl;
    return 0;
}
```
<P>答案</P>

![image](https://hackmd.io/_uploads/SkKEUyS70.png)
>為何寫到指標就需要特化？
<h3>GPT是你的好夥伴</h3>

特化一个类型的主要需求和场景包括性能优化、处理特定类型的特殊行为、处理不支持的类型、编译时元编程以及提供泛化接口的不同实现。通过使用模板特化，可以为特定类型提供定制的实现，从而提高代码的灵活性、性能和可维护性。

<P>function template</P>
<strong>沒有部分特化，只有重載</strong>

```
#include <bits/stdc++.h>
using namespace std;

template<typename T, typename P>           //generic template function宣告
void print(T, P);

template<typename T, typename P>           //實現function template （一般的形式）
void print(T t, P p){
    cout << t << " " << p << endl;
}

template<typename T>                        //以重載方式實現function template （名字前不必加'<>'，因為這行為非部分特化，是重載）
void print(T t, double *p, char c){
    cout<<t<<" "<<*p<<" "<<c<<endl;
}

template<>                                  //specialization for int* and double*（完全特化）
void print<int*, double*>(int *t, double *p){
    cout<<*t<<" "<<*p<<endl;
}

int main(void){
    int a{10}; double b{2.3}; char ch{'a'};
    int *pa = &a; double *pb = &b;

    print<int, double>(a, b);                             //function template，最一般的函示模板
    print(a, pb, ch);                                     //實現function overloading，修改變數type，增加變數數目
    print<int*, double*>(pa, pb);                         //實現function specialization，完全特化

    return 0;
}   
```
<hr>

<p>相較而言，如果不使用完全特化，也是可以全部使用重載</p>

```
#include <bits/stdc++.h>
using namespace std;

template<typename T, typename P>           //generic template function宣告
void print(T, P);

template<typename T, typename P>           //實現function template （一般的形式）
void print(T t, P p){
    cout << t << " " << p << endl;
}

template<typename T>                        //以重載方式實現function template （名字前不必加'<>'，因為這行為非部分特化，是重載）
void print(T t, double *p, char c){
    cout<<t<<" "<<*p<<" "<<c<<endl;
}
                                                
void print(int *t, double *p){              //實現function overloading，修改變數type                     //其實也跟完全特化長得差不多
    cout<<*t<<" "<<*p<<endl;
}

int main(void){
    int a{10}; double b{2.3}; char ch{'a'};
    int *pa = &a; double *pb = &b;

    print(a, b);                             //function template，最一般的函示
    print(a, pb, ch);                        //實現function overloading，修改變數type，增加變數數目
    print(pa, pb);                           //實現重載

    return 0;
}   
```

----

<h2>
    額外小知識~請問assert與static_assert有什麼差別
</h2>

><strong>Answer</strong>：assert再runtime時如果有錯誤才會停下<br>但是static_assert在compile time如果有錯就會報錯，<br>且錯誤訊息可以自己寫，較具可讀性。

<p>以下提供小小範例</p>

```
#include <bits/stdc++.h>
using namespace std;

template<class T>
class Equal{
private:
public:
    static_assert(!is_pointer<T>(), "Pointer type is not allowed.");    //知道指標地址不能比較，直接擋下來
                                                                        //不是指標才可以繼續往下做
    bool check(T data1, T data2){
        if(data1 == data2){
            return true;
        }
        else{
            return false;
        }
    }
};

int main(void){
    int i1 = 6, i2 = 8, i3 = 8;
    Equal<int> e1;
    cout<<boolalpha<<e1.check(i1, i2)<<endl;         // false
    cout<<boolalpha<<e1.check(i3, i2)<<endl;         // true
    Equal<double> e2;
    cout<<boolalpha<<e2.check(5.0, 3.0)<<endl;       // false
    cout<<boolalpha<<e2.check(5.0, 5.0)<<endl;       // true
    
    Equal<int*> e3;                             // Pointer type is not allowed. This will cause a compile-time error.
    cout<<boolalpha<<e3.check(&i1, &i2)<<endl;
    cout<<boolalpha<<e3.check(&i2, &i3)<<endl;
    return 0;
}
```
>當然~此題可以使用function overloading與function template完全特化處理掉

----

<p><i>algorithm</i>函示庫中其中兩個小小功能</p>

>比較陣列中的最小、最大項

```
#include <bits/stdc++.h>
using namespace std;

int main(void){
    int sor[]{30, 27, 19, 56, 72, 36};
    double sor2[]{3.6, 7.2, 8.5, 1.6, 9.1, 5.6};

    cout<<*(min_element(sor, sor+6))<<endl;    //sor中最小者，因為回傳是地址，取值使用'*'
    cout<<*(max_element(sor, sor+6))<<endl;     //sor中最大者
    cout<<*(min_element(sor2, sor2+6))<<endl;
    cout<<*(max_element(sor2, sor2+6))<<endl;
    return 0;
}

ans:19
    72
    1.6
    9.1
```

----

<p>沒東西講~開始套container</p>

<a href="https://cplusplus.com/reference/stack/stack/">Stack in Cplusplus</a>

```
#include <bits/stdc++.h>
using namespace std;

int main(void){
    stack<int> s;
    s.push(4);
    s.push(5);
    s.push(6);
    
    cout<<s.size()<<endl;
    while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
    }

    return 0;
}
```

---

<h2>First Class Function</h2>

>當一個function以<strong>參數</strong>的形式傳入另一個function，<br>即稱為<i>First Class Function</i>

----

<h4>Function Pointer 用指標指向函示第一個地址</h4>

```
#include <bits/stdc++.h>
using namespace std;

int sum(int a, int b){
    return a+b;
}

int product(int a, int b){
    return a*b;
}

int main(void){
    int (*pfunc)(int, int) = nullptr;    // 用指標指向function，在這裡初始化為nullptr
                                         // 這裡限制只能指向參數為int, int，且迴船值為int的function
                                         
    pfunc = sum;                          // 指標指向sum函數
    cout << pfunc(2, 3) << endl;          // 呼叫sum函數並輸出結果5

    pfunc = product;                      // 指標指向product函數
    cout << pfunc(2, 3) << endl;          // 呼叫product函數並輸出結果6
    return 0;
}
```

----

<h4>學會Function Pointer，就可以<mark>讓function變成參數</mark>實現高階函示</h4>

```
#include <bits/stdc++.h>
using namespace std;

void onokclick(){                         //callback function，因為其他function而被動觸發
    cout<<"OK"<<endl;
}

void oncancelclick(){                      //callback function，因為其他function而被動觸發
    cout<<"Cancel"<<endl;
}

void setonclick(void (*pfunc)() = nullptr){          //設定onclick function，預設為nullptr
    if(pfunc == nullptr) throw "No function to call";
    pfunc();
}

int main(void){
    try{
        setonclick();           //直接使用nullptr function，會出現未定義行為，使程式崩塌，因此在此加上try-catch
    }
    catch(const char* msg){
        cout<<msg<<endl;
    }
    setonclick(onokclick);       //使用onokclick function
    setonclick(oncancelclick);   //使用oncancelclick function
    return 0;
}
```
<hr>
><p>或return</p>

```
#include <bits/stdc++.h>
using namespace std;

void onokclick(){                         //callback function，因為其他function而被動觸發
    cout<<"OK"<<endl;
}

void oncancelclick(){                      //callback function，因為其他function而被動觸發
    cout<<"Cancel"<<endl;
}

void setonclick(void (*pfunc)() = nullptr){          //設定onclick function，預設為nullptr
    if(pfunc == nullptr){
        cout<< "No function to call"<<endl;
        return;
    }
    pfunc();
}

int main(void){
    setonclick();                //設定onclick function為nullptr
    setonclick(onokclick);       //使用onokclick function
    setonclick(oncancelclick);   //使用oncancelclick function
    return 0;
}
```
>callback function：類似一個按鈕，按了後會觸發啥（哪一個function）
>可視為~function是被動觸發，因為調用A function，被包含在其中的B function被觸發了 

---

<h2>
    First Class Function
</h2>

<ul>
    <li>
        <p>
            Callback Function：不由自己呼叫，通常由OS呼叫（EX:按鈕）
        </p>
    </li>
    <li>
        <p>
            Higher Order Function：當一個function將另一個function當變數引入的函示
        </p>
    </li>
    <li>
        <p>
            Lambda：當只需要使用一次，不需要特別給予名字的函示
        </p>
    </li>
</ul>

----

<h4>
    使用std::function方式寫出call back function與higher order function    
</h4>

```
#include <bits/stdc++.h>
using namespace std;

int sum(int, int);                                                          //call back function
int cal(int a, int b, function<int(int, int)>);                             //Higher order function

int main(void){
    int a = 10, b = 20;
    int result = cal(a, b, sum);
    cout << "Sum of " << a << " and " << b << " is " << result << endl;
    return 0;
}

int sum(int a, int b){
    return a + b;
}

int cal(int a, int b, function<int(int, int)>pfunc){                        //使用std::funcion包裝
    return pfunc(a, b);
}
```

----

>不要用std::function來寫class，還是使用古老版本（以下）就好

```
#include <bits/stdc++.h>
using namespace std;

class ex{
protected:
public: 
    int sum(int, int);                                                          //call back function
    // int cal(int a, int b, function<int(int, int)>);                          
    int cal(int a, int b, int(ex::*)(int, int));                                //Higher order function
    ex(){}
};


int main(void){

    ex obj;
    int a = 10, b = 20;
    int result = obj.cal(a, b, obj.sum);
    cout << "Sum of " << a << " and " << b << " is " << result << endl;
    return 0;
}

int ex::sum(int a, int b){
    return a + b;
}

// int ex::cal(int a, int b, function<int(int, int)>pfunc){                        //使用std::funcion包裝
//     return pfunc(a, b);
// }

int ex::cal(int a, int b, int(ex::*pfunc)(int, int)){
    return (this->*pfunc)(a, b);
}
```

---

<h2>
    Lambda Expression書寫方式
</h2>

----

<h4>
    一次看懂Lambda書寫方式    
</h4>

```
#include <bits/stdc++.h>
using namespace std;

int cal(int, int, int(*)(int, int));
int sum(int, int);

int main(void){
    cout<<cal(3, 5, sum)<<endl;                                 //使用higher-order function
    cout<<cal(3, 5, [](int a, int b){return (a+b);})<<endl;      //使用lambda function

    int x = 7, y = 3;
    auto fun0 = [&](){return x+y;};                               //使用lambda function，當使用到外面參數，選擇[=]或[&]
    cout<<fun0()<<endl;                                           //使用lambda function [&]，第一次copy即取xy的變數'地址'  

    auto fun1 = [=](){return x+y;};                               //使用lambda function，當使用到外面參數，選擇[=]或[&]
    x = 10, y = 5;                                                //修改xy的值，但fun1仍使用第一次copy的xy值
    cout<<fun1()<<endl;                                           //使用lambda function [=]，第一次copy即取xy的變數'值'
    cout<<fun0()<<endl;                                           //使用lambda function [&]，第一次copy即取xy的變數'地址'
    return 0;
}

int cal(int a, int b, int(*pfunc)(int, int)){
    return pfunc(a, b);
}

int sum(int a, int b){
    return (a+b);
}
```

----

<h4>
    統整Lambda
</h4>

<table>
    <tr>
        <td>
        </td>
        <td>
            =
        </td>
        <td>
            &
        </td>
    </tr>
    <tr>
        <td>
            差別
        </td>
        <td>
            第一次執行時copy內在需要引入外面變數的<strong>值</strong><br>故以後即使修改外面變數，<br>依然使用第一次copy到的值
        </td>
        <td>
            第一次執行時copy內在需要引入外面變數的<strong>地址</strong><br>故即使以後修改了，由外在引入的變數也會跟著修改
        </td>    
    </tr>
</table>

----