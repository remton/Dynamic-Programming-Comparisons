#pragma once

#include<vector>
#include<string>
using namespace std;

// Max practical time to test
const long long int MAX_PRACTICAL_TIME_SEC = 2;
const int SECONDS_TO_MICROSECONDS = 1000000;
string printTime(int microsecods);

// Fibonacci testing
// NOTE: If it takes longer than the max practical time to test an input, we do not test larger inputs for that function

struct FibonacciResult {
	string functionName;
	int n;
	bool isPractical;
	long long int ans;
	long long int nanoseconds;
};
vector<FibonacciResult> FibonacciFindMaxPracticalResult(vector<FibonacciResult> results);
vector<FibonacciResult> RunFibonacciTests(vector<long long int(*)(int)> functions, vector<string> function_names, vector<int> inputs);
void PrintFibonacciResults(vector<FibonacciResult> results);

// Matrix chain testing

struct MatrixChainResult {
	string functionName;
	vector<vector<int>> m;
	vector<vector<int>> s;
	long long int nanoseconds;
};

vector<MatrixChainResult> RunMatrixChainTests(vector<void(*)(vector<int>, vector<vector<int>>&, vector<vector<int>>&)> functions, vector<string> function_names, vector<int> inputs);
void PrintMatrixChainResults(vector<MatrixChainResult> results);