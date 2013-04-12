#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<string> tokenize(string sent);
int ConvertToDays(string month,string day);
int ConvertStringToNumber(string num);
int daysInBetween(string date1, string date2);

int main(int argc, char *argv[]){
    std::string date1 = argv[1];
    std::string date2 = argv[2];
    cout << daysInBetween(date1,date2) << endl;
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

int daysInBetween(string date1, string date2){
    vector<string> dt1 = tokenize(date1);
    vector<string> dt2 = tokenize(date2);
        
    int year1 = ConvertStringToNumber(dt1[2]);
    int year2 = ConvertStringToNumber(dt2[2]);
    
    int daydiff = 0;
    if ( year2 > year1 ){
        for ( int i = year1+1 ; i <= year2 - 1 ; i++ ){
            if ( i%4 == 0 )
                daydiff += 366;
            else
                daydiff += 365;
        }
        if ( year1%4 == 0 && ConvertStringToNumber(dt1[1]) <= 2 )
                daydiff += 366 - ConvertToDays(dt1[1],dt1[0]) + 1;
        else 
                daydiff += 365 - ConvertToDays(dt1[1],dt1[0]) + 1;

        if ( year2%4 == 0 && ConvertStringToNumber(dt2[1]) > 2 )
                daydiff += ConvertToDays(dt2[1],dt2[0]) + 2;
        else 
                daydiff += ConvertToDays(dt2[1],dt2[0]) + 1;
    }
    else if ( year1 > year2 ){ 
        for ( int i = year2+1 ; i <= year1 - 1 ; i++ ){
            if ( i%4 == 0 )
                daydiff += 366;
            else
                daydiff += 365;
        }
        if ( year2%4 == 0 && ConvertStringToNumber(dt2[1]) <= 2 )
                daydiff += 366 - ConvertToDays(dt2[1],dt2[0]) + 1;
        else 
                daydiff += 365 - ConvertToDays(dt2[1],dt2[0]) + 1;

        if ( year1%4 == 0 && ConvertStringToNumber(dt1[1]) > 2 )
                daydiff += ConvertToDays(dt1[1],dt1[0]) + 2;
        else 
                daydiff += ConvertToDays(dt1[1],dt1[0]) + 1;
    }
    else{
        int days1 = ConvertToDays(dt1[1],dt1[0]);
        int days2 = ConvertToDays(dt2[1],dt2[0]);
        if ( days1 > days2 ){
            if ( ConvertStringToNumber(dt1[1]) > 2 && ConvertStringToNumber(dt2[1]) <= 2 && ConvertStringToNumber(dt1[2])%4 == 0)
                daydiff += 1;  
            daydiff += days1 - days2 + 1;
        }
        else if (days2 > days1 ){
            if ( ConvertStringToNumber(dt2[1]) > 2 && ConvertStringToNumber(dt1[1]) <= 2 && ConvertStringToNumber(dt1[2])%4 == 0)
                daydiff += 1;  
            daydiff += days2 - days1 + 1;
        }
        else
            daydiff = 0;
    }
                
    return daydiff;
}


vector<string> tokenize(string sent){

    vector<string> word_collect;
    string::iterator it_start,it_end;
    it_start = sent.begin();
    it_end = sent.begin();
    int mark_start = 0, mark_end = 0;

    while ( it_end < sent.end() ){
        if ( *it_end=='/' ){
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






int ConvertToDays(string month,string day){

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
