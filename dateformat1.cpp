#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> tokenize(string sent);
vector<string> reverseVect(vector<string> strvect);
map<string, string> getMonthMap();
string ConvertCase(string str);



int main(){

    string dt="17 December,, 1998 ;;";
    vector<string> vdt = tokenize(dt);
    map<string, string> MonthMap = getMonthMap();
    string month_str;

    for ( int i = vdt.size() - 1 ; i >= 0 ; i-- )
        if ( i == 1 ){
           month_str = ConvertCase(vdt[i]);
           cout << MonthMap[month_str.substr(0,3)];
        }
        else
            cout << vdt[i];
    cout << endl;
}



string ConvertCase(string str){

    string::iterator it;
    string newstr;

    for ( it = str.begin() ; it < str.end() ; it++ )
        newstr.push_back(tolower(*it));

    return newstr;
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
