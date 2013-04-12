#include <iostream>
#include <list>

using namespace std;

typedef struct{
    int row;
    int col;
}coord;

typedef struct{
    int row;
    int col;
    bool isAlive;
    int AliveCount;
}cell;

list<coord> returnNeighbourCoords (coord currentCell) ;
int returnAliveCount (list<cell> sparse, list<coord> neighbours) ;
bool isFound ( list<cell> sparse, coord c );
cell returnCell ( list<cell> sparse, coord c );
list<cell> updateConway (list<cell> sparse);
void PrintMat(list<cell>);
coord returnMeanCoord(list<cell> sparse);
list<cell> displaceCoord(list<cell> sparse, coord disp);

int main(){
    list<cell> sparse;
    cell c;
    c.row = 5;
    c.col = 4;
    c.isAlive = true;
    sparse.push_back(c);
    c.row = 5;
    c.col = 5;
    c.isAlive = true;
    sparse.push_back(c);
    c.row = 5;
    c.col = 6;
    c.isAlive = true;
    sparse.push_back(c);
    c.row = 3;
    c.col = 5;
    c.isAlive = true;
    sparse.push_back(c);
    c.row = 4;
    c.col = 6;
    c.isAlive = true;
    sparse.push_back(c);
    
    sparse = updateConway (sparse );
    /*list<cell>::iterator it;
    for ( it = sparse.begin() ; it != sparse.end() ; it++ ){
        cout << "(" << (*it).row << "," << (*it).col << ")" << endl;
    }
    
    sparse = updateConway (sparse );
    //list<cell>::iterator it;
    for ( it = sparse.begin() ; it != sparse.end() ; it++ ){
        cout << "(" << (*it).row << "," << (*it).col << ")" << endl;
    }*/
    
    PrintMat(sparse);
    int count = 0;
    coord prevcoord = returnMeanCoord(sparse);
    coord newcoord,difcoord;
    while ( count < 500 ){
        sparse = updateConway(sparse);
        newcoord = returnMeanCoord(sparse);
        difcoord.row = newcoord.row - prevcoord.row;
        difcoord.col = newcoord.col - prevcoord.col;
        sparse = displaceCoord(sparse,difcoord);
        cout << string(50, '\n') << endl;
        PrintMat(sparse);
        prevcoord = newcoord;
        sleep(1);
        count++;
    }
}
        

list<cell> displaceCoord(list<cell> sparse, coord disp){
    list<cell>::iterator it;
    for ( it = sparse.begin(); it != sparse.end() ; it++ ){
        (*it).row = (*it).row - disp.row;
        (*it).col = (*it).col - disp.col;
    }
    return sparse;
}
        

coord returnMeanCoord(list<cell> sparse){
    list<cell>::iterator it;
    coord meanc;
    meanc.row = 0;
    meanc.col = 0;
    int count = 0;
    for ( it = sparse.begin() ; it != sparse.end() ; it++ ){
        meanc.row += (*it).row;
        meanc.col += (*it).col;
        count++;
    }
    meanc.row/=count;
    meanc.col/=count;
}



void PrintMat( list<cell> sparse ){
    int mat[12][12];
    for ( int i = 0; i<12 ; i++ )
        for ( int j = 0; j<12 ; j++ )
            mat[i][j] = 0;
    list<cell>::iterator it;
    for ( it = sparse.begin(); it != sparse.end() ; it++ )
        mat[(*it).row][(*it).col] = 1;
    for ( int i = 0; i<12 ; i++ ){
        for ( int j = 0; j<12 ; j++ ){
            if ( mat[i][j] == 1 )
                cout << "&" ;
            else
                cout << " ";
        }
        cout << endl;
    }
}
    
    

list<cell> updateConway (list<cell> sparse){
    list<cell> newsparse;
    list<cell>::iterator sp;
    for ( sp = sparse.begin() ; sp != sparse.end() ; sp++ ){
        coord current;
        current.row = (*sp).row;
        current.col = (*sp).col;
        list<coord> neighbours = returnNeighbourCoords(current);
        list<coord>::iterator ng;
        for ( ng = neighbours.begin() ; ng != neighbours.end(); ng++ ){
            if( !isFound(sparse,*ng) ){ //not a live member
                cell newmember;
                newmember.row = (*ng).row;
                newmember.col = (*ng).col;
                newmember.isAlive = false;
                newmember.AliveCount = returnAliveCount (sparse,returnNeighbourCoords(*ng));
                if ( newmember.AliveCount == 3 ){
                    newmember.isAlive = false;
                    if( !isFound(newsparse,*ng) )
                        newsparse.push_back (newmember);
                }
            }
            else{ // is a live member
                cell newmember;
                newmember.row = (*ng).row;
                newmember.col = (*ng).col;
                newmember.isAlive = true;
                newmember.AliveCount = returnAliveCount (sparse,returnNeighbourCoords(*ng));
                if ( newmember.AliveCount < 2 || newmember.AliveCount > 3 )
                    newmember.isAlive = false;
                else{
                    if( !isFound(newsparse,*ng) )
                        newsparse.push_back (newmember);
                }
            }
        }
    }
    sparse.clear();
    return newsparse;
}
                
        
                  
                
                
    



list<coord> returnNeighbourCoords (coord currentCell){
    list<coord> neighbours;
    coord temp;
    int x[] = {-1,0,1,-1,1,-1,0,1};
    int y[] = {-1,-1,-1,0,0,1,1,1};
    for ( int i = 0; i < 8; i++ ){
        temp.row = currentCell.row + x[i];
        temp.col = currentCell.col + y[i];
        neighbours.push_back(temp);
    }
    return neighbours;
}


bool isFound ( list<cell> sparse, coord c ){
    list<cell>::iterator sp;
    for ( sp = sparse.begin() ; sp != sparse.end() ; sp++ ){
        if ( (*sp).row == c.row && (*sp).col == c.col )
            return true;
    }
return false;
}
           
    

int returnAliveCount (list<cell> sparse, list<coord> neighbours){
    list<cell>::iterator sp;
    list<coord>::iterator ng;
    int alivecount = 0;
    for ( ng = neighbours.begin() ; ng != neighbours.end() ; ng++ ){
        if( isFound (sparse,*ng) )
            alivecount++;
    }
return alivecount;
}
    
            



/*void PrintMat( vector< vector<int> > SubMat );
vector< vector<int> > returnSubMat(vector< vector<int> > Original, int row, int col);
int returnAliveNeighbours ( vector< vector<int> > SubMat );
vector< vector<int> > initialize(int MAXSIZE);
vector< vector<int> > makeMap(int MATSIZE);
vector< vector<int> > updateConway(vector< vector<int> > Original, int MAXSIZE);

int main(){
    vector< vector<int> > Matrix = makeMap(12);
    PrintMat(Matrix);
    int count = 0;
    while ( count < 20 ){
        Matrix = updateConway(Matrix,12);
        cout << string(50, '\n') << endl;
        PrintMat(Matrix);
        sleep(1);
        count++;
    }
}

vector< vector<int> > updateConway(vector< vector<int> > Original, int MAXSIZE){

vector< vector<int> > initialize(int MAXSIZE){
    vector<int> temp;
    vector< vector<int> > Mat;
    for (int i = 0; i< MAXSIZE; i++){
        for (int j = 0; j<MAXSIZE; j++)
            temp.push_back(0);
        Mat.push_back(temp);
        temp.clear();
    }
    return Mat;
}


void PrintMat( vector< vector<int> > SubMat ){
    for (vector< vector<int> >::size_type u = 0; u < SubMat.size(); u++) { 
        for (vector<int>::size_type v = 0; v < SubMat[u].size(); v++) {
            if ( SubMat[u][v] == -1 )
                cout << "0";
            else if ( SubMat[u][v] == 1 )
                cout << "1";
            else
                cout << " ";
        }
    cout << endl;
    }
}
    
vector < vector<int> > makeMap(int MATSIZE){
    int initiate [12][12];
    for ( int i = 0; i <12; i++ )
        for ( int j = 0; j < 12 ; j++ )
            initiate[i][j] = 0;
    initiate[5][4] = 1;
    initiate[5][5] = 1;
    initiate[5][6] = 1;
    
    vector< vector<int> > MainMap = initialize(MATSIZE);
    for ( int i = 0; i < MATSIZE ; i++){
        for ( int j= 0; j < MATSIZE ; j++){
            if ( i == 0 || j == 0 || i == MATSIZE - 1 || j == MATSIZE - 1 )
                MainMap[i][j] = -1;
            else
                MainMap[i][j] = initiate[i][j];
        }
    }
    return MainMap;
}*/
