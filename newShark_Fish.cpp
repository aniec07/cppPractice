#include <iostream>
#include <list>
#include <set>
#include <math.h>
#include <utility>
#include <vector>
//#include <windows.h>

using namespace std;

#define r_max 20
#define c_max 50
#define initialStrength 4

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
		set<coord> blackMap;
};

//display status of the ocean in each generation
void displayGeneration(list<fish>,list<shark>);

list<shark> updateSharkList(list<fish> &,list<shark> &, list<shark> &);

list<fish> updateFishList ( list<fish> &, list<shark> &, list<shark> &);

void updateSharkStrength(list<shark> &sharkList, coord pos);

void SharkEatsSharkWhenFishExtinct(list<shark> &, list<shark> &);

void moveShark(list<fish>, list<shark> &, list<shark>);

bool compareSharkStrength(shark, shark);

void SharkEatsSharkWhenFishNotInVicinity(list<shark> &, list<shark> &);

list<coord> getNeighbours(coord pos);

bool isFoundShark ( list<shark> sharkList, coord c );

bool isFoundFish ( list<fish> fishList, coord c );

int returnAliveCountFish (list<fish> fishList, list<coord> neighbours);

int returnAliveCountShark (list<shark> sharkList, list<coord> neighbours);

int main() {
		list<fish> currentgen_fish;
		list<fish> nextgen_fish;
		cout << "Enter the no of currentgen fish cells:\n";
		int n;
		cin >> n;
		if (n > 0)
		   cout << "Enter the coordinates of fish cells:\n";
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
		if (sn > 0)
		   cout << "Enter the coordinates of shark cells:\n";
		while (sn--) {
				int xno;
				int yno;
				cin >> xno;
				cin >> yno;
				shark temp;
				temp.x = xno;
				temp.y = yno;
				temp.strength = 1.0;
				temp.starvetime = initialStrength;
				currentgen_shark.push_back(temp);
		}
		
        displayGeneration(currentgen_fish,currentgen_shark);
		for (int i = 0; i < c_max; i++) {
            cout << "*";
        }
        cout << endl;
        
        char c = 'y';
        while (c == 'y') {
                //Sleep(500);
                list<shark> hungryShark;
                /*if (currentgen_fish.size() != 0 && currentgen_shark.size() == 0) {
                     cout << "No sharks remaining" << endl;
                     break;
                }
                else if (currentgen_fish.size() == 0 && currentgen_shark.size() == 0) {
                   cout << "Ocean is empty" << endl;
                   break;
                }
                else if (currentgen_fish.size() == 0 && currentgen_shark.size() != 0) {
                     SharkEatsSharkWhenFishExtinct(currentgen_shark, hungryShark);
                     moveShark(currentgen_fish, currentgen_shark, hungryShark);
                     displayGeneration(currentgen_fish, currentgen_shark);
                     cout << "Show Next Generation?(y/n) ";
                     cin >> c;
                }
                else {                 
                     currentgen_shark = updateSharkList(currentgen_fish, currentgen_shark, hungryShark);
                     currentgen_fish = updateFishList(currentgen_fish, currentgen_shark, hungryShark);
                     displayGeneration(currentgen_fish, currentgen_shark);
                     cout << "Show Next Generation?(y/n) ";
                     cin >> c;
                     
                }*/
                if ( currentgen_shark.size() ){
                        cout << "Show Next Generation? (y/n) : ";
                        cin >> c;
                        if ( currentgen_fish.size() ){
                                currentgen_shark = updateSharkList(currentgen_fish, currentgen_shark, hungryShark);
                                currentgen_fish = updateFishList(currentgen_fish, currentgen_shark, hungryShark);
                        }
                        else{
                                SharkEatsSharkWhenFishExtinct(currentgen_shark, hungryShark);
                                moveShark(currentgen_fish, currentgen_shark, hungryShark);
                        }
                        displayGeneration(currentgen_fish, currentgen_shark);
                }
                else{
                        cout << "Ocean contains ";
                        if ( currentgen_fish.size() )
                                cout << "no sharks " << endl;
                        else
                                cout << "nothing " << endl;
                        break;
                }


                hungryShark.clear();
                for (int i = 0; i < c_max; i++) {
                    cout << "*";
                }
                cout << endl;
        }
        system("pause");
        
		return 0;
}

// To display using high->x high->y low->x low->y !!!

void displayGeneration(list<fish> currentgen_fish,list<shark> currentgen_shark) {
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
                                                if ((*sit).strength <= 1.5) {
                                                     cout << "s";
                                                
                                                }
                                                else if ((*sit).strength >= 1.5 && (*sit).strength <= 2.5 ){
                                                     cout << "S";
                                                }
                                                else
                                                        cout << "$";
                                                
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
        return;
}


/*
void new_ocean(list<fish> &currentgen_fish, list<shark> &currentgen_shark) {

        list<shark> nextgen_shark = updateSharkList(currentgen_fish, currentgen_shark);

        list<fish> nextgen_fish = updateFishList(currentgen_fish, nextgen_shark);

}*/

list<shark> updateSharkList(list<fish> &currentgen_fish,list<shark> &currentgen_shark, list<shark> &hungryShark) {
        list<shark> nextgen_shark;
        list<shark>::iterator sit;
        list<shark> hungryAndDyingShark;
        for (sit = currentgen_shark.begin(); sit != currentgen_shark.end(); sit++) {
                shark temp;
                temp.x = (*sit).x;
                temp.y = (*sit).y;
                temp.starvetime = (*sit).starvetime;
                temp.strength = (*sit).strength;
                coord c;
                c.x = temp.x;
                c.y = temp.y;
                list<coord> neighbourhood = getNeighbours(c);
                
                int countfish = returnAliveCountFish(currentgen_fish,neighbourhood);
                
                if (countfish == 0) {
                   if (temp.starvetime >= 0) {
                              temp.starvetime--;
                              nextgen_shark.push_back(temp);
                              hungryShark.push_back(temp);
                              if (temp.starvetime <= 2) {
                                            hungryAndDyingShark.push_back(temp);
                              }
                   }
                }
                else if (countfish > 0){ 
                        temp.starvetime = initialStrength;
                        nextgen_shark.push_back(temp);
                }
                
        }
        SharkEatsSharkWhenFishNotInVicinity(nextgen_shark, hungryAndDyingShark);
        hungryAndDyingShark.clear();
        return nextgen_shark;
}

list<fish> updateFishList ( list<fish> &fishList, list<shark> &newsharkList, list<shark> &hungryShark){
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
                        updateSharkStrength(newsharkList, current);
                        shark newshark;
                        newshark.x = current.x;
                        newshark.y = current.y;
                        newshark.starvetime = initialStrength;
                        newshark.strength = 1.0;
                        if (!isFoundShark(newspawnsharkList,current)) {
                                newspawnsharkList.push_back(newshark);
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
                                        newshark.starvetime = initialStrength;
                                        newshark.strength = 1.0;
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
                                        updateSharkStrength(newsharkList, *ng);


                                else if ( sAC >= 2 ){ //the fish is eaten by multiple and a new shark is spawned
                                        updateSharkStrength(newsharkList, *ng);
                                        shark newshark;
                                        newshark.x = (*ng).x;
                                        newshark.y = (*ng).y;
                                        newshark.starvetime = initialStrength;
                                        newshark.strength = 1.0;
                                        if (!isFoundShark(newsharkList,*ng)) {
                                                newspawnsharkList.push_back(newshark);
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
//    moveShark(newfishList,newsharkList,hungryShark);
    moveShark(newfishList, newsharkList, hungryShark);
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
                
                

void updateSharkStrength(list<shark> &sharkList, coord pos){
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
                float strengthUp = 1.0/numOfSharkInNeighbours ;
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

void SharkEatsSharkWhenFishExtinct(list<shark> &currentgen_shark, list<shark> &hungryShark) {
            int minCount = currentgen_shark.size();
                  //cout << "reached here" << endl;
                  float eps = 0.001;
                  list<shark>::iterator it;
                  currentgen_shark.sort(compareSharkStrength);
                  
            for (it  = currentgen_shark.begin(); it != currentgen_shark.end(); it++) {
                      list<coord> nbhood;
                      coord minSharkPos;
                      minSharkPos.x = (*it).x;
                      minSharkPos.y = (*it).y;
            
                      nbhood = getNeighbours(minSharkPos);        
                      list<coord>::iterator it_nb;
                      int aliveCount = returnAliveCountShark(currentgen_shark, nbhood);
                      if (aliveCount > 0) {
                         for (it_nb = nbhood.begin(); it_nb != nbhood.end(); it_nb++) {
                              if (isFoundShark (currentgen_shark, *it_nb)) {
                                      list<shark>::iterator nit;
                                      for (nit = currentgen_shark.begin(); nit != currentgen_shark.end(); nit++) {
                                          if ( (*nit).x == (*it_nb).x && (*nit).y == (*it_nb).y ) {
                                                   (*nit).strength += 2.0/aliveCount;
                                                   (*nit).starvetime = initialStrength;
                                          }
                                      }
                              }
                         }
                      it = currentgen_shark.erase(it);
                      }
                      else {
                           if ((*it).starvetime > 0) {
                                (*it).starvetime--;
                                hungryShark.push_back((*it));
                           }
                           else {
                                it = currentgen_shark.erase(it);
                           }
                      }
                }
            return;
}

bool compareSharkStrength(shark s1, shark s2) {
     
     if (s1.strength >= s2.strength)
        return true;
     else
         return false;
}
     
void moveShark(list<fish> nextgen_fish, list<shark> &nextgen_shark, list<shark> hungryShark) {	
	list<shark> :: iterator hShark;
	list<shark> oldSharkList = nextgen_shark;
	for (hShark = hungryShark.begin(); hShark != hungryShark.end(); hShark++){
		list<coord> neighbours;
		vector<coord> freeNeigh;
		coord pos;
		pos.x = (*hShark).x;
		pos.y = (*hShark).y;
		neighbours = getNeighbours(pos);
		list<coord> :: iterator it;
		for(it = neighbours.begin(); it != neighbours.end(); it++){
			if (!isFoundFish (nextgen_fish, (*it)) && !isFoundShark (nextgen_shark, (*it) ) && !isFoundShark (oldSharkList, (*it) ))
				freeNeigh.push_back(*it);
		}
		int lenOfFreeNeigh = freeNeigh.size();
		//cout << ((*hShark).strength) << endl;
        if(lenOfFreeNeigh && (*hShark).strength > 0){
			srand (time(NULL));
			int movement = rand()%(lenOfFreeNeigh);
			
			coord nextPos = freeNeigh[movement];
			
			list<shark>::iterator sit;
			for(sit = nextgen_shark.begin(); sit != nextgen_shark.end(); sit++){
				if ( (*sit).x == pos.x && (*sit).y == pos.y ){
					(*sit).x = nextPos.x;
					(*sit).y = nextPos.y;
					(*sit).strength = (*sit).strength-(*sit).strength/5;
				}
			}	
		}
	
	}
}

void SharkEatsSharkWhenFishNotInVicinity(list<shark> &currentgen_shark, list<shark> &hungryAndDyingShark) {
     
     list<shark>::iterator sit; 
 	 for (sit = currentgen_shark.begin(); sit != currentgen_shark.end(); sit++) {
 	     coord pos;
         pos.x = (*sit).x;
	     pos.y = (*sit).y;
	     list<coord> neighbours;
 	     neighbours = getNeighbours(pos);
 	     list<coord>:: iterator it;
 	     list<list<shark>::iterator > save_it;
 	     list<shark>::iterator hungry_it;
  	     int countStrongShark = 0;
		 for(it = neighbours.begin(); it != neighbours.end(); it++){
                for (hungry_it = hungryAndDyingShark.begin(); hungry_it != hungryAndDyingShark.end(); hungry_it++) {
                    if ((*hungry_it).x == (*it).x && (*hungry_it).y == (*it).y && (*hungry_it).strength > (*sit).strength) {
                             save_it.push_back(hungry_it);
                             countStrongShark++;
                    }
                }
         }
         list<list<shark>::iterator >::iterator i2;
         if (countStrongShark > 0) {
            for (i2 = save_it.begin(); i2 != save_it.end(); i2++) {
                (**i2).strength = (**i2).strength + 2.0/countStrongShark;
            }
            sit = currentgen_shark.erase(sit);
         }
   }
                  
}
