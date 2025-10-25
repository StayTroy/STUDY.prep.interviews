using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/*  
    PROBLEM 2: Course Schedule (Graph - Adjacency List)
    There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
    Return true if you can finish all courses. Otherwise, return false.
*/

/* 
    Input: numCourses = 2, prerequisites = [[1,0]]
    Output: true
    Explanation: 
    There are a total of 2 courses to take. 
    To take course 1 you should have finished course 0. So it is possible.
*/

/*
    Dont Assume!
    Questions:
        Is the graph directed or undirected?
        → e.g., A → B vs. A ↔ B.

        Can there be cycles?
        → affects if you need cycle detection (for topological sort, DFS recursion, etc.).

        Is the graph weighted or unweighted?
        → determines if you need Dijkstra/Bellman-Ford or just BFS.

        Are negative weights allowed?
        → if yes, Dijkstra fails, use Bellman-Ford.

        Can there be self-loops or multiple edges between the same nodes?
        → e.g., [a, a] or two edges (a, b) repeated.  
*/

/*
    Idea: build adjacency list graph
          check for back edge in graph 
          return false if cycle true otehrwise
*/

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
    {
        // build map (empty)
        for(int i = 0; i < numCourses; i++)
        {
            adjList[i] = {};
        }

        // fill dependency list for courses
        for (const auto& prereq: prerequisites)
        {
            adjList[prereq[0]].push_back(prereq[1]);
        }

        // perform dfs on every course in directed graph
        for (const auto& [course, v] : adjList)
        {
            if (!dfs(course)) {return false;}
        }
        return true;
    }

private:
    // represent vector of pairs as a directed graph
    unordered_map<int, vector<int>> adjList;
    unordered_set<int> seen;

    bool dfs(int course)
    {
        // base case
        if (adjList[course].empty()) {return true;} // no dependencies

        // check for cycle 
        if (seen.find(course) != seen.end()) {return false;} // back edge found

        //otherwise insert
        seen.insert(course);

        // for each prereq course perform dfs
        for (const auto& prereq: adjList[course])
        {
            if (!dfs(prereq)) {return false;}
        }

        seen.erase(course);
        adjList[course].clear();
        return true;
    }
};

int main() 
{
    // test cases
    
    // cycle exists -> false
    Solution sol1;
    vector<vector<int>> prereq1 = {{1, 0}, {2, 1}, {0, 2}};
    cout << (sol1.canFinish(3, prereq1) ? "true" : "false") << endl;

    // no cycle -> true
    Solution sol2;
    vector<vector<int>> prereq2 = {{1, 0}, {2, 1}, {3, 2}};
    cout << (sol2.canFinish(4, prereq2) ? "true" : "false") << endl;

    // empty prerequisites -> true
    Solution sol3;
    vector<vector<int>> prereq3 = {};
    cout << (sol3.canFinish(0, prereq3) ? "true" : "false") << endl;

    return 0;
}