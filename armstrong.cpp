#include <iostream>
#include <vector>
using namespace std;

vector<int> digit(int num);
bool isarmstrong(int num);
int power(int num,int index);

int main(){
    int temp=100;    
    while(temp<=999)
    {
        if(isarmstrong(temp))
             cout << temp << endl;
        temp++;
   } 
}

int power(int num,int index){
    int prod=1;
    while(index>=1)
    {
        prod*=num;
        index--;
    }
    return prod;
}

bool isarmstrong(int num){
    vector<int> dig=digit(num);
    int rank=dig.size();
    int sum=0;
    while(dig.size()>0)
    {
        sum+=power(dig.back(),rank);
        dig.pop_back();
    }
    if(sum==num)
        return true;
    else
        return false;
}
    





vector<int> digit(int num){
    vector<int> dig;
    while(num>0)
    {
        dig.push_back(num%10);
        num/=10;
    }
return dig;
}
   


