#include "Exercise6.h"

// Student name: Kent Hoang

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

// updates from 17 -> 21
// 2 for method 1 fix,
// another 2 for method 2 fix
int branchCount = 21;

// Two-sum function using a nested loop
// Cyclomatic complexity with fixed code beomces 5
// Runtime (big-O) complexity = n^2
result twoSumNaive(unsigned int target, std::vector<unsigned int> elements)
{
    TESTBRANCH
    for (int i = 0; i < elements.size(); i++)
    {
        TESTBRANCH
        for (int j = 0; j < elements.size(); j++)
        {
            TESTBRANCH
            if (i != j)
            {
                TESTBRANCH
                if (elements[i] + elements[j] == target)
                {
                    TESTBRANCH
                    return result{true, i, j};
                }
                TESTBRANCH
            }
            TESTBRANCH
        }
        TESTBRANCH
    }
    TESTBRANCH
    return result{};
}

// Two-sum function using a sorted list
// Cyclomatic complexity with fixed code becomes 4
// Runtime (big-O) complexity = O(nlogn)
result twoSumwSort(unsigned int target, std::vector<unsigned int> elements)
{
    TESTBRANCH
    std::vector<unsigned int> copy(elements);
    std::sort(copy.begin(), copy.end());
    for (int i = 0; i < copy.size(); i++)
    {
        TESTBRANCH
        int diff = target - copy[i];
        bool exists = std::binary_search(copy.begin() + i + 1, copy.end(), diff);
        if (exists)
        {
            int first = std::find(elements.begin(), elements.end(), copy[i]) - elements.begin();
            int diffIndex;
            if (diff == elements[first])
            {
                TESTBRANCH
                diffIndex = std::find(elements.begin() + first + 1, elements.end(), diff) - elements.begin();
            }
            else
            {
                diffIndex = std::find(elements.begin(), elements.end(), diff) - elements.begin();
            }
            TESTBRANCH
            return result{true, first, diffIndex};
        }
        TESTBRANCH
    }
    TESTBRANCH
    return result{};
}

// Two-sum function using a hash table
// Cyclomatic complexity = 3
// Runtime (big-O) complexity = O(n)
result twoSumwHash(unsigned int target, std::vector<unsigned int> elements)
{
    TESTBRANCH
    std::unordered_map<int, int> elementMap = std::unordered_map<int, int>(target);
    for (int i = 0; i < elements.size(); i++)
    {
        TESTBRANCH
        int other = elementMap[target - elements[i]];
        elementMap[elements[i]] = i + 1;
        if (other > 0 && other != i + 1)
        {
            TESTBRANCH
            return result{true, i, other - 1};
        }
        TESTBRANCH
    }
    TESTBRANCH
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
void test1()
{
    target = 0;
    arr = {0, 0};
    expected = true;
    RUNTEST();
}

// should be true return for index (2,3)
TESTCASE(t2, test2)
void test2()
{
    target = 2;
    arr = {1, 1, 2, 0};
    expected = true;
    RUNTEST();
}
// should be for the two index at the end of the array
TESTCASE(t3, test3)
void test3()
{
    target = 40;
    arr = {1, 2, 3, 4, 7, 9, 6, 8, 15, 25};
    expected = true;
    RUNTEST();
}

// case when no sums is the target
TESTCASE(t4, test4)
void test4()
{
    target = 9;
    arr = {2, 3, 4, 2, 3, 4};
    expected = false;
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
