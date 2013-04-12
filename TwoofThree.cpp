#include <iostream>
using namespace std;
bool compare(bool a,bool b);

int main(){
    bool a=false;
    bool b=false;
    bool c=true;
    cout << (compare(a,b)|compare(a,c)|compare(b,c)) << endl;
    return 0;
}

bool compare(bool a,bool b){
    return a&b;
}
