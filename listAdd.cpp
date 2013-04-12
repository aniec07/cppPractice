#include <iostream>
#include <list>

using namespace std;

void printList(std::list<int>);
list<int> addList(std::list<int>,std::list<int>);


int main(){

        std::list<int> first;
        std::list<int> second;
        int temp = 0;
        cout << "Enter first number digit by digit, -1 to exit: ";
        cin >> temp;
        while( temp != -1 ){
                first.push_back(temp);
                cout << "Enter next digit, -1 to exit: ";
                cin >> temp;
        }


        temp = 0;
        cout << "Enter second number digit by digit, -1 to exit: ";
        cin >> temp;
        while( temp != -1 ){
                second.push_back(temp);
                cout << "Enter next digit, -1 to exit: ";
                cin >> temp;
        }

        printList(first);
        printList(second);
        
        std::list<int> sumList = addList(first,second);

        printList(sumList);

        return 0;
}

void printList(list<int> listToPrint){
        for (std::list<int>::iterator it = listToPrint.begin(); it != listToPrint.end() ; it++ ){
                cout << *it ;
        }

        cout << endl;

}


std::list<int> addList(list<int> first, list<int> second){
        
        std::list<int>::iterator it1,it2;
        std::list<int> newList;
        first.push_front(0);
        second.push_front(0);
        it1 = first.end();
        it2 = second.end();
        int carry = 0;
        bool oneOfTheListFinished = false;
        it1--;
        it2--;
        do{

            if ( it1 == first.begin() && it2 != first.begin() ) { //case where first list is smaller and second list is longer
                    if ( !oneOfTheListFinished ){
                            newList.push_front((*it1 + *it2 + carry)%10);
                            if (( *it1 + *it2 + carry )/10 >= 1 ){
                                    carry = 1;
                            }
                            else{
                                    carry = 0;
                            }
                    oneOfTheListFinished = true;
                        it2--;
                    }
                    else{
                        newList.push_front(*it2);
                        carry = 0;
                        it2--;
                    }
            }
            else if( it2 == second.begin() && it1 != first.begin() ){ //case where the second list is smaller and the first is longer
                    if ( !oneOfTheListFinished ){
                            newList.push_front((*it1 + *it2 + carry)%10);
                            if (( *it1 + *it2 + carry )/10 >= 1 ){
                                    carry = 1;
                            }
                            else{
                                    carry = 0;
                            }
                            oneOfTheListFinished = true;
                            it1--;
                    }
                    else{
                            newList.push_front(*it1);
                            carry = 0;
                            it1--;
                    }

            }
            else{ //case where both are same
                    newList.push_front((*it1 + *it2 + carry)%10);
                            if (( *it1 + *it2 + carry )/10 >= 1 ){
                                    carry = 1;
                            }
                            else{
                                    carry = 0;
                            }
            it1--;
            it2--;
            }
        }while ( it1  != first.begin() || it2 != second.begin() );
        if ( carry )
                newList.push_front(carry);
                                          
        return newList;
}
























