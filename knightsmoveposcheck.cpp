#include <iostream>
#include <vector>

using namespace std;

struct coordinate{
    char x;
    int y;
};

bool isvalid (coordinate c);
vector<coordinate> returnAllNextMove(coordinate pos);
vector<coordinate> returnValidMoves(coordinate pos);

int main(){
    coordinate c;
    c.x = 'b';
    c.y = 4;
    vector<coordinate> ValidMoves = returnValidMoves(c);
    vector<coordinate>::iterator it;
    for ( it = ValidMoves.begin(); it < ValidMoves.end() ; it++){
        coordinate tempc = *it;
        cout << "(" << tempc.x << "," << tempc.y << ")" << endl;
    }
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
