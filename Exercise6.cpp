#include "Exercise6.h"
 
// Student name: _____Kenneth Mills______

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
// Cyclomatic complexity = _4__
// Runtime (big-O) complexity = _n^2__
result twoSumNaive(unsigned int target, std::vector<unsigned int> elements) { TESTBRANCH
    for (int i = 0; i < elements.size(); i++) { TESTBRANCH
        for (int j = 0; j < elements.size(); j++) { TESTBRANCH
            if (elements[i] + elements[j] == target) { TESTBRANCH
                if(i != j) { TESTBRANCH
                  return result{ true, i, j};
                } TESTBRANCH
            } TESTBRANCH
        } TESTBRANCH
    } TESTBRANCH
    return result{};
}

// Two-sum function using a sorted list
// Cyclomatic complexity = _3__
// Runtime (big-O) complexity = _nlogn__
result twoSumwSort(unsigned int target, std::vector<unsigned int> elements) { TESTBRANCH
    std::vector<unsigned int>elem_copy(elements);
    std::sort(elem_copy.begin(), elem_copy.end());
    for (int i = 0; i < elem_copy.size(); i++) { TESTBRANCH
        int diff = target - elem_copy[i];
        bool exists = std::binary_search(elem_copy.begin() + i + 1, elem_copy.end(), diff);
        if (exists) { TESTBRANCH
            i = std::find(elements.begin(), elements.end(), elem_copy[i]) - elements.begin();
            int diffIndex;
            if(diff == elements[i]) { TESTBRANCH
              diffIndex = std::find(elements.begin() + i + 1, elements.end(), diff) - elements.begin();
            }
            else {
              diffIndex = std::find(elements.begin(), elements.end(), diff) - elements.begin();
            } TESTBRANCH
            return result{true, i, diffIndex};
        } TESTBRANCH
    } TESTBRANCH
    return result{};
}

// Two-sum function using a hash table
// Cyclomatic complexity = _2__
// Runtime (big-O) complexity = _n__
result twoSumwHash(unsigned int target, std::vector<unsigned int> elements) { TESTBRANCH
    std::unordered_map<int, int> elementMap = std::unordered_map<int, int>(target);
    for (int i = 0; i < elements.size(); i++) { TESTBRANCH
        int other = elementMap[target - elements[i]];
        elementMap[elements[i]] = i+1;
        if (other > 0 && other != i+1) { TESTBRANCH
            return result{ true, i, other-1};
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
    target = 0;
    arr = {0,0};
    expected = true;
    RUNTEST();
}

TESTCASE(t2, test2)
void test2() {
  target = 3;
  arr = {2, 1, 0};
  expected = true;
  RUNTEST();
}

TESTCASE(t3, test3)
void test3() {
  target = 1;
  arr = {0, 0};
  expected = false;
  RUNTEST();
}

TESTCASE(t4, test4)
void test4() {
  target = 10;
  arr = {1, 2, 5, 6, 3, 4};
  expected = true;
  RUNTEST();
}

TESTCASE(t5, test5)
void test5() {
  target = 11;
  arr = {2, 4, 6, 8, 10};
  expected = false;
  RUNTEST();
}

TESTCASE(t6, test6)
void test6() {
  target = 9;
  arr = {3, 3, 3, 3};
  expected = false;
  RUNTEST();
}

TESTCASE(t7, test7)
void test7() {
  target = 15;
  arr = {15, 1, 3};
  expected = false;
  RUNTEST();
}

TESTCASE(t8, test8)
void test8() {
  target = 99;
  arr = {54, 0, 1, 22, 45};
  expected = true;
  RUNTEST();
}

TESTCASE(t9, test9)
void test9() {
  target = 10;
  arr = {0, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 0};
  expected = true;
  RUNTEST();
}

TESTCASE(t10, test10)
void test10() {
  target = 100;
  arr = {50, 40, 60, 50};
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
