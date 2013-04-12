#include <iostream>
#include <vector>

using namespace std;

vector<int> returnfactors(int num);
bool isfactor(int num, int div);
int sumfact(vector<int> fact);

int main() {
    int lim=10000;
    while ( lim>0 ){
        if ( lim == sumfact (returnfactors(lim) ) )
            cout << lim << endl;
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
            
            
