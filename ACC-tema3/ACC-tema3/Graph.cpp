#include <fstream>
#include <algorithm>

#include "Graph.h"

Graph::Graph()
{
	nodes = 0;
	startNode = 0;
}

int Graph::getNodes()
{
	return nodes;
}

void Graph::setNodes(int nodes)
{
	this->nodes = nodes;
}

std::vector<std::vector<int>> Graph::getAdMatrix()
{
	return adMatrix;
}

void Graph::setAdMatrix(std::vector<std::vector<int>> adMatrix)
{
	this->adMatrix = adMatrix;
}

int Graph::getStartNode()
{
	return startNode;
}

void Graph::setStartNode(int startNode)
{
	this->startNode = startNode;
}

void Graph::ReadGraph()
{
	std::ifstream fin("Input.txt");

	fin >> nodes;
	fin >> startNode;

	for (int index1 = 0; index1 < nodes; index1++)
	{
		std::vector<int> line;

		for (int index2 = 0; index2 < nodes; index2++)
		{
			int elem;
			fin >> elem;
			line.push_back(elem);
		}

		adMatrix.push_back(line);
	}
}

void Graph::GeneratePermutations(std::vector<int>& minPermutation, int& minTime)
{
	std::vector<int> permutation;
	int time = 0;

	minTime = INT32_MAX;

	for (int index = 0; index < nodes; index++)
	{
		permutation.push_back(index);
	}

	do
	{
		bool valid = true;

		if (permutation[0] != startNode)
			valid = false;
		else if (adMatrix[permutation[permutation.size() - 1]][permutation[0]] == 0)
			valid = false;
		else
		{
			time += adMatrix[permutation[permutation.size() - 1]][permutation[0]];

			for (int index = 0; index < permutation.size() - 1; index++)
			{
				if (adMatrix[permutation[index]][permutation[index + 1]] == 0)
				{
					valid = false;
					break;
				}
				else
					time += adMatrix[permutation[index]][permutation[index + 1]];
			}
		}

		if (valid)
		{
			if (time < minTime)
			{
				minTime = time;
				minPermutation = permutation;
			}
		}

		time = 0;
	} while (std::next_permutation(permutation.begin(), permutation.end()));
}

void Graph::ShowPermutation(std::vector<int> permutation, int time)
{
	for (int index = 0; index < permutation.size(); index++)
	{
		std::cout << permutation[index] << " ";
	}
	
	std::cout << startNode << "\n";
	std::cout << "The time is: " << time << "\n";
}
