#include <iostream>
#include <>

using namespace std;

typedef map<string,list<string> > flowchart;
typedef map<string,Level> Position_Detail;

void insertInChart (string, string, flowchart &);
//void deleteInChart (string, flowchart &);
string findtop (flowchart Chart);

int main{
}

void insertInChart (string superior, string reportee, flowchart &Chart){
        if ( Chart.find(superior) != Chart.end() ) // means alredy the superior exists;
                (Chart.find(superior))->second.push_back(reportee);
        else{
                list<string> repList;
                repList.push_back(reportee);
                Chart[superior] = repList;
            }
}

/*void deleteFromChart (string designation, flowchart &Chart){
        if ( Chart.find(designation) != Chart.end() ){ //implies designation is someone's superior
            list<string> repList1 = Chart.find(designation); // captures the reportees 
            flowchart::iterator it;
            bool notfound = true;
                for ( it = Chart.begin() ; it != Char.end() && notfound ; it++ ){   
                        list<string> repListTemp = (*it).second;
                        list<string>::iterator itlist;
                        for ( itlist = repListTemp.begin() ; itlist != repListTemp.end() && notfound ; itlist++ )
                                if ( (*itlist).compare(designation) == 0)
                                     notfound = true;
                }
            if ( it != Char.end() ){ //implies the designation was someone's reportee

                    (*it).
                    
*/

string findtop (flowchart Chart){
            //find top most
            flowchart::iterator it1,it2;
            bool notfound = true;
            bool topfound = false;
            for ( it1 = Chart.begin() ; it1 != Chart.end() && !topfound ; it1++){
                for ( it2 = Chart.begin() ; it2 != Chart.end() && notfound; it2++ ){
                        list<string> temp = (*it2).second;
                        list<string>::iterator lt = temp.find (temp.begin(),temp.end(),(*it1).first);
                        if ( lt != temp.end() )
                            notfound = false;
                }
                if(notfound)
                    topfound = true;
            }
            int level = 0, count = 1;
            cout << (*it1).first << endl;
            string start = (*it).first;
            return start;
}

void PrintChart (flowchart Chart){
            string top = findtop(Chart);




void PrintChart ( flowchart Chart, NodeStatus node_table ){
        string start = findtop(Chart);
        queue<string> breadth;
        breadth.push(start);
        (node_table.find(start))->second.visited = true;
        list<string> editDist;
        list<string>::iterator it;
        while ( breadth.size() > 0 ){

                editDist = (Chart.find(breadth.front()))->second;
    
                for ( it = editDist.begin() ; it != editDist.end() && !found ; it++ ){
                    if ( (node_table.find(*it))->second.visited == false ){
                        (node_table.find(*it))->second.visited = true;
                        (node_table.find(*it))->second.parent = breadth.front();
                        breadth.push(*it);
                        cout << (*it) << " ";
                     }
                }
                cout << endl;
                breadth.pop();
                    
        }
}   
                        
                        
        



