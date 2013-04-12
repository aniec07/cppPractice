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
    printCollatz (c,62);
    cout << "Done thrice" << endl;
}

void printCollatz(collatz &c, int start){
    collatz::iterator it;
    int temp = start;
    cout << temp << endl;
    do{
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
    }while( c.find(temp) == c.end() );
     
}   

