#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> tokenize(string sent);
vector<string> reverseVect(vector<string> strvect);
map<string, string> getMonthMap();
int ConverttoDays(string month,string days);



int main(){

    string dt="1998   05 15 ;;";
    cout<<dt<<endl;
    vector<string> vdt = tokenize(dt);
    map<string, string> MonthMap = getMonthMap();
    int month_str;

    cout<<vdt[0];
    month_str = ConverttoDays(vdt[1],vdt[2]);
    cout<<month_str;
    cout << endl;
}



int ConverttoDays(string month,string day){

    int monthdays[]={31,28,31,30,31,30,31,31,30,31,30,31};
    char *chararr;
    chararr = new char[month.length()];
    for ( int i=0; i <month.length() ; i++)
        chararr[i] = month[i] ;
    char *chararr2;
    chararr2 = new char[day.length()];
    for ( int i = 0; i < day.length() ; i++)
        chararr2[i] = day[i];
    int month_number = atoi (chararr) ;
    int numday = atoi(chararr2);
    for(int i = 0 ; i < month_number - 1 ; i++)
        numday += monthdays[i];
    return numday;
    
}


vector<string> tokenize(string sent){

    vector<string> word_collect;
    string::iterator it_start,it_end;
    it_start = sent.begin();
    it_end = sent.begin();
    int mark_start = 0, mark_end = 0;

    while ( it_end < sent.end() ){
        if ( *it_end==' ' || *it_end==',' || *it_end==';' || *it_end=='\t'){
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


map<string, string>  getMonthMap() {
    map<string, string> monthMap;
    monthMap["jan"] = "01";
    monthMap["feb"] = "02";
    monthMap["mar"] = "03";
    monthMap["apr"] = "04";
    monthMap["may"] = "05";
    monthMap["jun"] = "06";
    monthMap["jul"] = "07";
    monthMap["aug"] = "08";
    monthMap["sep"] = "09";
    monthMap["oct"] = "10";
    monthMap["nov"] = "11";
    monthMap["dec"] = "12";
    return monthMap;
}
