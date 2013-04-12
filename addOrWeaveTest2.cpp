#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<char> weave(string str1,string str2);
string addOrWeave(string str1, string str2);

int main(){
    string str1,str2;
    str1 = "hello";
    str2 = "world";
    cout << addOrWeave(str1,str2) << endl;
    str1 = "hello";
    str2 = "dmr";
    cout << addOrWeave(str1,str2) << endl;
    str1 = "good";
    str2 = "world";
    cout << addOrWeave(str1,str2) << endl;
}

string addOrWeave(string str1, string str2){
    if ( str1.length() < str2.length() ){
        string finalstr;
        finalstr = str1.append(str2.append(str1));
        return finalstr;
    }
    else if ( str1.length() > str2.length() ){
        string finalstr;
        finalstr = str2.append(str1.append(str2));
        return finalstr;
        
    }
    else{
        vector<char> str3=weave(str1,str2);
        string finalstr;
        for ( int i=0; i<str3.size() ; i++)
            finalstr.push_back(str3[i]);
        return finalstr;
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
    
