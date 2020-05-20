#pragma once
#include <vector>
#include <iostream>

class Graph
{
private:
	int nodes;
	int startNode;
	std::vector<std::vector<int>> adMatrix;

public:
	Graph();

	int getNodes();
	void setNodes(int nodes);
	std::vector<std::vector<int>> getAdMatrix();
	void setAdMatrix(std::vector<std::vector<int>> adMatrix);
	int getStartNode();
	void setStartNode(int startNode);

	void ReadGraph();
	void GeneratePermutations(std::vector<int>& minPermutations, int& minTime);
	void ShowPermutation(std::vector<int> permutation, int time);
};

