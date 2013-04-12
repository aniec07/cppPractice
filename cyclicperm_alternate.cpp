#include <iostream>
#include <string>

using namespace std;

bool iscycle(string str1,string str2);


int main(){
    string str1="Anirban";
    string str2="rbanAni";
    if(iscycle(str1,str2))
        cout <<  "Cyclic permutation exists" << endl;
    else
        cout << "No cyclic permutation" << endl;    
}


bool iscycle(string str1,string str2){
    str1.append(str1);
    for ( int i=0; i<str1.length(); i++)
        if(str2.compare(str1.substr(i,i+str2.length())))
            return true;
    return false;
}
