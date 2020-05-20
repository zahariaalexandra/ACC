#include <iostream>

#include "Graph.h"

int main()
{
    Graph graph;
    std::vector<int> minPermutation;
    int minTime;

    graph.ReadGraph();
    graph.GeneratePermutations(minPermutation, minTime);

    if (minTime != INT32_MAX)
    {
        std::cout << "The minimum permutation:\n";
        graph.ShowPermutation(minPermutation, minTime);
    }
    else
        std::cout << "No result!\n";

    system("pause");
    return 0;
}