



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
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
// Student name: Nicholas Limbach

// Exercise directions
/****************************************************/
/* First, enter your name in the space above.       */
/* Fill in the cyclomatic complexity and run-time   */
/* complexity for each of the three two-sum methods,*/
/* then write and run tests to achieve 100% code    */
/* (branch) coverage and pass rate. Fix any bugs    */
/* in the two-sum methods uncovered by testing. Do  */
/* not commit or merge to main; complete all work   */
/* in your own branch and issue a pull request when */
/* finished. Carefully read the two-sum definition. */
/****************************************************/

// Two-sum definition
/****************************************************/
/* If there are two distinct i, j in input array of */
/* ints that together sum to the input target int,  */
/* return a result with possible = true, first = i, */
/* and second = j. i,j may map to first & second in */
/* either order. If there are no such i, j, return  */
/* the default result object with possible = false. */
/* All input integers are non-negative, and you may */
/* assume that no elements in the array are larger  */
/* than the target sum.                             */
/****************************************************/

// Tested code area
/*************************************************/
/* Two-sum function definitions to be tested.    */
/* Modify this code to fix bugs as needed.       */
/* Do not alter method signatures.               */
/* Keep a TESTBRANCH statement for every branch, */
/* and update the branchCount value below to     */
/* match the number of TESTBRANCH statements.    */
/*************************************************/

int branchCount = 17;

// Two-sum function using a nested loop
// Cyclomatic complexity = 4 + 1
// Runtime (big-O) complexity = N^2
result twoSumNaive(unsigned int target, std::vector<unsigned int> elements) {
    TESTBRANCH
        for (int i = 0; i < elements.size(); i++) {
            TESTBRANCH
                for (int j = 0; j < elements.size(); j++) {
                    TESTBRANCH
                        if (elements[i] + elements[j] == target && elements[i] != elements[j]) { TESTBRANCH //Added the && statment defination requires I and J to be distinct also added not negative increase cyclic complexity by 1
                            
                                return result{ true, i, j };
                           
                        } TESTBRANCH
                } TESTBRANCH
        } TESTBRANCH
            return result{};
}

// Two-sum function using a sorted list
// Cyclomatic complexity = 3 + 2
// Runtime (big-O) complexity = N
result twoSumwSort(unsigned int target, std::vector<unsigned int> elements) {
    TESTBRANCH
        std::sort(elements.begin(), elements.end());
    result r = result{};
    for (int i = 0; i < elements.size(); i++) {
        TESTBRANCH
            int diff = target - elements[i];
        bool exists = std::binary_search(elements.begin(), elements.end(), diff);
        if (exists) {
            TESTBRANCH
                int diffIndex = std::find(elements.begin(), elements.end(), diff) - elements.begin();
            r.first = i;
            r.second = diffIndex;
            if (r.first != r.second) // Added this block increasing cyclic complexity by 1 as there are now two conditions
            {
                r.possible = true;
            }
            else
            {
                r.possible = false;
            }
            return r;
        } TESTBRANCH
    } TESTBRANCH
        return result{};
}

// Two-sum function using a hash table
// Cyclomatic complexity = 4
// Runtime (big-O) complexity = N
result twoSumwHash(unsigned int target, std::vector<unsigned int> elements) {
    TESTBRANCH
        std::unordered_map<int, int> elementMap = std::unordered_map<int, int>(target);
    for (int i = 0; i < elements.size(); i++) {
        TESTBRANCH
            int other = elementMap[target - elements[i]];
        elementMap[elements[i]] = i + 1;
        if (other > 0 && other != i + 1) {
            TESTBRANCH
                return result{ true, i, other - 1};
        } TESTBRANCH
    } TESTBRANCH
        return result{};
}

// Test case area
/****************************************************/
/* Test cases to be run against two-sum methods.    */
/* Add as many test cases as you need to achieve    */
/* 100% code coverage and identify any bugs in      */
/* methods being tested. Add a TESTCASE statement   */
/* above each case you create, giving an arbitrary  */
/* UNIQUE identifier for the first argument and     */
/* the function name for the second argument. Use   */
/* the variable names "target" and "arr" for two-   */
/* sum method arguments, and "expected" for the     */
/* result that should be returned for those values. */
/* Include RUNTESTS() at the end to execute test    */
/* case.                                            */
/****************************************************/

TESTCASE(t1, test1)
void test1() {
    target = 1;
    arr = { 1,0 };
    expected = true;
    RUNTEST();
}

TESTCASE(t2, test2)
void test2() {
    target = 1;
    arr = { 0,0 };
    expected = false;
    RUNTEST();
}

TESTCASE(t3, test3)
void test3() {
    target = 0;
    arr = { 1,0 };
    expected = false;
    RUNTEST();
}

TESTCASE(t4, test4)
void test4() {
    target = 1;
    arr = { 0,1 };
    expected = true;
    RUNTEST();
}

// Main function area
/*************************************************/
/* Main function to run tests and print (branch) */
/* coverage and pass rate for executed tests. Do */
/* not modify this method.                       */
/*************************************************/

int main()
{
    nBranches = branchCount;
    runAllTests();
    std::cout << "Pass rate: " << getPassRate() << "%\n";
    std::cout << "Coverage: " << getBranchCoverage() << "%\n";
}
