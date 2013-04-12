#include <iostream>
#include <vector>
using namespace std;

int returnHighorLow(vector<int> MainList, char ch);
vector<int> findMissing(vector<int> Mainlist);

int main(){
    vector<int> MainList;
    int starter=0;
    cout<<"Enter the roll numbers (-1 to exit)"<<endl;
    while(starter!=-1){
        cin>>starter;
        if(starter!=-1)
            MainList.push_back(starter);
    }
    vector<int> Missing=findMissing(MainList);
    vector<int>::iterator it;
    cout<<"The Missing Roll Numbers are: "<<endl;
    for(it=Missing.begin();it<Missing.end();it++)
        cout<<*it<<" - ";
    cout<<endl;
    
}


int returnHighorLow(vector<int> MainList, char ch){
    vector<int>::iterator it;
    int hl=MainList[0];
    if(ch=='h'){
        for(it=MainList.begin();it<MainList.end();it++)
            if(*it>hl)
                hl=*it;
    }
    else{
        for(it=MainList.begin();it<MainList.end();it++)
            if(*it<hl)
                hl=*it;
    }
    
    return hl;
}

vector<int> findMissing(vector<int> MainList){
    int low=returnHighorLow(MainList,'l');
    int high=returnHighorLow(MainList,'h');
    vector<int> MissingList;
    int *arr;
    arr=new int[high-low];

    for(int i=0;i<high-low;i++)
        arr[i]=0;
    vector<int>::iterator it;
    for(it=MainList.begin();it<MainList.end();it++)
        arr[*it-low]=1;
    for(int i=0;i<high-low;i++)
        if(arr[i]==0)
            MissingList.push_back(i+low);

    return MissingList;
}
