#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	ifstream FIFO;
	string Order = "";

	while (Order != "x@x@EXCHCLOSED@x@x@x") {
		FIFO.open("FIFO");

		while (FIFO >> Order)
			cout << Order << endl;

		FIFO.close();
	}
}
