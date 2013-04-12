#include <string>
#include <iostream>
#include <vector>

using namespace std;

string reverse_Word(string word);
vector<string> breaksentence(string sent);
string makesentence(vector<string> word);


int  main(){
    string str="Anirban is coding here okay";
    cout<< makesentence(breaksentence(str)) << endl;
}


string reverse_Word(string word){
    string revWord;
    string::iterator it;
    for ( it=word.end()-1; it>=word.begin(); it--)
        revWord.push_back(*it);
    return revWord;
}


vector<string> breaksentence(string sent){

    vector<string> word_collect;
    string::iterator it_start,it_end;
    it_start=sent.begin();
    it_end=sent.begin();
    int mark_start=0,mark_end=0;

    while(it_end<sent.end()){
        if(*it_end==' '||*it_end==','||*it_end==';'||*it_end=='\t'){
            word_collect.push_back(sent.substr(mark_start,mark_end-mark_start));
            it_start=it_end+1;
            mark_start=mark_end+1;
            word_collect.push_back(sent.substr(mark_end,1));
        }
        it_end++;
        mark_end++;
    }

    return word_collect;
}

string makesentence(vector<string> word){
    
    string newstring;
    vector<string>::iterator it;
    for ( it=word.begin(); it<word.end(); it++)
        newstring.append(reverse_Word(*it));
    return newstring;
}

        
    
