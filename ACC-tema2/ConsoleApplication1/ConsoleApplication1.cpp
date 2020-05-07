#include <fstream>
#include <iostream>
#include <vector>

void ReadInput(int& flights, int& crews, std::vector<std::vector<int>>& availability)
{
    std::ifstream fin("Availability.txt");

    fin >> flights;
    fin >> crews;

    for (int index1 = 0; index1 < flights; index1++)
    {
        std::vector<int> row;
        availability.push_back(row);

        for (int index2 = 0; index2 < crews; index2++)
        {
            int available;
            fin >> available;
            availability[index1].push_back(available);
        }
    }
}

int main()
{
    std::cout << "Hello World!\n";
}