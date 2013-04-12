#include <iostream>

using namespace std;

int add(int first, int second)
{
        return first + second;
}

int subtract(int first, int second)
{
        return first - second;
}

int operation(int first, int second, int (*func)(int, int))
{
        return (*func)(first, second);
}

int Value(int *p) {
        return ++(*p);
}

int main()
{
        int m = 5;
        cout << Value(&m) << endl;
        cout << m << endl;
        int  a, b;
        int  (*plus)(int, int) = add;
        a = operation(7, 5, add);
        b = operation(20, a, subtract);
        cout << "a = " << a << " and b = " << b << endl;
        return 0;
}
