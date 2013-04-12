#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<queue>
#include<fstream>

using namespace std;

struct visited {
		bool isvisited;
		int heuristic;
		string parent;
};

void bfs(string,map<string,visited> &,map<string,vector<string> >,queue<string> &);
void Print_Parent(string,string,map<string,visited> );
map<string,vector<string> > MakeGraph( vector<string> WordList );
map<string,visited> populate_node_status(map<string,vector<string> > init_graph);

int main() {
		map<string,vector<string> > Edit_Dist;
        string initial, final; 
        ifstream myReadFile;
        myReadFile.open("dict");
        string output;
        int count = 0;
        vector<string> WordList;
        if (myReadFile.is_open()) {
                while (!myReadFile.eof()) {
                        myReadFile >> output;
                        if ( output.length() == 5 && (output[0] - 'a') >= 0 ){ 
                                WordList.push_back(output);
                        }
                }

        }
        cout << WordList.size();
        myReadFile.close();
        cout << "Building Dictionary " << endl;
        Edit_Dist = MakeGraph(WordList);
        //PrintGraph (LookUp);
        cout << "Dictionary Built " << endl;
        map<string, visited> NS = populate_node_status(Edit_Dist);
		cout << "Enter The Start Word:" << endl;
		cin >> initial;

		cout << "Enter The End Word:" << endl;
		cin >> final;
		
		queue<string> bfstree;
		bfstree.push(initial);
		struct visited temp = NS[initial];
		temp.parent = "Root";
		temp.isvisited = true;
		NS[initial] = temp;

		bfs(final,NS,Edit_Dist,bfstree);

		cout << endl << "Final To Initial Path is:\n" << endl;

		Print_Parent(initial,final,NS);

		return 0;
}


map<string,visited> populate_node_status(map<string,vector<string> > init_graph) {
    visited tmp;
    tmp.isvisited = false;
    map<string,visited> node_table;
    for (map<string,vector<string> >::iterator it = init_graph.begin(); it != init_graph.end(); it++) {
        node_table.insert(pair<string, visited>((*it).first,tmp));
    }  
    return node_table;
}

map<string,vector<string> > MakeGraph( vector<string> WordList ){

    vector<string>::iterator it;
    vector<string> editDist;
    map<string,vector<string> >  LookUp;
    for ( it = WordList.begin(); it != WordList.end() ; it++ )
        LookUp[*it] = editDist;
    for ( it = WordList.begin(); it != WordList.end() ; it++ ){
        string temp = *it;
        for ( int i = 0; i < temp.length() ; i++ ){                     //replacing characters
            temp = *it;
            for ( char ch = 'a' ; ch <= 'z' ; ch++ ){
                if ( temp[i] != ch ){
                    temp[i] = ch;
                    if ( LookUp.find(temp) != LookUp.end() )
                        editDist.push_back(temp);
                    temp = *it;
                }
            }
        }
        //    cout << "\nTESTING for " << *it << endl;
        //    for(list<string>::iterator it1 = editDist.begin(); it1 != editDist.end(); it1++) {
        //    cout << *it1 << " ";
        //    cout << "\nTESTING DONE\n";
        //    }
        LookUp[*it] = editDist;
        editDist.clear();
    }
return LookUp;
}

void Print_Parent(string initial,string search,map<string,visited> Words) {
		struct visited temp = Words[search];
		if (search.compare(initial) == 0) {
				cout << initial << endl;
				return;
		}
		else {
				cout << search << endl;
				Print_Parent(initial,temp.parent,Words);
		}
		return;
}

void bfs(string final,map<string,visited> &NS,map<string,vector<string> > Edit_Dist,queue<string> &bfstree) {
		if (bfstree.empty())
				return;
		string temp = bfstree.front();
		bfstree.pop();
		vector<string> adjacent = Edit_Dist[temp];
		vector<string>::iterator it;
		for (it = adjacent.begin();it != adjacent.end(); it++) {
				struct visited Wtemp = NS[(*it)];
				if ((*it) != final && Wtemp.isvisited == false) {
						Wtemp.parent = temp;
						Wtemp.isvisited = true;
						NS[(*it)] = Wtemp;
						bfstree.push((*it));
				}
				else if ((*it) != final && Wtemp.isvisited == true) {
				}
				else if ((*it) == final){
						Wtemp.parent = temp;
						Wtemp.isvisited = true;
						NS[(*it)] = Wtemp;
						cout << "Match" << endl;
						return;
				}
		}
		bfs(final,NS,Edit_Dist,bfstree);
		return;
}

