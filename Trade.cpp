#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

typedef struct{
        
        string ID;
        string type;
        string name;
        float rate;
        int num;
        string expiry;
        string date;
}Scrip;

typedef list<Scrip> ScripList;
typedef map<string,ScripList> TradeList;



void checkExpiry (TradeList &, TradeList & );
void doTransaction (TradeList &, TradeList & );
void populateList (TradeList &, TradeList &, string req);
string Current_Time(time_t *Current_Time_time_t);
vector<string> tokenize(string sent, char sep);
string tostring(int i);
int ConvertStringToNumber(string num);
bool isAlive(string, string);
int ConvertTimeToSeconds(string);

int main(){
    time_t CT;
    time(&CT);
    cout << Current_Time(&CT) << endl;
}

int ConvertTimeToSeconds(string s){
    vector<string> ts = tokenize(s,':');
    int sec = 0;
    sec = (ConvertStringToNumber(ts[0]))*60*60 + (ConvertStringToNumber(ts[1]))*60 + ConvertStringToNumber(ts[2]);
    return sec;
}

bool isAlive(string ptime, string ctime){
    if ( ConvertTimeToSeconds(ptime) > ConvertTimeToSeconds(ctime) )
        return true;
    else 
        return false;
}



string Current_Time(time_t *Current_Time_time_t) {
	struct tm *Current_Time_tm;
    
	string tmp_hour;
	string tmp_min;
	string tmp_sec;
	string tmp_Time;

	Current_Time_tm = localtime(Current_Time_time_t);

	mktime(Current_Time_tm);

	tmp_hour = tostring(Current_Time_tm->tm_hour);
	tmp_min = tostring(Current_Time_tm->tm_min);
	tmp_sec = tostring(Current_Time_tm->tm_sec);
	tmp_Time = tmp_hour + ":" + tmp_min + ":" + tmp_sec;

	return tmp_Time;
}


// Converts int to string

string tostring(int i) {
	stringstream converter_stream;
	string converted_string;

	converter_stream << i;
	converter_stream >> converted_string;

	return converted_string;
}


int ConvertStringToNumber(string num){
    char *chararr1;
    int pos = 0;
    chararr1 = new char[num.length()];
    for ( int i = 0; i < num.length() ; i++){
        if(num[i]!='.'){
        chararr1[pos] = num[i];
        pos++;
        }
    }
    int number = atoi (chararr1);
    return number;
}   


void populateList (TradeList &BuyListAll, TradeList &SellListAll, string req){
    vector<string> tokenized_string = tokenize (req,'@');
    
    string Transaction_Type = tokenized_string[1];
        Scrip s;
        s.ID = tokenized_string[0];
        s.type = tokenized_string[1];
        s.name = tokenized_string[2]; 
        s.rate = ConvertStringToNumber(tokenized_string[3]);
        s.num = ConvertStringToNumber(tokenized_string[4]);
        vector<string> expiryTime = tokenize(tokenized_string[5],'$');
        s.expiry = expiryTime[1];
        s.date = expiryTime[0];
    
    if ( (s.type).compare("B") == 0 )
        ((BuyListAll.find(s.type))->second).push_back(s);
    else
        ((SellListAll.find(s.type))->second).push_back(s);
        
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

void checkExpiry ( TradeList &BuyListAll, TradeList &SellListAll ){
    
    TradeList::iterator buy,sell;
    ScripList::iterator b1,s1;
    ScripList blist, slist;
    
    time_t CT;
    time(&CT);
    string CurrentTime = Current_Time(&CT);
    
    for ( sell = SellListAll.begin() ; sell != SellListAll.end() ; sell++ ){
        slist = sell->second;
        for ( s1 = slist.begin(); s1 != slist.end() ; s1++ ){
            if ( !isAlive ( (*s1).expiry, CurrentTime ) )
                (sell->second).erase(s1);
        }
    }
     

    for ( buy = BuyListAll.begin() ; buy != BuyListAll.end() ; buy++ ){
        blist = buy->second;
        for ( b1 = blist.begin(); b1 != blist.end() ; b1++ ){
            if ( !isAlive ( (*b1).expiry, CurrentTime ) )
                (buy->second).erase(b1);
        }
    }

}

void doTransaction ( TradeList &BuyListAll, TradeList &SellListAll ){

    TradeList::iterator buy,sell;
    bool tradeflag = true;
    
    for ( sell = SellListAll.begin() ; sell != SellListAll.end() ; sell++ ){
        buy = BuyListAll.find(sell->first);

        if ( buy != BuyListAll.end() ){ // there is a buyer

            ScripList blist = buy->second;
            ScripList slist = sell->second;
            ScripList::iterator b1,s1;
            s1 = slist.begin();//check the first sale item

                for ( b1 = blist.begin(); b1 != blist.end() && tradeflag ; b1++ ){//check the buyer list entirely
                    if ( (*b1).rate > (*s1).rate ){

                        if ( (*b1).num >= (*s1).num ){//all sold
                            // *************print to file*************** //
                            (*b1).num -= (*s1).num;
                            (sell->second).erase(s1);
                            if ( (*b1).num == 0 )
                                (buy->second).erase(b1);
                            tradeflag = false;
                            }
                        if ( (*b1).num < (*s1).num ){//partially sold
                            // *************print to file*************** //
                            (*s1).num -= (*b1).num;
                            (buy->second).erase(b1);
                        }
                    }
                }
                
        }
    }
}
        
                            
            
            
        
