# include <bits/stdc++.h>
using namespace std;

int BS(vector<int>&, int);

int main(void){
    srand((unsigned) time(NULL));
    vector<int> sor={1, 3, 5, 21, 23, 35, 77, 99};  //set vector source
    for(int x :sor) cout<<x<<" ";
    cout<<endl;
    int tar = 0;
    cin>>tar;                                       //set target which you need to search
    int getAns = BS(sor, tar);                      //get index from binary-search function
    if(getAns == -1){
        cout<<"Not Found!"<<endl;
    }
    else{
        cout<<"The answer is: "<<getAns<<endl;
    }
    return 0;
}

int BS(vector<int>& sor, int tar){
    int left = 0, right = sor.size()-1;             //set left and right pointers
    while(left <= right){                           //if left bigger than right then not found
        int mid = ceil((left+right)/2);             //set middle is ceiling
        if(sor[mid] == tar) return mid;
        else if(sor[mid] < tar){                    //target bigger than middle, so target is on right side
            left = mid+1;
        }
        else{
            right = mid-1;                          //target smaller than middle, so target is on left side
        }
    }
    return -1;                                      //sadly, target isn't in vector
}