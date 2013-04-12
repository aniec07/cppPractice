#include <iostream>
#include <string>

using namespace std;

string cycle(string word);


int main(){
    string str1="Anirban";
    string str2="rbanAni";
    int i=0;
    if ( str1.length()==str2.length() ){
        while ( i<str1.length() ){
            str2=cycle(str2);
            if ( str1.compare(str2)==0 )
                cout << "Cyclic permutation exists for: " << str2 << endl;
            i++;
        }
    }
    else
        cout << "String lengths are unequal " << endl;    
}


string cycle(string word){
    string newstr;
    for ( int i=0; i<word.length(); i++)
        newstr.push_back(word[(i+1)%word.length()]);
    return newstr;
}
