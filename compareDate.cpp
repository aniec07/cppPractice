#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> tokenize (string sent);
map<string, string> getMonthMap();
int ConverttoDays (string month,string days);
int ConvertStringtoInteger (string s);
int dateCompare(vector<int> d1,vector<int> d2);
vector <int> ConvertStringVectortoInteger (vector<string> s);


int main(){

    string dt1="1989 07 19";
    string dt2="1989 05 10";
    cout << "Date 1 is: " << dt1 << endl;
    cout << "Date 2 is: " << dt2 << endl;
    vector<string> vdt1 = tokenize(dt1);
    vector<string> vdt2 = tokenize(dt2);
    vector<int> nvdt1 = ConvertStringVectortoInteger ( vdt1 );
    vector<int> nvdt2 = ConvertStringVectortoInteger ( vdt2 );
    if ( dateCompare (nvdt1,nvdt2) == 1 )
        cout << "Date 1 is later than second" << endl;
    else if ( dateCompare (nvdt1,nvdt2) == 0 )
        cout << "Dates are same" << endl;
    else
        cout << "Date 1 is earlier than second" << endl;
}

int dateCompare ( vector<int> d1,vector<int> d2){
    
    if(d1[0]>d2[0])
        return 1;
    else if(d1[0]==d2[0]){
        if ( d1[1] > d2[1] )
            return 1;
        else if ( d1[1] == d2[2])
            return 0;
        else
            return -1;
    }
    else
        return -1;
}





vector<int> ConvertStringVectortoInteger(vector<string> s){
    vector<int> number;
    vector<string>::iterator it;    
    number.push_back(ConvertStringtoInteger(s[0]));
    number.push_back(ConverttoDays (s[1],s[2]));
    return number;
}


int ConvertStringtoInteger (string s){
    
    char *chararr;
    chararr = new char[s.length()];
    for ( int i=0; i <s.length() ; i++)
        chararr[i] = s[i];
    int number = atoi (chararr) ;
    return number;
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


string generatecurentdate(){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    return asctime (timeinfo);
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
