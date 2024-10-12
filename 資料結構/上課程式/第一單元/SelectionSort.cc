# include <bits/stdc++.h>
using namespace std;

int main(){
    srand((unsigned)time(NULL));        //random seed
    int num{0};                         //number of elements
    vector<int>sor{};                   //vector to store elements
    cin>>num;
    for(int i = 0; i<num; i++){         //random for each element
        sor.push_back(rand()%100+1);
    }
    for(int i = 0; i<num-1; i++){       //from begin to end-1
        int minNum = sor[i];            //suppose that first element is minimum
        for(int j = i+1; j<num; j++){   //test now and after now till end
            if(sor[j]<minNum){          //if found number smaller than minNum, change minNum
                sor[j] = minNum;
            }
        }
        if(sor[i] > minNum){            //if now smaller than minNum, swap
            swap(sor[i], minNum);
        }
    }
    for(int x : sor){                   //print answer to check
        cout<<x<<" ";
    }
    cout<<endl;
    return 0;
}