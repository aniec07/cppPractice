#include <iostream>
#include <vector>
using namespace std;

bool isfactor(int num, int div);
bool issquare(int num);
bool evendigit(int num);
vector<int> digit(int num);


int main(){
    int temp=1000;    
    while(temp<=9999)
    {
        if(issquare(temp)&&evendigit(temp))
             cout << temp << endl;
        temp++;
   } 
}



bool issquare(int num){
    int temp=2;
    while(temp<=num/2)
    {
        if(isfactor(num,temp))
            if(num==temp*temp)
                return true;
        temp++;
    }
    return false;
}



bool evendigit(int num){
    vector<int> dignum=digit(num);
    while(dignum.size()>0)
    {
       
        if(isfactor(dignum.back(),2))
            dignum.pop_back();
        else
            return false;
    }
return true;
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
   


bool isfactor(int num, int div){

        if (num%div==0)
                return true;
        else
                return false;
}


