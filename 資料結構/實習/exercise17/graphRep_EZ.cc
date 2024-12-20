# include <bits/stdc++.h>
using namespace std;

# define room 10000

int sor[room][room];

int main(void){
    for(int i = 0; i<room; i++){
        for(int j = 0; j<room; j++){
            sor[i][j] = 0;
        }
    }

    int x{0}, y{0};
    int sz{0};
    while(cin>>x>>y){
        int tmpMax{0};
        sor[x][y] = 1;
        sor[y][x] = 1;
        tmpMax = max(x, y);
        if(sz < tmpMax) sz = tmpMax;
    }

    cout<<"adjacency matrix:"<<endl;
    for(int i = 0; i<=sz; i++){
        for(int j = 0; j<=sz; j++){
            cout<<sor[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"adjacency list:"<<endl;
    for(int i = 0; i<=sz; i++){
        cout<<i<<": ";
        for(int j = 0; j<=sz; j++){
            if(sor[i][j] == 1) cout<<j<<" -> ";
        }
        cout<<"NULL"<<endl;
    }

    return 0;
}

//////////////////////////////
/*
0 3
1 2
1 3
2 3
*/