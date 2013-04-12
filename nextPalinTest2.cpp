#include <iostream>
#include <string>
#include <vector>

using namespace std;

//number of digits will always be fixed because 9999... is a palindrome number
string reverse_Word(string word);
string increasenumber(string number);
string nextPalin(string number);

int main(int argc, char *argv[]){
    std::string number = argv[1];
    cout << "Original Number: " << number << endl;
    cout << "Next Palindrome: " << nextPalin(number) << endl;
}

string nextPalin(string number){
    number = increasenumber(number);
    while(number.compare(reverse_Word(number)) != 0)
        number = increasenumber(number);
    return number;
}
    
    
string increasenumber(string number){
    int it = number.length() - 1 ;
    int flag = 1;
    while (flag){
        number[it]++;
        if ( number[it] - '9' > 0 ){
            number[it] = '0';
            it--;
        }
        else
            flag = 0;
    }
    return number;
}

string reverse_Word(string word){
    string revWord;
    string::iterator it;
    for ( it=word.end()-1; it>=word.begin(); it--)
        revWord.push_back(*it);
    return revWord;
}
