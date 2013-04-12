#include <iostream>

using namespace std;


struct triangle{
    double s1;
    double s2;
    double s3;
};

string returnTypeofTriangle ( triangle a );


int main(){
    triangle t;
    t.s1 = 4;
    t.s2 = 7;
    t.s3 = 4;
    cout << "Triangle type is: " << returnTypeofTriangle (t) << endl;
}


string returnTypeofTriangle ( triangle a ){
    if ( a.s1 == a.s2 && a.s1 == a.s3 )
        return "Equilateral";
    else if ( a.s1 == a.s2 || a.s1 == a.s3 || a.s2 == a.s3 )
        return "Isoceles";
    else 
        return "Scalene";
}
    
