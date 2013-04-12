#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <string>

using namespace std;

typedef struct{
    bool visited;
    int hamming;
    string parent;
    }Word;

typedef map<string, list<string> > Graph;
typedef map<string, Word> NodeStatus; 

void PrintGraph (Graph MakeGraph);
Graph MakeGraph( vector<string> WordList );
NodeStatus populate_node_status(Graph init_graph);
string breadthSearch (Graph LookUp, NodeStatus &node_table, string start, string last);
void printBFS(NodeStatus &node_table, string first, string last);
int ConvertStringToNumber(string num);
int checkDiffer(string s1, string s2);

int main(int c, char *argv[]){

    ifstream myReadFile;
    myReadFile.open("dict");
    string output;
    int count = ConvertStringToNumber(argv[1]);
    vector<string> WordList;
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;
            if ( output.length() == count && (output[0] - 'a') >= 0 ){ 
               WordList.push_back(output);
            }
        }

    }
    cout << WordList.size();
    myReadFile.close();
    cout << "Building Dictionary " << endl;
    Graph LookUp = MakeGraph(WordList);
    //PrintGraph (LookUp);
    cout << "Dictionary Built " << endl;
    Graph::iterator it1,it2;
    string s1,s2;
    for ( it1 = LookUp.begin() ; it1 != LookUp.begin() ; it++ )
        for ( it2 = LookUp.begin() ; it2 != LookUp.begin() ; it++ ){
            s1 = (*it1).first;
            s2 = (*it2).first;
            if ( checkDiffer(s1,s2) == count ){
                
            
    
                NodeStatus NS = populate_node_status(LookUp);
                //string start = argv[2];
                //string last = argv[3];
                string result = breadthSearch(LookUp,NS,s1,s2);
                if ( result.compare(start) == 0 )
                    cout << "Conversion Invalid" <<endl;
                else{
                    cout << "The Path is: " <<  endl;
                    printBFS(NS,start,last);
                    }
            }
        }    
    
return 0;
}

int ConvertStringToNumber(string num){
    char *chararr1;
    chararr1 = new char[num.length()];
    for ( int i = 0; i < num.length() ; i++){
        chararr1[i] = num[i];
    }
    int number = atoi (chararr1);
    return number;
}

int checkDiffer(string s1, string s2){
    int dif = 0;
    for ( int i = 0 ; i < s1.length() ; i++ )
        if ( s1[i] != s2[i] )
            dif++;
    return dif;
}
   
void printBFS(NodeStatus &node_table, string first, string last){
    vector<string> path;
    path.push_back(last);
    while ( ((node_table.find(last))->second.parent).compare(first) != 0 ){
        path.push_back((node_table.find(last))->second.parent);
        last = path.back();
    }
    cout << first ;
    for ( vector<string>::iterator it = path.end() - 1 ; it >= path.begin() ; it-- )
        cout << " --> " << *it;
    cout << endl;
}
    

string breadthSearch (Graph LookUp, NodeStatus &node_table, string start, string last){
        queue<string> breadth;
        breadth.push(start);
        (node_table.find(start))->second.visited = true;
        bool found = false;
        if ( start.compare(last) == 0 )
            found = true;
        list<string> editDist;
        list<string>::iterator it;
        while ( breadth.size() > 0 && !found ){

                editDist = (LookUp.find(breadth.front()))->second;
    
                for ( it = editDist.begin() ; it != editDist.end() && !found ; it++ ){
                    if ( (node_table.find(*it))->second.visited == false ){
                        (node_table.find(*it))->second.visited = true;
                        (node_table.find(*it))->second.parent = breadth.front();
                        breadth.push(*it);
                        if ( (*it).compare(last) == 0 )
                            found = true;
                     }
                }
                breadth.pop();
                    
        }
        if ( breadth.size() > 0 )
            return breadth.back();
        else
            return start;
}   
                    
    

NodeStatus populate_node_status(Graph init_graph) {
    Word tmp;
    tmp.visited = false;
    NodeStatus node_table;
    for (Graph::iterator it = init_graph.begin(); it != init_graph.end(); it++) {
        node_table.insert(pair<string, Word>((*it).first,tmp));
    }  
    return node_table;
}



Graph MakeGraph( vector<string> WordList ){
    vector<string>::iterator it;
    list<string> editDist;
    Graph LookUp;
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
                    

void PrintGraph (Graph MakeGraph){
    Graph::iterator it;
    for ( it = MakeGraph.begin(); it != MakeGraph.end(); it++ ){
        list<string>::iterator s;
        for ( s = (*it).second.begin() ; s != (*it).second.end() ; s++ )
            cout << *s << " " ;
        cout << endl;
    }
}
    
            
        
    
        
        
        





