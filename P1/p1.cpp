using namespace std;
#include <iostream>
#include <vector>
#include <unordered_set>

/*  
    PROBLEM 1: Continuous Subarray Sum Equals K (Vector)

    Given an integer array nums and an integer k, return true if there exists a 
    continuous subarray of size at least two whose sum is a multiple of k. 
*/

/* 
    Input: nums = [2,4,6,7], k = 6
    Output: true
    Explanation: 
    [2,4] sums to 6.
*/

/*
    Dont Assume!
    Questions:
        Is the vector sorted? No.
        Does the vector contain negative numbers? Yes.
*/

/*
    Idea: Use prefix sum pattern!
    Prefixsum - target = (The value we must find)
*/

bool hasSubArray(const vector<int> &nums, int k)
{
    unordered_set<int> seen = {0}; // initialize set with 0

    int prefixSum = 0;
    for(int num: nums)
    {
        prefixSum += num;
        int findVal = prefixSum - k; 

        if(seen.find(findVal) != seen.end()) {return true;}

        seen.insert(num);
    }
    return false;
}



int main() 
{
    // test cases

    vector<int> v1 = {2, 4, 5, 7}; // ordered
    int k1 = 6;
    // true
    cout << (hasSubArray(v1, k1) ? "true" : "false") << endl;

    vector<int> v2 = {2, 7, 1, 3}; // unordered
    int k2 = 8;
    // true
    cout << (hasSubArray(v2, k2) ? "true" : "false") << endl;

    vector<int> v3 = {2, 4, -1, 7}; // negative
    int k3 = 3;
    // true
    cout << (hasSubArray(v3, k3) ? "true" : "false") << endl;

    vector<int> v4 = {2}; // single value
    int k4 = 2;
    // true
    cout << (hasSubArray(v4, k4) ? "true" : "false") << endl;

    vector<int> v5 = {}; // empty
    int k5 = 0;
    // false
    cout << (hasSubArray(v5, k5) ? "true" : "false") << endl;

    return 0;
}

