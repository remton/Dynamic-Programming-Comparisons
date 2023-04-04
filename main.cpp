// Remington Ward
// CS 4120 Algorithms
// This project compares the runtime of three different implementations of fibonacci and optimal matrix chain problems:
// Straightforward reursive
// Memoized recursive
// Bottom Up

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <vector>
#include "Fibonacci.h"
#include "MatrixChain.h"
#include "Testing.h"
using namespace std;

void TestFib(vector<int> inputs);
void TestMtrx(vector<int> inputs);
vector<int> GetNumbers(string input);

int main() {
	string FIB_CHOICE = "f";
	string MTRX_CHOICE = "m";
	string QUIT_CHOICE = "q";
	string input;
	do {
		cout << "To test Fibonacci type: " << FIB_CHOICE << endl;
		cout << "To test Matrix Chain type: "<< MTRX_CHOICE << endl;
		cout << "To quit type: " << QUIT_CHOICE << endl;
		getline(cin, input);
		if (input == FIB_CHOICE) {
			cout << "Write each value to test seperated by commas: " << endl;
			getline(cin, input);
			TestFib(GetNumbers(input));
		}
		if (input == MTRX_CHOICE) {
			cout << "How many matrices? " << endl;
			getline(cin, input);
			int count = stoi(input);
			cout << "Write the dimension changes in the matrix chain seperated by commas: " << endl;
			getline(cin, input);
			TestMtrx(GetNumbers(input));
		}

	} while (input != QUIT_CHOICE);
}

vector<int> GetNumbers(string input) {
	vector<int> inputVec;
	string numStr;
	for (size_t i = 0; i < input.size(); i++) {
		if (isdigit(input[i])) {
			numStr += input[i];
		}
		else if (numStr.size() > 0) {
			inputVec.push_back(stoi(numStr));
			numStr.clear();
		}
	}
	if (numStr.size() > 0) {
		inputVec.push_back(stoi(numStr));
		numStr.clear();
	}
	return inputVec;
}

void TestFib(vector<int> inputs) {
	// FIBONACCI
	vector<long long int(*)(int)> functions = { Fibonacci_Recursive, Fibonacci_Memoized, Fibonacci_Bottom_up };
	vector<string> function_names = { "Fibonacci_Recursive", "Fibonacci_Memoized", "Fibonacci_Bottom_up" };
	vector<FibonacciResult> results = RunFibonacciTests(functions, function_names, inputs);
	cout << endl << "=========== FIBONACCI TIMES ===========" << endl;
	PrintFibonacciResults(results);
	cout << endl << "==== FIBONACCI MAX PRACTICAL TIMES ====" << endl;
	PrintFibonacciResults(FibonacciFindMaxPracticalResult(results));
	cout << endl << endl;
}

void TestMtrx(vector<int> inputs) {
	// MATRIX CHAIN
	vector<void(*)(vector<int>, vector<vector<int>>&, vector<vector<int>>&)> functions = {
		Matrix_Chain_Recursive, Matrix_Chain_Memoized, Matrix_Chain_Bottom_Up
	};
	vector<string> function_names = {
		"Matrix_Chain_Recursive", "Matrix_Chain_Memoized", "Matrix_Chain_Bottom_Up"
	};
	vector<MatrixChainResult> results = RunMatrixChainTests(functions, function_names, inputs);
	cout << "========= MATRIX CHAIN RESULTS =========" << endl;
	PrintMatrixChainResults(results);
}