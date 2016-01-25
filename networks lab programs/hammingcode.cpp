#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(void) {
	string message;
	cin >> message; // 7 bits
	message = message.substr(0, 7);
	string code("00000000000");
	//cout << code << endl;
	for(int i = 0, j = 0; i < 11; i++) {
		if(!(i == 0 || i == 1 || i == 3 || i == 7))
			code[i] = message[j++];
	}
	
	code[1-1] = '0'+(0+code[1-1]+code[3-1]+code[5-1]+code[7-1]+code[9-1]+code[11-1] - 6*'0')%2;
	code[2-1] = '0'+(0+code[2-1]+code[3-1]+code[6-1]+code[7-1]+code[10-1]+code[11-1] - 6*'0')%2;
	code[4-1] = '0'+(0+code[4-1]+code[5-1]+code[6-1]+code[7-1] - 4*'0')%2;
	code[8-1] = '0'+(0+code[8-1]+code[9-1]+code[10-1]+code[11-1] - 4*'0')%2;
	
	cout << code << endl;
	
	string tcode;
	cin >> tcode;
	tcode = tcode.substr(0, 11);
	int p1 = (0+tcode[1-1]+tcode[3-1]+tcode[5-1]+tcode[7-1]+tcode[9-1]+tcode[11-1] - 6*'0')%2;
	int p2 = (0+tcode[2-1]+tcode[3-1]+tcode[6-1]+tcode[7-1]+tcode[10-1]+tcode[11-1] - 6*'0')%2;
	int p4 = (0+tcode[4-1]+tcode[5-1]+tcode[6-1]+tcode[7-1] - 4*'0')%2;
	int p8 = (0+tcode[8-1]+tcode[9-1]+tcode[10-1]+tcode[11-1] - 4*'0')%2;
	int ans = p1*1 + p2*2 + p4*4 + p8*8;
	if(ans == 0)
		cout << "No error" << endl;
	else
		cout << "bit " << ans << " was changed." << endl;
	
	return 0;
}
