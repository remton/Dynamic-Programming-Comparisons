#include "Fibonacci.h"


// --- ALGORITHMS ---

//straightforward recursive solution (with no dynamic programming)
long long int Fibonacci_Recursive(int n) {
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;
    return Fibonacci_Recursive(n - 1) + Fibonacci_Recursive(n - 2);
}

//memoized topdown version
long long int Fibonacci_Memoized_Aux(long long int* memo, int n) {
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;
    if (memo[n] == 0)
        memo[n] = Fibonacci_Memoized_Aux(memo, n - 1) + Fibonacci_Memoized_Aux(memo, n - 2);
    return memo[n];
}
long long int Fibonacci_Memoized(int n) {
    long long int* memo = new long long int[n + 1];
    for (int i = 0; i < n+1; i++) {memo[i] = 0;}
    long long int ans = Fibonacci_Memoized_Aux(memo, n);
    delete[] memo;
    return ans;
}

//bottom-up version
long long int Fibonacci_Bottom_up(int n) {
    long long int prev_f = 0;
    long long int curr_f = 1;
    for (int i = 1; i < n; i++) {
        long long int f = prev_f + curr_f;
        prev_f = curr_f;
        curr_f = f;
    }
    return curr_f;
}


