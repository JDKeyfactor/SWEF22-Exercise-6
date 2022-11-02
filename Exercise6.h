#pragma once

/*********************************************/
/* Definitions and test framework functions. */
/* DO NOT MODIFY CONTENTS OF THIS FILE.      */
/* Yes, there's code in a .h file. Sue me.   */
/*********************************************/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

// Return type for two-sum functions
struct result {
    bool possible = false;
    int first = -1;
    int second = -1;
};

// Tracking number of branches in code under test
int branchNum = 0;
int nBranches;
char* currentFunction;
#define TESTBRANCH {currentFunction = (char*)__func__; static int t = -1; if (t < 0) { t = branchNum++; }; paths.push_back(t);}

// Machinery to register test cases and measure results
std::vector<void (*)()> testCases = std::vector<void (*)()>();
int registerTest(void func()) { testCases.push_back(func); return 0; }
#define TESTCASE(name, func) void func(); int name = registerTest(func);
#define RUNTEST() {runTest(expected, target, arr, (char*)__func__);}
std::vector<int> paths = std::vector<int>();
int nPass = 0;
int nFail = 0;

// Variables to be assigned in a test case. Not thread-safe.
unsigned int target;
std::vector<unsigned int> arr;
bool expected;

// Definitions for the functions to be tested.
result twoSumNaive(unsigned int target, std::vector<unsigned int> elements);
result twoSumwSort(unsigned int target, std::vector<unsigned int> elements);
result twoSumwHash(unsigned int target, std::vector<unsigned int> elements);

// Run provided test function with given arguments and expected output (with result indexes in either order). Track results.
bool runTest(bool expected, unsigned int target, std::vector<unsigned int> elements, result func(unsigned int, std::vector<unsigned int>), char* testName) {
    result actual = func(target, elements);
    if (!actual.possible && !expected) {
        nPass++;
        return true;
    }
    if (actual.first >= 0 && actual.second >= 0 && actual.possible == expected && elements[actual.first] + elements[actual.second] == target && actual.first != actual.second) {
        nPass++;
        return true;
    }
    printf("Expected %d but got %d (indexes %d,%d) from %s on %s\n", expected, actual.possible, actual.first, actual.second, currentFunction, testName);
    nFail++;
    return false;
}

// Run tests for all functions with given arguments and expected output.
void runTest(bool expected, unsigned int target, std::vector<unsigned int> elements, char* testName) {
    runTest(expected, target, elements, twoSumNaive, testName);
    runTest(expected, target, elements, twoSumwSort, testName);
    runTest(expected, target, elements, twoSumwHash, testName);
}

// Run all registered tests on every version of two-sum
void runAllTests() {
    for (int i = 0; i < testCases.size(); i++) {
        (*testCases[i])();
    }
}

// Get the percentage of test cases that passed testing
float getPassRate() {
    return (float)nPass / (testCases.size() * 3) * 100;
}

// Get percentage of branches executed by at least one test
float getBranchCoverage() {
    std::sort(paths.begin(), paths.end());
    std::vector<int>::iterator last = std::unique(paths.begin(), paths.end());
    paths.resize(std::distance(paths.begin(), last));
    return (float)paths.size() / nBranches * 100;
}