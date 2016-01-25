#include <iostream>
#include <string>
#include <cmath>

#define append "0000000000000000"

using namespace std;

void exor(string &tmsg, string & g, size_t i) {
	if(tmsg[i] == '0') return;
	for(size_t j = 0; j < g.size(); j++) {
		tmsg[i+j] = '0' + ((tmsg[i+j] - '0') ^ (g[j] - '0'));
	}
}

void divide(string& tmsg, string & gx, string & chksum) {
	for(size_t i = 0; i < gx.size()-1; i++) {
		exor(tmsg, gx, i);
	}
	chksum = tmsg.substr(tmsg.size() - gx.size());
}

int main(void) {
	string message, gx = "1101101011010111";
	cin >> message;
	string tmsg = message+append;
	cout << tmsg << endl;
	string chksum = append;
	divide(tmsg, gx, chksum);
	tmsg = message+chksum;
	cout << "generated crc code: " << tmsg << endl;
	cin >> tmsg;
	divide(tmsg, gx, chksum);
	size_t i;
	for(i = 0; i < chksum.size(); i++) {
		if(chksum[i] != '0') break;
	}
	if(i == chksum.size())
		cout << "no error" << endl;
	else
		cout << "error" << endl;
	return 0;
}
