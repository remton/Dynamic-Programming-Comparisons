#pragma once
#include <vector>
using namespace std;

void Matrix_Chain_Recursive(vector<int> p, vector<vector<int>>& m, vector<vector<int>>& s);
void Matrix_Chain_Memoized(vector<int> p, vector<vector<int>>& m, vector<vector<int>>& s);
void Matrix_Chain_Bottom_Up(vector<int> p, vector<vector<int>>& m, vector<vector<int>>& s);
