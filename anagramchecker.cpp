#include <iostream>
#include <string>
using namespace std;

bool isanagram(string str1,string str2);

int main(){

    string str1, str2;
    str1="Arma";
    str2="mary";
    if ( isanagram(str1,str2) )
        cout << " Strings are an anagarm" << endl;
    else
        cout<< " Strings are not anagram" <<endl;
}



bool isanagram(string str1,string str2){

    int char_marker[26];
    for ( int i=0;i<26;i++ )
        char_marker[i]=0;
    if ( str1.length()==str2.length() )
    {
        string::iterator it1;
        string::iterator it2;
        it2=str2.begin();
        for ( it1=str1.begin() ; it1 < str1.end(); it1++, it2++ )
        {
            if( (int)(*it1)<90 )
                char_marker[(int)(*it1)-65]++;
            else
                char_marker[(int)(*it1)-97]++;
            if( (int)(*it2)<90 )
                char_marker[(int)(*it2)-65]--;   
            else
                char_marker[(int)(*it2)-97]--;
        }
        for ( int i=0;i<26;i++ )
            if ( char_marker[i]!=0 )
                return false;

        return true;
    }
    else
         return false;
}
  


