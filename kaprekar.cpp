#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int power(int num,int index);
vector<int> sortnum(vector<int> num);
vector<int> num_to_digit(int num);
int kaprekar(int begin);
int makenumber(vector<int> dig, char ch);



int main(){
    int flag=1,index;
    int begin=234781;
    int diff=kaprekar(begin);
    vector<int> cycle;
    while ( flag ){   
        index=0;
        diff=kaprekar(diff);
        cycle.push_back(diff);
        while ( (index<cycle.size()-1)&&flag==1 ){
            if(diff==cycle[index])
            flag=0;
            index++;
        }
    }
    cout<<"The Cycle is: "<<endl;
    while ( index<cycle.size() ) {    
        cout<<cycle[index]<<endl;
        index++;
    }    
    return 0;
}





int kaprekar(int begin){
    int more=0,less=0,diff=0;
    more=makenumber(sortnum(num_to_digit(begin)),'a');
    less=makenumber(sortnum(num_to_digit(begin)),'d');
    diff=more-less;
    cout<<more<<" "<<less<<" "<<diff<<endl;
    return diff;
}


int makenumber(vector<int> numarr, char ch)
{
    int sum=0;
    if(ch=='a')
        for ( int i=0;i<numarr.size();i++ )
            sum+=numarr[i]*power(10,i);
    else
        for ( int i=numarr.size()-1;i>=0;i--)
            sum+=numarr[i]*power(10,numarr.size()-i-1);
return sum;
}
    



vector<int> sortnum(vector<int> num){
    sort(num.begin(),num.end());
    return num;
}

    
int power(int num,int index){
    int prod=1;
    while(index>=1){
        prod*=num;
        index--;
    }
    return prod;
}

vector<int> num_to_digit(int num){
    vector<int> dig;
    while(num>0){
        dig.push_back(num%10);
        num/=10;
    }
return dig;
}
