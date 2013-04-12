#include<iostream>
#include<list>
#include<utility>

using namespace std;

#define r_max 20
#define c_max 50


typedef struct{
        int x;
        int y;
}coord;

struct fish{
		int x;
		int y;
};

struct shark{
		int x;
		int y;
		float strength;
		int starvetime;
};

void display_gen(list<fish>,list<shark>);
list<shark> updateShark(list<fish> &currentgen_fish,list<shark> &currentgen_shark);
list<fish> updateFish ( list<fish> fishList, list<shark> &sharkList);
list<coord> getNeighbours(coord pos);
bool isFoundShark ( list<shark> sharkList, coord c );
bool isFoundFish ( list<fish> fishList, coord c );
int returnAliveCountFish (list<fish> fishList, list<coord> neighbours);
int returnAliveCountShark (list<shark> sharkList, list<coord> neighbours);
void updateStrength(list<shark> &sharkList, coord pos);


int main() {
		list<fish> currentgen_fish;
		list<fish> nextgen_fish;
		cout << "Enter the no of currentgen fish cells:\n";
		int n;
		cin >> n;
		while (n--) {
				int xno;
				int yno;
				cin >> xno;
				cin >> yno;
				fish temp;
				temp.x = xno;
				temp.y = yno;
				currentgen_fish.push_back(temp);
		}
		list<shark> currentgen_shark;
		list<shark> nextgen_shark;
		cout << "Enter the no of currentgen shark cells:\n";
		int sn;
		cin >> sn;
		while (sn--) {
				int xno;
				int yno;
				cin >> xno;
				cin >> yno;
				shark temp;
				temp.x = xno;
				temp.y = yno;
				temp.strength = 0.0;
				temp.starvetime = 5;
				currentgen_shark.push_back(temp);
		}
		display_gen(currentgen_fish,currentgen_shark);
    
        char c;
        do {
                nextgen_shark = updateShark(currentgen_fish, currentgen_shark);
                nextgen_fish = updateFish(currentgen_fish, nextgen_shark);
                display_gen(nextgen_fish, nextgen_shark);
                currentgen_fish.clear();
                currentgen_shark.clear();
                currentgen_fish = nextgen_fish;
                currentgen_shark = nextgen_shark;
                cout << "would you like to continue?(y/n) ";
                cin >> c;
        }
        while (c == 'y');

		return 0;
}

// To display using high->x high->y low->x low->y !!!

void display_gen(list<fish> currentgen_fish,list<shark> currentgen_shark) {
		list<fish>::iterator it;
		list<shark>::iterator sit;
        it = currentgen_fish.begin();
        sit = currentgen_shark.begin();
        for (int i = 0; i < r_max ; i++) {
                for (int j = 0; j < c_max; j++) {
                        int isMatch = 0;
                        for(it = currentgen_fish.begin(); it != currentgen_fish.end(); it++){
                                if ((*it).x == i && (*it).y == j && it != currentgen_fish.end() ) {
                                        cout << "f";
                                        isMatch = 1;							
                                }
                        }
                        if (isMatch == 0){
                                for(sit = currentgen_shark.begin(); sit != currentgen_shark.end(); sit++){    
                                        if ((*sit).x == i && (*sit).y == j && sit != currentgen_shark.end() ) {
                                                cout << "s";
                                                isMatch = 1; 
                                        }
                                }
                        }
                        if(isMatch == 0) {
                                cout << "-";
                        }
                }
                cout << endl;
        }
        sleep(1);
        return;
}


/*
void new_ocean(list<fish> &currentgen_fish, list<shark> &currentgen_shark) {

        list<shark> nextgen_shark = updateShark(currentgen_fish, currentgen_shark);

        list<fish> nextgen_fish = updateFish(currentgen_fish, nextgen_shark);

}*/

list<shark> updateShark(list<fish> &currentgen_fish,list<shark> &currentgen_shark) {
        list<shark> nextgen_shark;
        list<shark>::iterator sit;
        for (sit = currentgen_shark.begin(); sit != currentgen_shark.end(); sit++) {
                shark temp;
                temp.x = (*sit).x;
                temp.y = (*sit).y;
                temp.starvetime = (*sit).starvetime;
                coord c;
                c.x = temp.x;
                c.y = temp.y;
                list<coord> neighbourhood = getNeighbours(c);
                int countfish = returnAliveCountFish(currentgen_fish,neighbourhood);
                if (countfish > 0){ 
                        temp.starvetime = 0;
                        nextgen_shark.push_back(temp);
                }
                else {
                        if (temp.starvetime > 0) {
                                temp.starvetime--;
                                nextgen_shark.push_back(temp);
                        }
                }
        }
        return nextgen_shark;
}

list<fish> updateFish ( list<fish> fishList, list<shark> &newsharkList){
    list<fish> newfishList;                                             //empty fish list
    list<fish>::iterator fl;
    list<shark> newspawnsharkList;

    for ( fl = fishList.begin() ; fl != fishList.end() ; fl++ ){
        coord current;
        current.x = (*fl).x;
        current.y = (*fl).y;
        list<coord> neighbours = getNeighbours(current); //returns coordinates of the neighbours
        list<coord>::iterator ng;

        if ( returnAliveCountFish (fishList,getNeighbours(current)) == 0 && returnAliveCountShark (newsharkList,getNeighbours(current)) >= 2){
                        updateStrength(newsharkList, current);
                        shark newshark;
                        newshark.x = current.x;
                        newshark.y = current.y;
                        newshark.starvetime = 5;
                        newshark.strength = 0;
                        if (!isFoundShark(newspawnsharkList,current)) {
                                newspawnsharkList.push_back(newshark);
                                cout << "shark spawns in place of fish" << endl;
                        }

        }





        if ( returnAliveCountFish (fishList,getNeighbours(current)) == 0 && returnAliveCountShark (newsharkList,getNeighbours(current)) == 0 ) {
                newfishList.push_back(*fl);
        }

        if ( returnAliveCountFish (fishList,getNeighbours(current)) >= 0 ) {
                for ( ng = neighbours.begin() ; ng != neighbours.end(); ng++ ){  //scanning all the neighbours of current fish
                        if( !isFoundFish(fishList,*ng) && !isFoundShark(newsharkList, *ng) ){ //is an empty cell
                                fish newfish;
                                newfish.x = (*ng).x;
                                newfish.y = (*ng).y;
                                int fAC = returnAliveCountFish (fishList,getNeighbours(*ng));//rules for fish regeneration
                                int sAC = returnAliveCountShark (newsharkList,getNeighbours(*ng));
                                if ( fAC > 1 && sAC < 2 && !isFoundFish(newfishList,*ng) ){//new fish spawns
                                        if (!isFoundFish(newfishList,*ng)) {
                                                newfishList.push_back (newfish);
                                        }
                                }
                                if ( fAC >= 2 && sAC >=2 ){ //shark spawns
                                        shark newshark;
                                        newshark.x = (*ng).x;
                                        newshark.y = (*ng).y;
                                        newshark.starvetime = 0;
                                        newshark.strength = 0;
                                        if (!isFoundShark(newspawnsharkList,*ng)) {
                                                newspawnsharkList.push_back(newshark);
                                        }

                                }
                        }
                        if ( isFoundFish(fishList,*ng) && !isFoundFish(newfishList, *ng) && !isFoundShark(newspawnsharkList,*ng)){ // is a live fish member not updated
                                fish newfish;
                                newfish.x = (*ng).x;
                                newfish.y = (*ng).y;
                                int sAC = returnAliveCountShark (newsharkList,getNeighbours(*ng));// rules for fish consumption or shark respawn

                                if ( sAC == 1 )  //current fish eaten by only 1 shark
                                        updateStrength(newsharkList, *ng);


                                else if ( sAC >= 2 ){ //the fish is eaten by multiple and a new shark is spawned
                                        updateStrength(newsharkList, *ng);
                                        shark newshark;
                                        newshark.x = (*ng).x;
                                        newshark.y = (*ng).y;
                                        newshark.starvetime = 0;
                                        newshark.strength = 0;
                                        if (!isFoundShark(newsharkList,*ng)) {
                                                newspawnsharkList.push_back(newshark);
                                                cout << "shark spawns in place of fish" << endl;
                                        }
                                }

                                else if (sAC == 0) { //the fish continues to next generation
                                        fish newfish;
                                        newfish.x = (*ng).x;
                                        newfish.y = (*ng).y;
                                        if (!isFoundFish(newfishList,*ng)) {
                                                newfishList.push_back(newfish);
                                        }
                                }
                        }
                }
        }
    }

    list<shark>::iterator sit;
    
    for (sit = newspawnsharkList.begin(); sit != newspawnsharkList.end(); sit++) {
            coord ctemp;
            ctemp.x = (*sit).x;
            ctemp.y = (*sit).y;
            if (!isFoundShark(newsharkList,ctemp)) {
                    newsharkList.push_back((*sit));
            }
    }
    cout << "Size of new sharklist " << newsharkList.size() << endl;

    return newfishList;
}



                

list<coord> getNeighbours(coord pos){
        list<coord> neighbours;
        int xUpRange = pos.x+1;
        int xDownRange = pos.x-1;
        int yUpRange = pos.y+1;
        int yDownRange = pos.y-1;


        for (int i = xDownRange; i <= xUpRange; i++){
                for (int j = yDownRange; j <= yUpRange; j++){
                        if (!(pos.x == i && pos.y == j)){
                                coord neigh;
                                neigh.x = i%r_max;
                                if (neigh.x < 0)
                                        neigh.x = r_max - 1;
                                neigh.y = j%c_max;
                                if (neigh.y < 0)
                                        neigh.y = c_max - 1;
                                neighbours.push_back(neigh);
                        }
                }
        }
        return neighbours;
}
                
                

void updateStrength(list<shark> &sharkList, coord pos){
        list<coord> neighbours = getNeighbours(pos);
        list<shark> :: iterator sharkIt;
        float numOfSharkInNeighbours = 0;
        list<coord>:: iterator it;
        for(it = neighbours.begin(); it != neighbours.end(); it++){
                for(sharkIt = sharkList.begin(); sharkIt != sharkList.end(); sharkIt++){
                        if ((*it).x == (*sharkIt).x  && (*it).y == (*sharkIt).y)
                                numOfSharkInNeighbours++;
                }
        }

        if(numOfSharkInNeighbours){
                float strengthUp = 1/numOfSharkInNeighbours ;
                for(it = neighbours.begin(); it != neighbours.end(); it++){
                        for(sharkIt = sharkList.begin(); sharkIt != sharkList.end(); sharkIt++){
                                if ((*it).x == (*sharkIt).x  && (*it).y == (*sharkIt).y)
                                        (*sharkIt).strength = (*sharkIt).strength+strengthUp;

                        }
                }
        }
}




bool isFoundFish ( list<fish> fishList, coord c ){
    list<fish>::iterator sp;
    for ( sp = fishList.begin() ; sp != fishList.end() ; sp++ ){
        if ( (*sp).x == c.x && (*sp).y == c.y )
            return true;
    }
return false;
}
           
    
bool isFoundShark ( list<shark> sharkList, coord c ){
    list<shark>::iterator sp;
    for ( sp = sharkList.begin() ; sp != sharkList.end() ; sp++ ){
        if ( (*sp).x == c.x && (*sp).y == c.y )
            return true;
    }
return false;
}

int returnAliveCountFish (list<fish> fishList, list<coord> neighbours){
    list<fish>::iterator sp;
    list<coord>::iterator ng;
    int alivecount = 0;
    for ( ng = neighbours.begin() ; ng != neighbours.end() ; ng++ ){
        if( isFoundFish (fishList,*ng) )
            alivecount++;
    }
return alivecount;
}
    

int returnAliveCountShark (list<shark> sharkList, list<coord> neighbours){
    list<shark>::iterator sp;
    list<coord>::iterator ng;
    int alivecount = 0;
    for ( ng = neighbours.begin() ; ng != neighbours.end() ; ng++ ){
        if( isFoundShark (sharkList,*ng) )
            alivecount++;
    }
return alivecount;
}

