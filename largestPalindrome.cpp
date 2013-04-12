#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    int i = 0;
    int length = argv[0].length();
    for ( i = 0; i < length/2 ; i++ ){
        if ( i < (length/2) - 1 ){
            argv[0][length - i] = argv[0][i];
        }
        else{
            argv[0][i] = 
        }
    }

}

