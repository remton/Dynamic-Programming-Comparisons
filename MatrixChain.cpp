#include "MatrixChain.h"
#include <iostream>
#include <limits.h>
using namespace std;


int Matrix_Chain_Recursive_Aux(vector<int> p, vector<vector<int>>& m, vector<vector<int>>& s, int i, int j){
	if (i == j) {
		m[i][j] = 0;
		s[i][j] = i;
		return 0;
	}
	int min_m = INT_MAX;
	int min_s = INT_MAX;
	for (int k = i; k < j; k++) {\
		//cout << "i=" << i << " k=" << k << " j=" << j << endl; // DEBUG
		int curr_m = Matrix_Chain_Recursive_Aux(p, m, s, i, k) + Matrix_Chain_Recursive_Aux(p, m, s, k + 1, j) + p[i - 1] * p[k] * p[j];
		if (curr_m < min_m) {
			min_m = curr_m;
			min_s = k;
		}
	}
	m[i][j] = min_m;
	s[i][j] = min_s;
	return min_m;
}
void Matrix_Chain_Recursive(vector<int> p, vector<vector<int>>& m, vector<vector<int>>& s) {
	int n = p.size();
	m.clear();
	s.clear();
	for (int x = 0; x < n; x++) {
		vector<int> vec;
		for (int y = 0; y < n; y++) {
			vec.push_back(0);
		}
		m.push_back(vec);
		s.push_back(vec);
	}
	Matrix_Chain_Recursive_Aux(p, m, s, 1, n - 1);
}



int Matrix_Chain_Memoized_Aux(vector<int> p, vector<vector<int>>& m, vector<vector<int>>& s, int i, int j) {
	if (i == j) {
		m[i][j] = 0;
		s[i][j] = i;
		return 0;
	}

	// MEMOIZED!!
	// If we have already computed this matrix chain we don't need to do it again
	if (m[i][j] != 0) {
		return m[i][j];
	}

	int min_m = INT_MAX;
	int min_s = INT_MAX;
	for (int k = i; k < j; k++) {
		//cout << "i=" << i << " k=" << k << " j=" << j << endl; // DEBUG
		int curr_m = Matrix_Chain_Memoized_Aux(p, m, s, i, k) + Matrix_Chain_Memoized_Aux(p, m, s, k + 1, j) + p[i - 1] * p[k] * p[j];
		if (curr_m < min_m) {
			min_m = curr_m;
			min_s = k;
		}
	}
	m[i][j] = min_m;
	s[i][j] = min_s;
	return min_m;
}
void Matrix_Chain_Memoized(vector<int> p, vector<vector<int>>& m, vector<vector<int>>& s) {
	int n = p.size();
	m.clear();
	s.clear();
	for (int x = 0; x < n; x++) {
		vector<int> vec;
		for (int y = 0; y < n; y++) {
			vec.push_back(0);
		}
		m.push_back(vec);
		s.push_back(vec);
	}
	Matrix_Chain_Memoized_Aux(p, m, s, 1, n - 1);
}


// Code taken from psudocode in the textbook: 
// Introduction to Algorithms, Third Edition page 375
void Matrix_Chain_Bottom_Up(vector<int> p, vector<vector<int>>& m, vector<vector<int>>& s) {
	int n = p.size();

	m.clear();
	s.clear();
	for (int x = 0; x < n; x++) {
		vector<int> vec;
		for (int y = 0; y < n; y++) {
			vec.push_back(0);
		}
		m.push_back(vec);
		s.push_back(vec);
	}

	for (int l = 2; l < n; l++) {
		for (int i = 1; i < n - l + 1; i++) {
			int j = i + l - 1;
			m[i][j] = INT_MAX;
			for (int k = i; k < j; k++) {
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}