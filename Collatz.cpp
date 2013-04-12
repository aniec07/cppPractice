#include <iostream>
#include <map>

using namespace std;

typedef map<int,int> collatz;

void printCollatz (collatz &, int );

int main(){
    collatz c;
    int start = 15;
    printCollatz (c,start);
    cout << "Done once" << endl;
    printCollatz (c,7);
}

void printCollatz(collatz &c, int start){
    collatz::iterator it;
    int temp = start;
    cout << temp << endl;
    if ( temp % 2 == 0 ){
        c[temp] = temp/2;
        temp /= 2;
        cout << temp << endl;
    }
    else{
        c[temp] = temp*3 + 1;
        temp = temp*3 + 1;
        cout << temp << endl;
    }
    while ( c.find(temp) == c.end() ){
        if ( temp % 2 == 0 ){
            c[temp] = temp/2;
            temp /= 2;
            cout << temp << endl;
        }
        else{
            c[temp] = temp*3 + 1;
            temp = temp*3 + 1;
            cout << temp << endl;
        }
    } 
}   

