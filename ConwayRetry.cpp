#include <iostream>
#include <vector>
#include <string>

using namespace std;

void PrintMat( vector< vector<int> > SubMat );
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
    //vector< vector<int> >SubM = returnSubMat(Matrix,4,5);
    //PrintMat(SubM);
    //sleep(10);
    //vector< vector<int> >upMat = updateConway(Matrix,12);
    //PrintMat(upMat);
    //cout<<returnAliveNeighbours(SubM)<<endl;
    //cout<<upMat[4][5]<< "  " <<upMat[6][5] << endl;
}

vector< vector<int> > updateConway(vector< vector<int> > Original, int MAXSIZE){
    vector < vector<int> > update = Original;
    for ( int i = 0; i< MAXSIZE; i++ )
        for ( int j = 0; j<MAXSIZE; j++){
            if ( Original[i][j] == -1)
                update[i][j] = -1;
            else{
                int alive = returnAliveNeighbours(returnSubMat(Original,i,j));
                if ( Original[i][j] == 1 ){
                    --alive;
                    if ( alive == 2 || alive == 3 ){
                        update[i][j] = 1;
                    }
                    else{
                        update[i][j] = 0;
                    }
                }
                if ( Original[i][j] == 0 ){
                    if ( alive == 3){
                        update[i][j] = 1;
                    }
                }
            }
        }
    return update;
}
            
    

int returnAliveNeighbours ( vector< vector<int> > SubMat ){
    int Alive = 0;
    for (vector< vector<int> >::size_type u = 0; u < SubMat.size(); u++) {
        for (vector<int>::size_type v = 0; v < SubMat[u].size(); v++) {
            if ( SubMat[u][v] == 1 )
                Alive++;
        }
    }
    return Alive;
}

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

vector< vector<int> > returnSubMat(vector< vector<int> > Original, int row, int col){
    int i = 0;
    int j = 0;
    vector < vector<int> > Sub;
    Sub = initialize(3);
    for (i = row - 1; i <= row + 1; i++) { 
        for (j = col - 1 ; j <= col + 1; j++) {
            Sub[i-row+1][j-col+1] = Original[i][j];
        }
    }
    return Sub;
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
}
