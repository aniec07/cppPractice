# include <iostream>
using namespace std;
int checklarge(int num);
bool isfactor(int num, int div);
bool ispowertwo(int num);

int main(){
        int num;
        //cout << "Enter the number" <<endl;
        //cin >> num;
        num=8;
        if(ispowertwo(num))
            cout << "Power of Two" << endl;
        else
            cout << "Not power of Two" << endl;
        return 0;
}

bool ispowertwo(int num){
        
        if (num==1)
                return true;
        if (num==0||num%2!=0)
                return false;
        ispowertwo(num/2);
}

bool isfactor(int num, int div){

        if (num%div==0)
                return true;
        else
                return false;

}



int checklarge(int num){

        int copy=num-1;
        while(copy!=0)
        {
                if(isfactor(num,copy))
                        return copy;
                else
                        copy--;
        }
}


