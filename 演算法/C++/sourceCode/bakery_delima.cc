#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Order{
public:
    int day;
    int penalty;
    int index;
    Order(int day = 0, int penalty = 0, int index = 0);
};

Order::Order(int day, int penalty, int index){
    this->day = day;
    this->penalty = penalty;
    this->index = index;
}

bool compareOrders(const Order& a, const Order& b) {
    long long ratioA = (long long)a.penalty * b.day;
    long long ratioB = (long long)b.penalty * a.day;
    
    if (ratioA == ratioB) {
        return a.index < b.index;
    }
    return ratioA > ratioB;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Order> orders;
    
    for (int i = 0; i < n; i++) {
        int d{0}, p{0}, idx{(i+1)};
        cin >> d >> p;
        orders.push_back(Order(d, p, idx));
    }
    
    sort(orders.begin(), orders.end(), compareOrders);
    
    long long totalPenalty = 0;
    int elapsedDays = 0;
    
    for (const auto& order : orders) {
        totalPenalty += (long long)order.penalty * elapsedDays;
        elapsedDays += order.day;
    }
    
    for (int i = 0; i < n; i++) {
        cout << orders[i].index<<" ";
    }
    cout << endl;
    
    return 0;
}

/*
17
34 8
7 12
7 4
63 2
5 5
27 96
70 4
60 60
29 29
20 75
55 33
25 61
87 99
54 28
59 34
39 22
72 67
*/