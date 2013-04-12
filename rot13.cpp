#include <iostream>
#include <string>

using namespace std;

int findCharPosition (char ch);
string encodeString(string str, char ch, int rotateby);

int main(){
    string str = "hello";
    cout << encodeString(str, 'e', 13) << endl;
}


int findCharPosition( char ch){
    string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
    string::iterator it = alpha.begin();
    int count=0,flag=1;
    while ( flag ){
        if ( *it == ch )
            return (count%26);
        it++;
        count++ ;
    }
}

string encodeString(string str, char ch, int rotateby){
    string::iterator it;
    string newstr;
    string alphalow = "abcdefghijklmnopqrstuvwxyz";
    string alphahigh = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alphalow = alphalow.append (alphalow.append (alphalow));
    alphahigh = alphahigh.append (alphahigh.append (alphahigh));
    if ( ch == 'e' ){
        for ( it = str.begin() ; it < str.end() ; it ++)
            newstr.push_back ( alphalow[findCharPosition(*it)+rotateby]);
    }
    else{
        for ( it = str.begin() ; it < str.end() ; it ++)
            newstr.push_back ( alphalow[findCharPosition(*it)+26-rotateby]);
    }
    return newstr;
}

     
        
