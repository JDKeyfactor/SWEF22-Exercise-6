#include "Exercise6.h"
 
// Student name: Shubh Patel

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

//There shouldn't be a global variable unless its constant but I don't want to make it local incase it messes up the program
int branchCount = 19;

// Two-sum function using a nested loop
// Cyclomatic complexity = 4 for unfixed code or 5 for fixed code
// Runtime (big-O) complexity = O(n^2)
result twoSumNaive(unsigned int target, std::vector<unsigned int> elements) 
{ TESTBRANCH
    //Loops through the vector
    for (int i = 0; i < elements.size(); ++i) 
    { TESTBRANCH
        //Nested loop for the vector
        for (int j = 0; j < elements.size(); ++j) 
        { TESTBRANCH
            //Code sees if the elements from the two loops added together are equal to desired value
            //Added (i != j) to the if statement to fix code to check if indexed are the same.
            if (elements[i] + elements[j] == target && i != j) 
            { TESTBRANCH
                return result{true, i, j};
            } TESTBRANCH
        } TESTBRANCH
    } TESTBRANCH
    return result{};
}

// Two-sum function using a sorted list
// Cyclomatic complexity = 2 for unfixed code, 3 for fixed code
// Runtime (big-O) complexity = O(n)
result twoSumwSort(unsigned int target, std::vector<unsigned int> elements) 
{ TESTBRANCH
    //This sorts the vector and makes a result object.
    std::sort(elements.begin(), elements.end());
    result r = result{};

    //Loops through the vector
    for (int i = 0; i < elements.size(); ++i) 
    { TESTBRANCH
        //Calculates the diffence between target and current value in loop
        int diff = target - elements[i];
        //Checks if the difference exists in the vector
        bool exists = std::binary_search(elements.begin(), elements.end(), diff);
        
        //Conditional activates if two values that are equal to target value are found
        if (exists) 
        { TESTBRANCH
            //Gets the index of 2nd value
            int diffIndex = std::find(elements.begin(), elements.end(), diff) - elements.begin();
            //Added a if statement to check if the indexes are the same
            //for the values. If so performs the desired operations
            if (diffIndex != i) 
            { TESTBRANCH
                r.first = i;
                r.second = diffIndex;
                r.possible = true; //Added this to fix code which lets program know a match is found
                return r;
            } TESTBRANCH
        } TESTBRANCH
    } TESTBRANCH
    return result{};
}

// Two-sum function using a hash table
// Cyclomatic complexity = 4
// Runtime (big-O) complexity = O(n)
result twoSumwHash(unsigned int target, std::vector<unsigned int> elements) 
{ TESTBRANCH
    //Initials hashmap with target value as a key
    std::unordered_map<int, int> elementMap = std::unordered_map<int, int>(target);
    for (int i = 0; i < elements.size(); ++i) 
    { TESTBRANCH
        //Sees if the target minus current element exist in hash map and stores its index if it does.
        int other = elementMap[target - elements[i]];
        //Adds the current value as a key and its current index + 1 as value.
        elementMap[elements[i]] = i + 1;
        //Checks if the other variable has a value greater then 1 and not equal to current value index+1. If it does
        //then it executes the desired operations.
        if (other > 0 && other != i + 1) 
        { TESTBRANCH
            return result{true, i, other - 1};
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

/*
Bug List:
1. Naive test did not check if indexes were same for values.
2. Sort test did not check if indexes were same for values.
3. Sort test did not set the .possible value to true.
*/

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
    target = 8;
    arr = {1, 3, 5, 7};
    expected = true;
    RUNTEST();
}

TESTCASE(t3, test3)
void test3() 
{
    target = 13;
    arr = {2, 4, 7, 6};
    expected = true;
    RUNTEST();
}

TESTCASE(t4, test4)
void test4() 
{
    target = 13;
    arr = {0, 0};
    expected = false;
    RUNTEST();
}

TESTCASE(t5, test5)
void test5() 
{
    target = 7;
    arr = {1, 0, 3};
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
