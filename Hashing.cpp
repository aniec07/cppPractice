#include <iostream>
#include <string>

using namespace std;

int returnSumAscii (string str);
int returnModulo ( int num, int div);

int main(){
    string Names[] = {  "Maaz", "Siddharth", "Sakshi", "Joel", "Sandeep", "Kunal",
                        "Prince", "Sharath", "Praveen", "Vidyullatha", "Prafull",
		                "Rini", "Nethra", "Ankit", "Kashish", "Shiva",
		                "Ashwani", "Akshara", "Akshay", "Anirban", "Chandranshu",
		                "Omar", "Vivek", "Komal", "Harsh", "Arpit", "Aman", "Gaurav",
		                "Bharat", "Tulasi", "Suthakar", "Abhinav"};
    int div = 100;
    int *arr;
    int collision = 0;
    arr = new int[div];
    for ( int i = 0 ; i < div ; i++ )
        arr[i] = 0;
    for ( int i = 0 ; i < 32; i++ )
        arr [ returnModulo ( returnSumAscii(Names [i]) , div) ] ++;
    for ( int i = 0 ; i < div ; i++ ){
            cout << arr[i] << " , ";
            if ( arr [i] > 1 ) 
            collision = collision + (arr[i] - 1);
        }
        cout << endl << "The number of Collisions is" << collision << endl;
    
}

int returnModulo (int num, int div){
    return num%div;
}

int returnSumAscii (string str){
    string::iterator it;
    int sum=0;
    for ( it = str.begin() ; it != str.end() ; it++){
        sum += *it;
    }
    return sum;
}
