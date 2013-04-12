#include <iostream>
#include <vector>

using namespace std;


bool isoverlap (vector<int> a, vector<int> b) ;
int returnHighorLow (vector<int> a, char ch);
vector<int> makesets (int Min, int Max);

int main(){
    vector<int> set1,set2;
    set1=makesets(24,40);
    set2=makesets(7,18);
    if ( isoverlap (set1,set2) ) 
        cout << "Overlap exists" <<endl;
    else
        cout << "Overlap does not exist" << endl;
}

bool isoverlap (vector<int> a, vector<int> b){
    if ( returnHighorLow (a, 'l') < returnHighorLow (b,'h') ){
        vector<int>::iterator ita,itb;
        int matchindicator=0;
        for ( ita = a.begin() ; matchindicator != 1 && ita < a.end() ; ita++)
            for ( itb = b.begin () ; matchindicator != 1 && itb < b.end() ; itb++)
                if ( *ita == *itb){
                    matchindicator = 1;
                    return true;
                }
    return false;
    }
    else
        return false;
}

int returnHighorLow (vector<int> a, char ch){
    
    vector<int>::iterator it;
    int hl=a[0];
    if ( ch == 'h' )
        for ( it = a.begin() ; it < a.end() ;it++ )
            if ( *it > hl )
                hl = *it;
    else
        for ( it = a.begin() ; it < a.end() ;it++ )
            if ( *it < hl )
                hl = *it;
    
    return hl;
}


vector<int> makesets (int Min, int Max){
    vector<int> set;
    for ( int i = Min ; i <= Max ; i++)
        set.push_back(i);
    return set;
}
