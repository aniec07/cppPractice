#include <iostream>
#include <vector>

using namespace std;

typedef struct{
int row;
int col;
} cell;

int returnAliveNeighbours(vector < vector<int> > MainMat, cell coord);
vector < vector<int> > updateConway ( vector <vector<int> > MainMat );
vector < vector<int> > initMap(int MATSIZE);

int main(){
    vector < vector<int> > MainMap = initMap(12);
    int count = 0;
    while ( count < 4 ){
         
        //MainMap = updateConway (MainMap);
        for (vector< vector<int> >::size_type u = 0; u < MainMap.size(); u++) {
            for (vector<int>::size_type v = 0; v < MainMap[u].size(); v++) {
                if ( MainMap[u][v] == 1 )
                    cout << MainMap[u][v];
                else if ( MainMap[u][v] == 0 )
                    cout<<" ";
                else
                    cout<<"O";
            }
        cout << endl;
        }
    cell coord;
    coord.row = 5;
    coord.col = 4;
    cout << "Check Alive: " << returnAliveNeighbours ( MainMap, coord) << endl;
    for ( int j = 0 ; j < 100000 ; j++);
    count++;
        MainMap = updateConway (MainMap);
    }    
}
        

int returnAliveNeighbours( vector < vector<int> > MainMat, cell coord){
    int AliveSize = 0;
    for (vector< vector<int> >::size_type u = coord.row - 1; u <= coord.row + 1; u++) 
        for (vector<int>::size_type v = coord.col - 1; v <= coord.col + 1; v++)
            if ( u !=coord.row && v!=coord.col ) 
               if ( MainMat [u][v] == 1 )
                    AliveSize++;
    return AliveSize;
}

vector < vector<int> > updateConway ( vector < vector<int> > MainMat ){
    vector < vector<int> > NewMat = initMap(12);
    int alivecount = 0;
    cell coord;
    int MATSIZE = 12;
    int i=0;
    int j=0;
    for (vector< vector<int> >::size_type u = 0; u < MainMat.size(); u++) {
        for (vector<int>::size_type v = 0; v < MainMat[u].size(); v++) {
            if ( MainMat[u][v]!= -1){
                coord.row = u;
                coord.col = v;
                alivecount = returnAliveNeighbours ( MainMat, coord );
                if ( MainMat[u][v] == 1){
                    if ( alivecount < 2 || alivecount > 3)
                        NewMat[u][v] = 0;
                    else
                        NewMat[u][v] = 1;
                }
                if ( MainMat[u][v] == 0 ){
                    if ( alivecount == 3 )
                        NewMat[u][v] = 1;
                    else
                        NewMat[u][v] = 0;
                }
            }
        }
    }
    return NewMat;
}    


            
vector < vector<int> > initMap(int MATSIZE){
    int initiate [12][12];
    for ( int i = 0; i <12; i++ )
        for ( int j = 0; j < 12 ; j++ )
            initiate[i][j] = 0;
    initiate[5][4] = 1;
    initiate[5][5] = 1;
    initiate[5][6] = 1;
    
    vector< vector<int> > MainMap;
    vector<int> temprow;
    for ( int i = 0; i < MATSIZE ; i++){
        for ( int j= 0; j < MATSIZE ; j++){
            if ( i == 0 || j == 0 || i == MATSIZE - 1 || j == MATSIZE - 1 )
                temprow.push_back(-1);
            else
                temprow.push_back(initiate[i][j]);
        }
        MainMap.push_back(temprow);
        temprow.clear();
    }
    return MainMap;
}
 
