#include <iostream>
#include <cmath>

using namespace std;

int power(int a, int e, int mod) {
	if(e == 0) return 1;
	int temp = power(a, e/2, mod);
	temp = (temp*temp)%mod;
	if(e%2)
		return (temp*a)%mod;
	return temp;
}

int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b, a%b);
}

void egcd(int a, int &x, int b, int &y) {
	if(b == 0) {
		x = 1;
		y = 0;
		return;
	}
	egcd(b, x, a%b, y);
	int tempx = y;
	int tempy = x - (a/b)*y;
	x = tempx; y = tempy;
}

int mmi(int a, int mod) {
	int x, y;
	egcd(a, x, mod, y);
	return x;
}

int main(void) {
	int p, q;
	cin >> p >> q;
	int n = p*q;
	int phi = (p-1)*(q-1); // if p == q then do phi = p^2 - p
	// find e such that gcd(e and phi) is 1;
	int e, d;
	for(e = phi-2; e >= 1; e--) {
		if(gcd(e, phi) == 1) {
			d = mmi(e, phi);
			break;
		}
	}
	cout << "public key: {" << e << ", " << n << "}" << endl;
	cout << "private key: {" << d << ", " << n << "}" << endl;
	cout << "Enter your message: " << endl;
	string message;
	cin >> message;
	for(size_t i = 0; i < message.size(); i++) {
		int temp = power(message[i], e, n);
		cout << "E('" << message[i] << "') = " << temp;
		cout << "\tD(" << temp << ") = " << char(power(temp, d, n)) << endl;
	}
	return 0;
}
