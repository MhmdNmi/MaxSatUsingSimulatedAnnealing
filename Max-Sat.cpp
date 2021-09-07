#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>

using namespace std;

double T = 10;
int n, m;
int** clauses;
int* variables;

int evaluation(int* variables) {
	int x = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (clauses[i][j] == 0) break;
			else if (clauses[i][j] < 0) {
				if (variables[(-clauses[i][j]) - 1] == 0) {
					x++;
					break;
				}
			}
			else if (variables[clauses[i][j] - 1] == 1) {
				x++;
				break;
			}
		}
	}
	return x;
}

int* makeState() {
	int* next = new int[n];
	for (int i = 0; i < n; i++) {
		double x = ((double)rand() / (RAND_MAX + 1));
		if (x >= 0.5) next[i] = 1;
		else next[i] = 0;
	}
	return next;
}

int main() {
	srand(time(0));
	cin >> n >> m;
	clauses = new int* [m];
	for (int i = 0; i < m; i++) {
		clauses[i] = new int[n];
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> clauses[i][j];
			if (clauses[i][j] == 0) break;
		}
	}
	//Start State
	variables = makeState();
	int C = evaluation(variables);
	//simulated annealing
	int* next;
	while (T > 0.000000000000001) {
		next = makeState();
		int Ct = evaluation(next);
		if (Ct > C) {
			free(variables);
			variables = next;
			C = Ct;
		}
		else {
			double r = ((double)rand() / (RAND_MAX + 1));
			double p = pow(exp(1.0), ((double)(C - Ct) / T));
			if (r > p) {
				free(variables);
				variables = next;
				C = Ct;
			}
			else free(next);
		}
		if (C == m) break;
		T *= 0.99;
	}
	cout << C << endl;
	for (int i = 0; i < n; i++) cout << variables[i];
	return 0;
}
