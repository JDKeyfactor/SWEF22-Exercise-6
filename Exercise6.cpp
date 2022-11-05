#include "Exercise6.h"
#include <iostream>
 
// Student name: Anthony Lupica

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

int branchCount = 19;

// Two-sum function using a nested loop
// Cyclomatic complexity = 5
// Runtime (big-O) complexity = O(N^2)
result twoSumNaive(unsigned int target, std::vector<unsigned int> elements) 
{ TESTBRANCH

    for (int i = 0; i < elements.size(); i++) 
    { TESTBRANCH 
        
        for (int j = 0; j < elements.size(); j++) 
        { TESTBRANCH 

            /* return true when elements[i] + elements[j] == target iff . . .

                * i != j "No comparing an element against itself" 
            */
            if ((i != j) && (elements[i] + elements[j] == target))
            { TESTBRANCH
    
                return result{ true, i, j };

            } TESTBRANCH
        } TESTBRANCH
    } TESTBRANCH
    
    return result{};
}

// Two-sum function using a sorted list
// Cyclomatic complexity = 3
// Runtime (big-O) complexity = O(N)
result twoSumwSort(unsigned int target, std::vector<unsigned int> elements) 
{ TESTBRANCH

    std::sort(elements.begin(), elements.end());
    result r = result{};
    
    for (int i = 0; i < elements.size(); i++) 
    { TESTBRANCH
        
        // diff is the number that must be found elsewhere in the array to complete the equivalence
        // elements[i] + diff = target, for some index i
        int diff = target - elements[i];
        
        // set elements[i] to sentinel value -99 and store a copy
        int tempVal = elements[i];
        elements[i] = -99;
        bool exists = std::binary_search(elements.begin(), elements.end(), diff);
        
        // block only entered if the corresponding diff exists for elements[i]
        std::vector<unsigned int>::iterator diffItr;

        if (exists) 
        { TESTBRANCH
            
            diffItr = std::find(elements.begin(), elements.end(), diff);

            if (diffItr != elements.end())
            { TESTBRANCH
                
                int diffIndex = std::distance(elements.begin(), diffItr);

                r.first = i;
                r.second = diffIndex;
                r.possible = true;

                return r;

            } TESTBRANCH
        } TESTBRANCH

        // restore elements[i]
        elements[i] = tempVal;

    } TESTBRANCH
    
    return result{};
}

// Two-sum function using a hash table
// Cyclomatic complexity = 4
// Runtime (big-O) complexity = O(N)
result twoSumwHash(unsigned int target, std::vector<unsigned int> elements) 
{ TESTBRANCH

    std::unordered_map<int, int> elementMap = std::unordered_map<int, int>(target);
    
    for (int i = 0; i < elements.size(); i++) 
    { TESTBRANCH

        int other = elementMap[target - elements[i]];
        elementMap[elements[i]] = i+1;
        if (other > 0 && other != i+1) 
        { TESTBRANCH

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
void test1() 
{
    target = 0;
    arr = {0, 0};
    expected = true;
    RUNTEST();
} 

TESTCASE(t2, test2)
void test2() 
{
    target = 4;
    arr = {2, 1, 3};
    expected = true;
    RUNTEST();
}

TESTCASE(t3, test3)
void test3() 
{
    target = 4;
    arr = {2, 1, 1};
    expected = false;
    RUNTEST();
}

TESTCASE(t4, test4)
void test4() 
{
    target = 6;
    arr = {3, 2, 3};
    expected = true;
    RUNTEST();
}

TESTCASE(t5, test5)
void test5() 
{
    target = 6;
    arr = {1, 2, 3, 4, 5};
    expected = true;
    RUNTEST();
}

TESTCASE(t6, test6)
void test6() 
{
    target = 10;
    arr = {1, 2, 3, 4, 5};
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
    std::cout << "\nPass rate: " << getPassRate() << "%\n";
    std::cout << "Coverage: " << getBranchCoverage() << "%\n";
}
