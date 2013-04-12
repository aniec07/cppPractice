#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct{
    int start;
    int finish;
}duration;

int convertTimeToMinutes(string time);
vector<string> tokenize(string sent, char sep);
int ConvertStringToNumber(string num);
bool isOverlap(duration d1, duration d2);
bool isfindcolon(string str);
bool isAppointmentOverlap(vector<string> applist);
    
int main(){
    vector<string> applist;
    cout<<"Enter the appointments: " << endl;   
    std::string s;
    getline( std::cin, s, '\n' );
    applist.push_back(s);
    while ( s.compare("0") != 0 ){
        getline( std::cin, s, '\n' );
        applist.push_back(s);
     }
    if (isAppointmentOverlap(applist))
        cout << "Appointments Overlap" << endl;
    else
        cout << "Appointments Do Not Overlap" << endl;    
    
}


bool isOverlap(duration d1, duration d2){
    if( (d1.start > d2.start && d1.start < d2.start ) || (d1.finish < d2.finish && d1.finish > d2.start) )
        return true;
    else
        return false;
}

bool isfindcolon(string str){
    for ( int i = 0; i< str.length(); i++ )
        if ( str[i] == ':' )
            return true;
    return false;
}

bool isAppointmentOverlap(vector<string> applist){
    for ( int i = 0 ; i< (int)applist.size() ; i++ )
        for ( int j = i+1 ; j< (int)applist.size() - 1; j++ ){
                duration d1;  
                vector<string> app1 = tokenize(applist[i],' ');
                d1.start = convertTimeToMinutes (app1[0]);
                if ( isfindcolon(app1[1]) )
                    d1.finish = convertTimeToMinutes (app1[1]);
                else
                    d1.finish = d1.start + ConvertStringToNumber (app1[1]);

                duration d2;  
                vector<string> app2 = tokenize(applist[j],' ');
                d2.start = convertTimeToMinutes (app2[0]);
                if ( isfindcolon(app2[1]) )
                    d2.finish = convertTimeToMinutes (app2[1]);
                else
                    d2.finish = d2.start + ConvertStringToNumber (app2[1]);
        
                if(isOverlap(d1,d2))
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

vector<string> tokenize(string sent, char sep){

    vector<string> word_collect;
    string::iterator it_start,it_end;
    it_start = sent.begin();
    it_end = sent.begin();
    int mark_start = 0, mark_end = 0;

    while ( it_end < sent.end() ){
        if ( *it_end == sep ){
            if ( mark_start != mark_end )
            word_collect.push_back(sent.substr(mark_start,mark_end-mark_start));
            it_start = it_end+1;
            mark_start = mark_end+1;
        }
        it_end++;
        mark_end++;
    }
    if ( mark_start != mark_end )
        word_collect.push_back(sent.substr(mark_start,mark_end-mark_start));

    return word_collect;
}



int convertTimeToMinutes(string tm){
    vector<string> t = tokenize(tm,':');
    return ( (ConvertStringToNumber(t[0]))*60 + ConvertStringToNumber(t[1]) );
}
