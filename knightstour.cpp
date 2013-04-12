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
bool isvisited(vector<int> masterlist, int pos);
int NextMove(vector<int> masterlist, map< int,vector<coordinate> > FinalMap, vector<coordinate> possiblemoves);
bool notcomplete(vector<int> masterlist);
int currentsize(vector<int> masterlist, vector<coordinate> possiblemoves);
vector<int> knightsPath(coordinate c);


int main(int argc,char *argv[]){
    coordinate c;
    c.x = argv[1][0];
    c.y = (int)(argv[1][1]-'0');
    map< int,vector<coordinate> > FinalMap = returnAllPossibleMoves();
    vector<int> masterlist = knightsPath(c);
    vector<int>::iterator ml = masterlist.begin();
    for ( int i = 0; i< 8 ; i++){
        for ( int j = 0; j < 8 ; j++ ){
            if ( *ml < 10 )
                cout << " 0" << *ml << " ";
            else
                cout << " " << *ml << " ";
        ml++;    
        }
    cout << endl << endl;
    }
}


vector<int> knightsPath(coordinate c){
    vector<int> masterlist;
    int movecount = 1;
    int nm = ChesstoPosNumber(c);
    map< int,vector<coordinate> > FinalMap = returnAllPossibleMoves();
    for ( int i = 0; i < 64 ; i++)
        masterlist.push_back(0);
    masterlist[nm - 1] = 1;
    while ( notcomplete(masterlist) ){
        nm = NextMove(masterlist,FinalMap,FinalMap.find(nm)->second);
        movecount++;
        masterlist[nm - 1] = movecount;
    }
    return masterlist;
}
    
        
int NextMove(vector<int> masterlist, map< int,vector<coordinate> > FinalMap, vector<coordinate> possiblemoves){
    vector<coordinate>::iterator it;
    coordinate NMove;
    int minsize = 100;
    for ( it = possiblemoves.begin() ; it < possiblemoves.end(); it++)
        if ( !isvisited(masterlist, ChesstoPosNumber(*it)) )
            if ( currentsize(masterlist, FinalMap.find(ChesstoPosNumber(*it))->second) < minsize ){
                minsize = currentsize(masterlist,FinalMap.find(ChesstoPosNumber(*it))->second);
                NMove = *it;
        }
    return ChesstoPosNumber(NMove);
}

int currentsize(vector<int> masterlist, vector<coordinate> possiblemoves){
    int size = 0;
    vector<coordinate>::iterator pm;
    for ( pm = possiblemoves.begin(); pm < possiblemoves.end() ; pm++)
        if(!isvisited(masterlist,ChesstoPosNumber(*pm)))
            size++;
    return size;
}

bool notcomplete(vector<int> masterlist){
    int count = 0;
    vector<int>::iterator it;
    for ( it = masterlist.begin() ; it < masterlist.end() ; it++)
        if ( *it > 0)
            count++;
    if ( count < 64 )
        return true;
    else
        return false;
}


bool isvisited(vector<int> masterlist, int pos){
    if ( masterlist[pos-1] > 0)
        return true;
    else
        return false;
}
        

int ChesstoPosNumber(coordinate c){
    int PosNumber=0;
    PosNumber = (c.y-1)*8+(int)(c.x-'a')+1;
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
