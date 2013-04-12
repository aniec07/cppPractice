#include <iostream>

using namespace std;

int bigger(int a, int b);
int best(int a, int b, int c);

int main(){
    int a,b,c;
    a=8;
    b=5;
    c=1;
    cout << "The largest of the three integers is: " << best(a,b,c) << endl;
}

int bigger(int a, int b){
    return ((a>b)*a+(b>a)*b);
}

int best(int a, int b, int c){
    return (bigger(bigger(a,b),c));
}
