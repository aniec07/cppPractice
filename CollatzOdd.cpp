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
    cout << "Done twice" << endl;
    //printCollatz (c,62);
    //cout << "Done thrice" << endl;
}

void printCollatz(collatz &c, int temp){
    collatz::iterator it;
    do{
        if ( temp % 2 == 0 ){
            while( temp % 2 == 0 ){
                cout << temp << endl;
                temp /= 2;
            }
        }
        else{
            c[temp] = temp*3 + 1;
            cout << temp << endl;
            temp = temp*3 + 1;
        }
    }while( c.find(temp) == c.end() );
     
}   

