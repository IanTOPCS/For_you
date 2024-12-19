# include <bits/stdc++.h>
using namespace std;

# define room 10000

int main(void){
    int sor[room]{0};
    int index{0};
    string input{""}; getline(cin, input);
    for(int i = 0; i<input.size(); i++){
        if(input[i] == ' ') continue;
        string tmp{""};
        while((i < input.size()) && (input[i] != ' ')){
            tmp += input[i];
            i++;
        }
        sor[index] = stoi(tmp);
        index++;
    }
    int cycle{0};cin>>cycle;
    if((cycle < 0) || (cycle >= index)) cout<<0<<endl;
    else cout<<(index-cycle)<<endl;
    return 0;
}

/*
3 2 0 -4
1
*/