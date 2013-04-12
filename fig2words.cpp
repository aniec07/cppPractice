#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(){

    string units[] = {"", "One ", "Two ", "Three ", "Four ", "Five ", "Six ",
                      "Seven ", "Eight ", "Nine ", "Ten ", "Eleven ", "Twelve ",
                      "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ",
                      "Seventeen ", "Eighteen ", "Nineteen "};

    string tens[] = {"", "Ten ", "Twenty ", "Thirty ", "Forty ", "Fifty ",
                     "Sixty ", "Seventy ", "Eighty ", "Ninety "};

    int denom_values[] = {10000000, 100000, 1000, 100, 1};

    map<int, string> denom_names;
    denom_names[10000000] = "Crore ";
    denom_names[100000] = "Lakh ";
    denom_names[1000] = "Thousand ";
    denom_names[100] = "Hundred ";
    denom_names[1] = "only";

    int nDenoms = 5;
    string in_words = "";
    int amount;

    cin >> amount;

    int denom, d;

    for (int i = 0; i < nDenoms; i++){
        denom = denom_values[i];
        d = amount / denom;

        if (d > 0){
            if (d < 20){
                in_words += units[d];
            }
            else{
                in_words += (tens[d / 10] + units[d % 10]);
            }
            in_words += denom_names[denom];
        }
        amount %= denom;
    }
    cout << in_words << endl;
}
