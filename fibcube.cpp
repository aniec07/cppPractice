#include <iostream>

using namespace std;

int checklarge(int num);
bool isfactor(int num, int div);
bool iscube(int num);
void fib(int num);

int main(){
        int num;
        cout << "Fibonacci Numbers which are perfect cube are" <<endl;
        fib(1000000);
}

void fib(int limit){
        int a,b,c;
        a=0;
        b=1;
        c=a+b;
        while(c<limit)
        {
            c=a+b;
            a=b;
            b=c;
            if(iscube(c))
                cout << c << endl;
        }
}

bool iscube(int num){
        int temp=1;
        while(temp<=num/3)
        {
           if(num==temp*temp*temp)
                return true;
           temp++;
        }
        return false;
}

