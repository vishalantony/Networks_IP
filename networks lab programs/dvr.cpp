#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

struct rtable {
	int dist[100];
	int next[100];
};

int a[100][100];
rtable router[100];
int n;

void dvr(void) {
	int count;
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			router[i].dist[j] = a[i][j];
			router[i].next[j] = j;
		}
	}
	
	do {
		count = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				for(int k = 0; k < n; k++) {
					if(router[i].dist[j] > a[i][k]+router[k].dist[j]) {
						router[i].dist[j] = a[i][k]+router[k].dist[j];
						router[i].next[j] = k;
					}
				}
			}
		}
	}while(count != 0);
}

int main(void) {
	ifstream fin("input");
	fin >> n;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			fin >> a[i][j];
	dvr();
	for(int i = 0; i < n; i++) {
		cout << "\nFor " << i << endl;
		cout << "node | distance | next\n----------------------" << endl;
		for(int j = 0; j < n; j++)
			cout << j << "\t|" << router[i].dist[j] << "\t|" << router[i].next[j] << endl;
	}
	return 0;
}
