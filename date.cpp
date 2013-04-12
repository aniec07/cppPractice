#include <iostream>
#include <map>

using namespace std;

string remove_commas(string str);
string extract_word_after_index(string str, int *index);
map<string, string>  getMonthMap();

int main() {
    string str_input = "I am, kio";
    str_input = remove_commas(str_input);

    int index = 0;
    string reverse_str = "";
    while(index < str_input.length()) {
        reverse_str = extract_word_after_index(str_input, &index) + " " + reverse_str;
    }
    map<string, string> monthMap = getMonthMap();
    string month = reverse_str.substr(4, reverse_str.length() - 6);
    string str = reverse_str.substr(0, 4);
    str += monthMap[month];
    str += reverse_str.substr(reverse_str.length() - 2, 2);
    cout << "Commas removed = " << str << endl;
}

string remove_commas(string str) {
    int index = 0;
    string str1;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == ',') {
            str1 = str.substr(0, i);
            str1 += str.substr(i + 1, str.length() - i - 1);
            str = str1;
            i--;
        }
    }
    return str;
}

string extract_word_after_index(string str, int *index) {
    int inWord = 0, start, end;
    int i, length = str.length();
    string str1;
    for (i = *index; i < length; i++) {
        if (inWord == 0 && (str.at(i) != ' ' && str.at(i) != '\t')) {
            inWord = 1;
            start = i;
        } else if (inWord == 1 && (str.at(i) == ' ' || str.at(i) == '\t')) {
            str1 = str.substr(start, i - start);
            *index = i;
            break;
        }
    }
    if(i == length) {
        if(str.at(i - 1) != ' ' && str.at(i - 1) != '\t') {
            str1 = str.substr(start, i - start);
            *index = i;
        }
    }
    return str1;
 }

map<string, string>  getMonthMap() {
    map<string, string> monthMap;
    monthMap["Jan"] = "01";
    monthMap["Feb"] = "02";
    monthMap["Mar"] = "03";
    monthMap["Apr"] = "04";
    monthMap["May"] = "05";
    monthMap["Jun"] = "06";
    monthMap["Jul"] = "07";
    monthMap["Aug"] = "08";
    monthMap["Sep"] = "09";
    monthMap["Oct"] = "10";
    monthMap["Nov"] = "11";
    monthMap["Dec"] = "12";
    return monthMap;
}

