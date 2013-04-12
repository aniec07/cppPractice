#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

bool oneLD(string s1, string s2);

int main(int argc, char *argv[]){
    std::string word1 = argv[1];
    std::string word2 = argv[2];
    if ( oneLD(word1,word2) )
        cout << "TRUE" << endl;
    else
        cout << "FALSE" << endl;
}

bool oneLD(string s1, string s2){

    int l1 = s1.length();
    int l2 = s2.length();
    if ( abs(l1 - l2) <= 1 ){
        vector<char> ch1,ch2;
        for ( int i = 0; i < s1.length() ; i++ )
            ch1.push_back(s1[i]);
        for ( int i = 0; i < s2.length() ; i++ )
            ch2.push_back(s2[i]);
        
        int matchcount = 0;
        vector<char>::iterator it1,it2;
        for ( it1 = ch1.begin() ; it1 != ch1.end() ; it1++ )
            for ( it2 = ch2.begin() ; it2 != ch2.end() ; it2++ )
                if ( *it1 == *it2 )
                    matchcount++ ;
        if ( abs (l1 - matchcount) <= 1 && abs (l2 - matchcount) <= 1 )
            return true;
        else
            return false;
    }
    else
        return false;
}
        
                
        
        
