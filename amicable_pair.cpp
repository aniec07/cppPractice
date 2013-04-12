#include <iostream>
#include <vector>

using namespace std;

vector<int> returnfactors(int num);
bool isfactor(int num, int div);
int sumfact(vector<int> fact);

int main() {
    int lim = 10000;
    while ( lim>0 ){
        int num1 = sumfact(returnfactors(lim));
        int num2 = sumfact(returnfactors(num1));
            if ( num2 == lim && num2 > num1 )
                cout << num1 << " " << num2 <<endl;
        lim--;
    }    
}

vector<int> returnfactors (int num){
    vector<int> fact;
    int copy = num-1;
    while ( copy>0 ){
        if ( isfactor(num,copy) )
                fact.push_back(copy);
        copy--;
    }
    return fact;
}

int sumfact ( vector<int> fact ){
    int sum=0;
    vector<int>::iterator it;
    for ( it = fact.begin() ; it<fact.end() ; it++)
        sum += *it;
    return sum;
}

bool isfactor ( int num, int div ){
    if ( num%div==0 )
        return true;
    else
        return false;
}
            
            
