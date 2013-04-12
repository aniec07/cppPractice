#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;

// Constants

const int ScripA_Selection_Probability_percent = 80;

const int ScripA_Swing_Seed_bps = 5;
const int ScripB_Swing_Seed_bps = 15;

const int Qty_Seed = 10;
const int Lot_Unit = 100;

const int Exp_Date_Seed_sec = 100;
const int Sleep_Seed_sec = 5;
const int Starting_Delay_sec = 30;
 
// Typedefs

typedef struct {
		string Ticker;
		char Category;
		float Market_Rate;
		} Scrip;

typedef vector<Scrip> Scrip_Table;

// Function Prototypes

void Populate_Scrips(Scrip_Table *);
void Insert_Scrip(Scrip_Table *, string, char, float);
int Count_Scrips(Scrip_Table, char);
int Randomize_Customer();
char Randomize_Transaction();
Scrip Randomize_Scrip(Scrip_Table, int, int);
float Randomize_Bid(Scrip);
int Randomize_Qty();
string Randomize_Exp_Date(time_t, int);
bool End_Block_Now();
string Future_Time(time_t *, int);
int intrand(int);
string zeropad(int, int);
string tostring(int);

// Main Function

int main(int argc, char *argv[]) {
	Scrip_Table Scrips;
	Scrip Selected_Scrip;

	int Number_Of_Trades;
	int ScripA_Count;
	int ScripB_Count;

	int Sleep_Delay;
	int Total_Sleep_Delay = 0;
	time_t Program_Start_Time; 

	string Delimiter = "@";

	ofstream FIFO;

	if (argc == 2)
		Number_Of_Trades = atoi(argv[1]);	
	else {
		cout << "Usage Stocks_Test_Data rec_count" << endl;
		exit(false);
	}

	Populate_Scrips(&Scrips);

	ScripA_Count = Count_Scrips(Scrips, 'A');
	ScripB_Count = Count_Scrips(Scrips, 'B');

	time(&Program_Start_Time);

	sleep(Starting_Delay_sec);
	Total_Sleep_Delay += Starting_Delay_sec;

	FIFO.open("FIFO");

	for (int i = 1; i <= Number_Of_Trades; i++)
	{
		FIFO << "IN" << zeropad(Randomize_Customer(), 9) << Delimiter;
		FIFO << Randomize_Transaction() << Delimiter;
		Selected_Scrip = Randomize_Scrip(Scrips, ScripA_Count, ScripB_Count);
		FIFO << Selected_Scrip.Ticker << Delimiter;
		FIFO << setiosflags(ios::fixed) << setprecision(2) << Randomize_Bid(Selected_Scrip) << Delimiter;
		FIFO << Randomize_Qty() << Delimiter;
		FIFO << Randomize_Exp_Date(Program_Start_Time, Total_Sleep_Delay) << endl;

		if (End_Block_Now() && i < Number_Of_Trades) {
			Sleep_Delay = 1 + intrand(Sleep_Seed_sec);
			Total_Sleep_Delay += Sleep_Delay;

			FIFO.close();

			sleep(Sleep_Delay);

			FIFO.open("FIFO");
		}
	}

	FIFO.close();

	sleep(5);

	FIFO.open("FIFO");

	FIFO << "x@x@EXCHCLOSED@x@x@x" << endl;

	FIFO.close();
}

// Populates the Scrip Table with a number of Scrips

void Populate_Scrips(Scrip_Table *Scrips) {
	Insert_Scrip(Scrips, "INFY", 'A', 2475.10);
	Insert_Scrip(Scrips, "SBI", 'A', 2156.75);
	Insert_Scrip(Scrips, "RCOM", 'A', 62.60);
	Insert_Scrip(Scrips, "ALEMBICLTD", 'B', 15.75);
	Insert_Scrip(Scrips, "BLUESTAR", 'B', 165.90);
	Insert_Scrip(Scrips, "CANFINHOME", 'B', 104.00 );
	Insert_Scrip(Scrips, "DLINKIND", 'B', 22.00);
	Insert_Scrip(Scrips, "EIDPARRY", 'B', 172.75);
	Insert_Scrip(Scrips, "GATI", 'B', 35.65);
	Insert_Scrip(Scrips, "HCLINFO", 'B', 41.50);
	Insert_Scrip(Scrips, "JKCEM", 'B', 147.00);
	Insert_Scrip(Scrips, "KAMATHOQ", 'B', 128.00);
	Insert_Scrip(Scrips, "MOSERBAER", 'B', 8.91);
	Insert_Scrip(Scrips, "NIIT", 'B', 41.75);
	Insert_Scrip(Scrips, "POLARIS", 'B', 122.25);
	Insert_Scrip(Scrips, "SAHARA", 'B', 133.95);
	Insert_Scrip(Scrips, "TIMEX", 'B', 24.20);
	Insert_Scrip(Scrips, "WOMENNET", 'B', 7.75);
}

// Used to iniliatize the Scrips table with appropriate values

void Insert_Scrip(Scrip_Table *Scrips, string Ticker, char Category, float Market_Rate) {
	Scrip temp;

	temp.Ticker = Ticker;
	temp.Category = Category;
	temp.Market_Rate = Market_Rate;

	Scrips->push_back(temp);
}

// Counts Number of Scrips by Category

int Count_Scrips(Scrip_Table Scrips, char Category) {
	Scrip_Table::iterator Scrips_it;
	int Category_Count = 0;	

	for (Scrips_it = Scrips.begin(); Scrips_it != Scrips.end(); Scrips_it++)
		if (Scrips_it->Category == Category)
			Category_Count++;

	return Category_Count;
}

// Generate Random Custmer Code

int Randomize_Customer() {
	return intrand(999999999) + 1;
}

// Generate Random Transaction Code 'B' Buy 'S' Sell

char Randomize_Transaction() {
	if (intrand(2))
		return 'S';
	else
		return 'B';
}

// Selects a Random Scrip using ScripA_Selection_Probability

Scrip Randomize_Scrip(Scrip_Table Scrips, int ScripA_Count, int ScripB_Count) {
	char Selected_Category;
	int Selected_Count;
	int Selected_Index;
	Scrip_Table::iterator Scrips_it;
	int i = 0;
	Scrip Selected_Scrip;	

	if (intrand(100) < ScripA_Selection_Probability_percent) {
		Selected_Category = 'A';
		Selected_Count = ScripA_Count;
	}
	else {
		Selected_Category = 'B';
		Selected_Count = ScripB_Count;
	}

	Selected_Index = intrand(Selected_Count);
	
	for (Scrips_it = Scrips.begin(); Scrips_it != Scrips.end(); Scrips_it++)
	{
		if (Scrips_it->Category == Selected_Category)
		{ 
			if (i == Selected_Index)
				return *Scrips_it;
			i++;
		}
	}
}

// Generates a Random Bid for the Selected Scrip

float Randomize_Bid(Scrip Selected_Scrip) {
	char Selected_Category;
	int Selected_Swing_Seed_bps;
	float Scrip_Change_percent;
	float Scrip_Multiplier;

	if (Selected_Scrip.Category == 'A')
		Selected_Swing_Seed_bps = ScripA_Swing_Seed_bps;
	else
		Selected_Swing_Seed_bps = ScripB_Swing_Seed_bps;
		
	Scrip_Change_percent = intrand(100 * Selected_Swing_Seed_bps) / 10000.0;
	
	if (intrand(2))
		Scrip_Multiplier = 1 + (Scrip_Change_percent / 100.0);
	else 
		Scrip_Multiplier = 1 - (Scrip_Change_percent / 100.0);

	return Selected_Scrip.Market_Rate * Scrip_Multiplier;
}

// Generates a Random Bid Quantity

int Randomize_Qty() {
	return Lot_Unit * (1 + intrand(Qty_Seed));
}

// Generates a Random Future Expiry Date and Time

string Randomize_Exp_Date(time_t Program_Start_Time, int Total_Sleep_Delay) {
	return Future_Time(&Program_Start_Time, Total_Sleep_Delay + intrand(Exp_Date_Seed_sec));
}

// Add time specified and return a future time as a ctime() string

string Future_Time(time_t *Current_Time_time_t, int Delay_secs) {
	struct tm *Current_Time_tm;

	string tmp_mday;
	string tmp_mon;
	string tmp_year;
	string tmp_Date;

	string tmp_hour;
	string tmp_min;
	string tmp_sec;
	string tmp_Time;

	Current_Time_tm = localtime(Current_Time_time_t);
	Current_Time_tm->tm_sec += Delay_secs;

	mktime(Current_Time_tm);

	tmp_mday = tostring(Current_Time_tm->tm_mday);
	tmp_mon = tostring(Current_Time_tm->tm_mon + 1);
	tmp_year = tostring(Current_Time_tm->tm_year + 1900);
	tmp_Date = tmp_mday + "/" + tmp_mon + "/" + tmp_year;

	tmp_hour = tostring(Current_Time_tm->tm_hour);
	tmp_min = tostring(Current_Time_tm->tm_min);
	tmp_sec = tostring(Current_Time_tm->tm_sec);
	tmp_Time = tmp_hour + ":" + tmp_min + ":" + tmp_sec;

	return tmp_Date + "$" + tmp_Time;
}

// Determines whether we end this block of trades or not

bool End_Block_Now() {
	if ((5 - intrand(9)) > 0)
		return true;
	else
		return false;
}

// Generates a random number with a finite seed

int intrand(int n) {
	return rand() % n;
}

// Pads number with leading zeroes

string zeropad(int Number, int Digits) {
	char Number_String[256];
	int Number_Of_Digits;
	char Padded_Number[256] = "";

	Number_Of_Digits = sprintf(Number_String, "%d", Number);

	for (int i = 0; i < Digits - Number_Of_Digits; i++)
		strcat(Padded_Number, "0");

	strcat(Padded_Number, Number_String);

	return (string) Padded_Number;
}

// Converts int to string

string tostring(int i) {
	stringstream converter_stream;
	string converted_string;

	converter_stream << i;
	converter_stream >> converted_string;

	return converted_string;
}
