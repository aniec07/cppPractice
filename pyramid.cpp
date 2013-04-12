#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string makeline(int length);

int main(int argc, char *argv[]){
    int l=(int)(argv[1][0]-48);
    int scrnwidth=(int)(argv[2][0]-48)*100+(int)(argv[2][1]-48)*10+(int)(argv[2][1]);
    for ( int i=1;i<=l;i++){
        streamsize width=(streamsize)(makeline(2*i-1).length()+scrnwidth)/2;
        cout<<setw(width)<<makeline(2*i-1)<<endl;
    }
}

string makeline(int length){
    string line;
    for ( int i=0;i<length;i++ ){
        line.push_back('*');
    }
    return line;
}
    

