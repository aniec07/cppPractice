#include <iostream>
#include <vector>

using namespace std;

struct filler{
    bool rightflag;
    bool downflag;
    bool isblack;
    int number;
};

typedef filler cell;

vector< vector<cell> > initiate(int initializer[][15], int MATSIZE);
bool isWordStartPossible ( vector< vector<cell> > CWord, int MATSIZE, int u, int v, char direction );
vector< vector<cell> > CrossFiller ( vector< vector<cell> > CWord, int MATSIZE );

int main(){
    int initializer[15][15] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,1,1,1,1,1,0,1,1,1,1,1,1,1,0},
                               {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
                               {0,1,1,1,0,1,1,1,1,1,1,1,1,1,0},
                               {0,1,0,1,0,1,0,1,0,1,0,0,0,1,0},
                               {0,1,1,1,1,1,1,1,0,1,1,1,1,1,0},
                               {0,1,0,1,0,0,0,1,0,1,0,1,0,0,0},
                               {0,1,1,1,1,1,1,0,1,1,1,1,1,1,0},
                               {0,0,0,1,0,1,0,1,0,0,0,1,0,1,0},
                               {0,1,1,1,1,1,0,1,1,1,1,1,1,1,0},
                               {0,1,0,0,0,1,0,1,0,1,0,1,0,1,0},
                               {0,1,1,1,1,1,1,1,1,1,0,1,1,1,0},
                               {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
                               {0,1,1,1,1,1,1,1,0,1,1,1,1,1,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
     vector< vector<cell> > CWord = initiate(initializer, 15);
     CWord = CrossFiller ( CWord, 15 );
    for (vector< vector<cell> >::size_type u = 0; u < CWord.size(); u++) {
        for (vector<cell>::size_type v = 0; v < CWord[u].size(); v++) {
            if ( CWord[u][v].isblack )
                cout << "  ";
            if ( CWord[u][v].number > 9)
                cout <<  CWord[u][v].number;
            if ( CWord[u][v].number > 0 && CWord[u][v].number <= 9 )
                cout << "0" << CWord[u][v].number;
            if ( CWord[u][v].number == 0 && !CWord[u][v].isblack)
                cout << "__";    
        }
    cout << endl;
    }
}

vector< vector<cell> > initiate(int initializer[][15], int MATSIZE){
    vector< vector<cell> > CWord;
    vector<cell> temprow;
    cell tempcell;
    for ( int i = 0; i < MATSIZE ; i++){
        for ( int j= 0; j < MATSIZE ; j++){
            if ( initializer[i][j] == 0){
                tempcell.number = 0;
                tempcell.rightflag = false;
                tempcell.downflag = false;
                tempcell.isblack = true;
            }
            else {
                tempcell.number = 0;
                tempcell.rightflag = false;
                tempcell.downflag = false;
                tempcell.isblack = false;
            }
            temprow.push_back(tempcell);
        }
        CWord.push_back(temprow);
        temprow.clear();
    }
    return CWord;
}

bool isWordStartPossible ( vector< vector<cell> > CWord, int MATSIZE, int u, int v, char direction ){
    if ( u < MATSIZE-1 && v < MATSIZE-1 ){
        if ( (CWord[u][v]).isblack )
            return false;
        if ( direction == 'r' ){
            if ( !(CWord[u][v+1]).isblack && !(CWord[u][v+1]).rightflag && !CWord[u][v].rightflag )
                return true;
            else
                return false;
        }
        else{         
            if ( !(CWord[u+1][v]).isblack && !(CWord[u][v]).downflag && !CWord[u+1][v].downflag )
                return true;
            else
                return false;
        }
    }
    else
        return false;
}
        
   
vector< vector<cell> > CrossFiller ( vector< vector<cell> > CWord, int MATSIZE ){
    int wordcount = 1;
    int rightmove = 0;
    int downmove = 0;
    for (vector< vector<cell> >::size_type u = 0; u < CWord.size()-1; u++)
        for (vector<cell>::size_type v = 0; v < CWord[u].size() -1 ; v++) {
            if ( isWordStartPossible( CWord, MATSIZE, u, v, 'r') ){
                rightmove = v;
                while (!(CWord[u][rightmove+1]).isblack ){
                    CWord[u][rightmove].rightflag = true;
                    rightmove++;
                }
                CWord[u][v].number = wordcount;
                if( !isWordStartPossible( CWord, MATSIZE, u, v, 'd') )    
                    wordcount++;
            }
            if ( isWordStartPossible( CWord, MATSIZE, u , v, 'd') ){          
                downmove = u;
                while (!(CWord[downmove+1][v]).isblack ){
                    CWord[downmove][v].downflag = true;
                    downmove++;
                }
                CWord[u][v].number = wordcount;
                wordcount++;
            }
        }
    return CWord;
}

                    
                
    
