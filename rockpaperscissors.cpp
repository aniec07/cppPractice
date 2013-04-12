#include <iostream>
#include <vector>
#include <string>

using namespace std;

string winner (string ch1, string ch2);
int returnPosition (vector<string> rps, string ch);

int main(){
    string str1 = "Scissor";
    string str2 = "Scissor";
    cout << winner(str1,str2) << endl;
}

int returnPosition ( vector<string> rps, string ch, int from){
    int i;
    for ( i = from-1; i < rps.size() ; i++)
        if ( ch.compare(rps[i]) == 0)
            return (i+1);
return i;
}

string winner (string ch1, string ch2){
    vector<string> rps,circrps;
    rps.push_back("Rock");
    rps.push_back("Paper");
    rps.push_back("Scissor");
    vector<string>::iterator it;
    for ( it = rps.begin(); it < rps.end(); it++)
        circrps.push_back ( *it );
    for ( it = rps.begin(); it < rps.end(); it++)
        circrps.push_back ( *it );
    int pos1 = returnPosition ( circrps, ch1, 1);
    int pos2 = returnPosition ( circrps, ch2, pos1) ;
    if ( ( pos2 - pos1)%3 == 0)
        return "Draw";
    else if ( ( pos2 - pos1)%3 == 1 )
        return ch2;
    else return ch1;
}
    
    
    

