#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <string>

using namespace std;

// Creating typedefs

typedef struct{
    bool visited;
    int hamming;
    string parent;
    }Word;

typedef map<string, list<string> > Graph;
typedef map<string, Word> NodeStatus; 


// Function Prototypes

void PrintGraph (Graph MakeGraph);
Graph MakeGraph( vector<string> WordList );
NodeStatus populate_node_status(Graph init_graph);
string breadthSearch (Graph LookUp, NodeStatus &node_table, string start, string last);
void printBFS(NodeStatus &node_table, string first, string last);
int ConvertStringToNumber(string num);
bool isValidWord(string,vector<string>);




int main(int c, char *argv[]){

    ifstream myReadFile;
    myReadFile.open("dict");
    string output;
    int count;
    vector<string> WordList;
    vector<string> FullDict;
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;
            FullDict.push_back(output);
        }

    }
    myReadFile.close();
    string start = argv[1];
    string last = argv[2];
    int len1 = start.length();
    int len2 = last.length();
    bool one = isValidWord(start,FullDict);
    bool two = isValidWord(last,FullDict);

    if ( one && two ) {
            ifstream myReadFile;
            myReadFile.open("dict");
            string output;
            int count = start.length();
            vector<string> WordList;
            vector<string> FullDict;
            if (myReadFile.is_open()) {
                    while (!myReadFile.eof()) {
                            myReadFile >> output;
                            if ( output.length() == count && (output[0] - 'a') >= 0 ){ 
                                    WordList.push_back(output);
                            }
                    }

            }
            myReadFile.close();
            cout << "Building Dictionary " << endl;
            Graph LookUp = MakeGraph(WordList);
            cout << "Dictionary Built " << endl;
            NodeStatus NS = populate_node_status(LookUp);
                
            if (start.compare(last) != 0 && len1 == len2 && len1 == count) {
                    string result = breadthSearch(LookUp,NS,start,last);
                    if ( result.compare(start) == 0 )
                            cout << "Conversion Not Possible" <<endl;
                    else{
                            cout << "The Path is: " <<  endl;
                            printBFS(NS,start,last);
                    }
            }    
            else if (start.compare(last) !=0 && len1 != len2){
                    cout << "Length of the two valid words is not the same\n";
            }
            else if (start.compare(last) == 0 && len1 == len2 && len1 == count) {
                    cout << "The two input words are valid and equal\n";
            }
            else if (len1 != count || len2 != count) {
                    cout << "Both Starting and Final Words are valid and both donot match the specified length\n";

            }
    }
    else if (one == true && two == false){
            cout << "Final Word is Not a Valid Word\n";
    }
    else if (one == false && two == true) {
            cout << "Starting Word is Not a Valid Word\n";
    }
    else {
            cout << "Both Starting and Final Words are Not Valid\n";
    }

    return 0;
}



bool isValidWord(string str,vector<string> WordList) {

        vector<string>::iterator it;
        for (it = WordList.begin() ; it != WordList.end(); it++) {
                if ((*it).compare(str) == 0 )
                        return true;
        }
        return false;
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
        for ( int i = 0; i < temp.length() ; i++ ){                   
            //temp = *it;
            for ( char ch = 'a' ; ch <= 'z' ; ch++ ){
                if ( temp[i] != ch ){
                    temp[i] = ch;
                    if ( LookUp.find(temp) != LookUp.end() )
                        editDist.push_back(temp);
                    temp = *it;
                }
            }
        }
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
    
            
        
    
        
        
        





