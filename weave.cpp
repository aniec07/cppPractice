#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<char> weave(string str1,string str2);

int main(){
    string str1,str2;
    str1="Anirban";
    str2="Pramanick";
    vector<char> str3=weave(str1,str2);
    for ( int i=0; i<str3.size() ; i++)
    {
        cout << str3[i];
    }
}

vector<char> weave(string str1,string str2){

    string::iterator it1;
    string::iterator it2;
    it1=str1.begin();
    it2=str2.begin();
    vector<char> newstr;
    int length=0;
    while ( it1<str1.end()||it2<str2.end() )
    {
        if ( it1<str1.end() )
        {
            newstr.push_back(*it1);
            it1++;
        }
        if ( it2<str2.end() )
        {
            newstr.push_back(*it2);
            it2++;
        }
    }
return newstr;
}        
    
