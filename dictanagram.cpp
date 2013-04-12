#include <iostream>
#include <string>

using namespace std;

string sorter(string str);


int compare(const void *a_ , const void *b_){
    const char *a=(const char *)a_;
    const char *b=(const char *)b_;
    return *a<*b?-1:*a>*b;
}




int main(){

string str="anirban";
cout << str << endl;
qsort(str, strlen(str),1, compare);
cout << str << endl;
}
