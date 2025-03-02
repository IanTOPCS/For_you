#include <iostream>
using namespace std;
#define MAX static_cast<int>(1e7)
int input[MAX+5] = {}, tmp[MAX+5] = {};

void divide (int, int);

void combine (int, int, int);

int main(void)
{
    int test_data = 0;
    int inputData{0};
    while(cin>>inputData)
    {
        input[test_data++] = inputData;
    }

    divide(0, (test_data-1));//分治

    for(int i = 0; i<test_data; i++)
    {
        cout<<input[i]<<" ";
    }
    cout<<"\n";
    return 0;
}

void divide (int left, int right)
{
    if(left == right)//分到最末端，只剩下自己
    {
        return;
    }
    
    int middle = (left + right)/2;//分
    
    //治
    divide (left, middle), divide (middle+1, right);
    combine (left, middle, right);//合
}

void combine (int left, int middle, int right)
{
    int ptr_left = left, ptr_right = (middle + 1);//左指針，左半第一個，又指針，右半第一個
    
    int tmp_index = left;//排序需要的

    while(ptr_left <= middle && ptr_right <= right)//當兩個指針都沒有超過各自範圍
    {
        if(input[ptr_left] < input[ptr_right])//如果左半小於右半，根據由小到大，左邊放入暫存解答
        {
            tmp[tmp_index] = input[ptr_left];
            tmp_index++, ptr_left++;
        }
        else
        {
            tmp[tmp_index] = input[ptr_right];
            tmp_index++, ptr_right++;
        }
    }

    while(ptr_left <= middle)//當右指針已經超出範圍
    {
        tmp[tmp_index] = input[ptr_left];
        tmp_index++, ptr_left++;
    }

    while(ptr_right <= right)//當只剩下右指針仍在範圍，按順序插入，因為已經排好了
    {
        tmp[tmp_index] = input[ptr_right];
        tmp_index++, ptr_right++;
    }

    for(int i = left; i <= right; i++)//將暫存答案慢慢填入真正解
    {
        input[i] = tmp[i];
    }
}