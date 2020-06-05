#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include "Graph.h"

void GenerateDataSet(int size, int startNode)
{
    std::ofstream fout("DataSet.txt");
    int line = 0;
    srand(time(NULL));

    fout << size << "\n" << startNode << "\n";

    while (line < size)
    {
        int column = 0;

        while (column < size)
        {
            if (line != column)
            {
                int randomTime = rand() % 100 + 1;
                fout << randomTime << " ";
                column++;
            }
            else
            {
                fout << "0 ";
                column++;
            }
        }

        fout << "\n";
        line++;
    }
}

int main()
{
    Graph graph;
    std::vector<int> minPermutation;
    int minTime;

    graph.ReadGraph("Input.txt");
    graph.GeneratePermutations(minPermutation, minTime);

    if (minTime != INT32_MAX)
    {
        std::cout << "The minimum permutation:\n";
        graph.ShowPermutation(minPermutation, minTime);
    }
    else
        std::cout << "No result!\n";

    std::cout << "\n";
    Graph largeGraph;
    GenerateDataSet(10, 0);
    largeGraph.ReadGraph("DataSet.txt");
    
    largeGraph.GeneratePermutations(minPermutation, minTime);

    if (minTime != INT32_MAX)
    {
        std::cout << "The minimum permutation:\n";
        largeGraph.ShowPermutation(minPermutation, minTime);
    }
    else
        std::cout << "No result!\n";

    system("pause");
    return 0;
}