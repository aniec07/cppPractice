#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct position{
    char x;
    int y;
};

typedef position coordinate;

bool isvalid (coordinate c);
vector<coordinate> returnAllNextMove(coordinate pos);
vector<coordinate> returnValidMoves(coordinate pos);
map< int,vector<coordinate> > returnAllPossibleMoves();
int ChesstoPosNumber(coordinate c);

int main(){
    coordinate c;
    c.x = 'b';
    c.y = 4;
    vector<coordinate> ValidMoves = returnValidMoves(c);
    vector<coordinate>::iterator it;
    map< int,vector<coordinate> > FinalMap = returnAllPossibleMoves();    
    for ( it = ValidMoves.begin(); it < ValidMoves.end() ; it++){
        coordinate tempc = *it;
        cout << "(" << tempc.x << "," << tempc.y << ")" << endl;
    }
    vector<coordinate> tempvect;
    for ( int it = 1; it <= 64 ; it++){
        tempvect = FinalMap.find(it)->second;
        cout << "Position for " << it << " is: ";
        vector<coordinate>::iterator itvect;    
        for ( itvect = tempvect.begin() ; itvect < tempvect.end() ; itvect++)
            cout << "(" << (*itvect).x << "," << (*itvect).y << ")" <<  " -- ";
        cout << endl;
    }
}

int ChesstoPosNumber(coordinate c){
    int PosNumber=0;
    PosNumber = (c.y-1)*8+(int)(c.x-96);
    return PosNumber;
}

map< int,vector<coordinate> > returnAllPossibleMoves(){
    coordinate tempc;
    int posNum;
    map< int,vector<coordinate> > FinalMap;
    for ( char x = 'a' ; x <= 'h' ; x++)
        for ( int y = 1 ; y<= 8 ; y++ ){
            tempc.x = x;
            tempc.y = y;
            posNum = ChesstoPosNumber(tempc);
            vector<coordinate> vt = returnValidMoves(tempc);
            FinalMap.insert( pair< int,vector<coordinate> >(posNum,vt) );
        }
    return FinalMap;
}

bool isvalid ( coordinate c){
    if(c.x >= 'a' && c.x <= 'h' && c.y >= 1 && c.y <= 8 )
        return true;
    else return false;
}

vector<coordinate> returnAllNextMove(coordinate pos){
    coordinate c;
    vector<coordinate> AllNextMove;
    c.x = pos.x - 2;
    c.y = pos.y - 1;
    AllNextMove.push_back(c);
    
    c.x = pos.x - 2;
    c.y = pos.y + 1;
    AllNextMove.push_back(c);
            
    c.x = pos.x + 2;
    c.y = pos.y - 1;
    AllNextMove.push_back(c);
    
    c.x = pos.x + 2;
    c.y = pos.y + 1;
    AllNextMove.push_back(c);
    
    c.x = pos.x - 1;
    c.y = pos.y - 2;
    AllNextMove.push_back(c);
    
    c.x = pos.x + 1;
    c.y = pos.y - 2;
    AllNextMove.push_back(c);
    
    c.x = pos.x - 1;
    c.y = pos.y + 2;
    AllNextMove.push_back(c);
    
    c.x = pos.x + 1;
    c.y = pos.y + 2;
    AllNextMove.push_back(c);
    
return AllNextMove;
} 


vector<coordinate> returnValidMoves(coordinate pos){
    vector<coordinate> AllNextMove = returnAllNextMove(pos);
    vector<coordinate> ValidMoves;
    vector<coordinate>::iterator it;
    for ( it = AllNextMove.begin(); it < AllNextMove.end() ; it++)
        if ( isvalid (*it))
            ValidMoves.push_back (*it);
return ValidMoves;
}
