// djikstra's algorithm

#include <iostream>
#include <climits>
#include <fstream>
#include <cstring>


using namespace std;

int next(unsigned int * dist, bool * v, int n) {
	int nx = -1;
	unsigned int m = 100;
	for(int i = 1; i <= n; i++)
		if(m > dist[i] && !v[i]) {
			m = dist[i];
			nx = i;
		}
	return nx;
}

void route(int * pen, int i, int src) {
	if(i == -1) return;
	if(i == src) {
		cout << i;
		return;
	}
	route(pen, pen[i], src);
	cout << " ---> " << i;
}


int main(void) {
	int n;
	int a[100][100];
	int src;
	
	ifstream fin("input");
	cout << "Enter number of vertices" << endl;
	fin >> n;
	cout << "Enter adjacency cost matrix" << endl;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			fin >> a[i][j];
		}
	}
	
	cout << "Enter source" << endl;
	fin >> src;
	
	unsigned int dist[100]; memset(dist, -1, sizeof(dist));
	int pen[100]; memset(pen, -1, sizeof(pen));
	bool visited[100] = {0};
	
	//cout << dist[0] << endl; return 0;
	
	dist[src] = 0;
	int temp = src;
	while(temp != -1) {
		visited[temp] = true;
		for(int i = 1; i <= n; i++) {
			if(i != temp && dist[i] > dist[temp] + a[temp][i]) {
				pen[i] = temp;
				dist[i] = dist[temp] + a[temp][i];
			}
		}
		temp = next(dist, visited, n);
	}
	
	// print routes:
	for(int i = 1; i <= n; i++) {
		if(dist[i] >= 100)
			cout << "Infinite distance. no route\n" << endl;
		else {
			route(pen, i, src);
			cout << endl;
		}
	}
	
	fin.close();
	return 0;
}	
