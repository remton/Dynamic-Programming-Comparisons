#include"Testing.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include "MatrixChain.h"


MatrixChainResult TimeMatrixChain(void(*func)(vector<int> p, vector<vector<int>>& m, vector<vector<int>>& s), vector<int> p) {
	MatrixChainResult result;
	vector<vector<int>> m;
	vector<vector<int>> s;
	auto start = chrono::steady_clock::now();
	func(p, m, s);
	auto end = chrono::steady_clock::now();
	result.nanoseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
	result.m = m;
	result.s = s;
	return result;
}

string PrintParenthesis(MatrixChainResult result) {
	return "()";
}

void PrintMatrixChainResults(vector<MatrixChainResult> results) {
	cout << left;
	cout << setw(25) << "Function" << setw(25) << "Parenthesization" << setw(30) << "Optimal Multiplications" << setw(25) << "Time" << endl;
	int prev_n = -1;
	for (int i = 0; i < results.size(); i++) {
		string function = results[i].functionName;
		string parens = PrintParenthesis(results[i]);
		string mults = to_string(results[i].m[1][results[i].m.size()-1]);
		string time = printTime(results[i].nanoseconds);
		cout << setw(25) << function << setw(25) << parens << setw(30) << mults << setw(25) << time << endl;
	}
	cout << endl;
}

vector<MatrixChainResult> RunMatrixChainTests(vector<void(*)(vector<int> p, vector<vector<int>>& m, vector<vector<int>>& s)> functions, vector<string> function_names, vector<int> inputs) {

	// initialize variables for holding results
	vector<MatrixChainResult> results;

	//Run tests
	//for each function
	for (int i = 0; i < functions.size(); i++) {
		MatrixChainResult result = TimeMatrixChain(functions[i], inputs);
		result.functionName = function_names.at(i);
		results.push_back(result);
	}
	return results;
}