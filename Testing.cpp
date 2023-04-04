#include"Testing.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include "Fibonacci.h"
#include "MatrixChain.h"

using namespace std;

string printTime(int microseconds) {
	return to_string(microseconds) + " microseconds";
}

//Runs the tests on the given fibonacci function and returns the runtime in microseconds
FibonacciResult TimeFibonacci(long long int(*func)(int), int n) {
	FibonacciResult result;
	auto start = chrono::steady_clock::now();
	result.ans = func(n);
	auto end = chrono::steady_clock::now();
	result.nanoseconds = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	result.n = n;
	return result;
}

vector<FibonacciResult> FibonacciFindMaxPracticalResult(vector<FibonacciResult> results) {
	vector<FibonacciResult> max;
	for (int i = 0; i < results.size(); i++) {
		if (results[i].isPractical) {
			bool hasFunc = false;
			for (int j = 0; j < max.size(); j++) {
				if (results[i].functionName == max[j].functionName) {
					hasFunc = true;
					if (results[i].n > max[j].n) {
						max[j] = results[i];
					}
				}
			}
			if (!hasFunc)
				max.push_back(results[i]);
		}
	}
	return max;
}

//Prints the results for the given fibonacci results
void PrintFibonacciResults(vector<FibonacciResult> results) {
	cout << left;
	cout << setw(35) << "Function" << setw(35) << "Result" << setw(35) << "Time" << endl;
	int prev_n = -1;
	for (int i = 0; i < results.size(); i++) {
		if (results[i].n != prev_n)
			cout << endl;
		prev_n = results[i].n;
		string function = results[i].functionName + "(" + to_string(results.at(i).n) + ")";
		string time = printTime(results[i].nanoseconds);
		cout << setw(35) << function << setw(35) << to_string(results.at(i).ans) << setw(35) << time << endl;
	}
	cout << endl;
}
//Runs and prints tests for given functions and inputs
vector<FibonacciResult> RunFibonacciTests(vector<long long int(*)(int)> functions, vector<string> function_names, vector<int> inputs) {
	sort(inputs.begin(), inputs.end());

	// initialize variables for holding results
	vector<bool> fibonacci_do_test;
	vector<FibonacciResult> fibonacci_results;
	for (size_t i = 0; i < functions.size(); i++) {
		fibonacci_do_test.push_back(true);
		FibonacciResult r;
	}
	//Run tests
	//for each input size
	for (int i = 0; i < inputs.size(); i++) {
		//for each function
		for (int j = 0; j < functions.size(); j++) {
			if (fibonacci_do_test[j]) {
				FibonacciResult result = TimeFibonacci(functions[j], inputs[i]);
				result.functionName = function_names[j];
				result.isPractical = true;
				if (result.nanoseconds >= MAX_PRACTICAL_TIME_SEC * SECONDS_TO_MICROSECONDS) {
					fibonacci_do_test[j] = false;
					result.isPractical = false;
				}
				fibonacci_results.push_back(result);
			}
		}
	}
	return fibonacci_results;
}

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

string PrintParenthesisAux(vector<vector<int>> s, int i, int j) {
	string str;
	if (i == j) {
		str += "A" + to_string(i);
	}
	else {
		str += "(";
		str += PrintParenthesisAux(s, i, s[i][j]);
		str += PrintParenthesisAux(s, s[i][j]+1, j);
		str += ")";
	}
	return str;
}
string PrintParenthesis(MatrixChainResult result) {
	return PrintParenthesisAux(result.s, 1, result.s.size()-1);
}

void PrintMatrixChainResults(vector<MatrixChainResult> results) {
	cout << left;
	cout << setw(25) << "Function" << setw(30) << "Parenthesization" << setw(30) << "Optimal Multiplications" << setw(25) << "Time" << endl;
	int prev_n = -1;
	for (int i = 0; i < results.size(); i++) {
		string function = results[i].functionName;
		string parens = PrintParenthesis(results[i]);
		string mults = to_string(results[i].m[1][results[i].m.size() - 1]);
		string time = printTime(results[i].nanoseconds);
		cout << setw(25) << function << setw(30) << parens << setw(30) << mults << setw(25) << time << endl;
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