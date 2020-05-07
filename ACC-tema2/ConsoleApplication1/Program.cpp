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

int NumberOfAvailableCrews(std::vector<int> flight)
{
    int available = 0;

    for (int elem : flight)
    {
        if (elem != 0)
            available++;
    }

    return available;
}

int AvailableCrew(std::vector<int> flight)
{
    for (int index = 0; index < flight.size(); index++)
    {
        if (flight[index] == 1)
            return index;
    }

    return 0;
}

void UpdateCrew(std::vector<std::vector<int>>& availability, int crew)
{
    for (int index = 0; index < availability.size(); index++)
    {
        availability[index][crew] = 0;
    }
}

std::vector<int> GeneratePossibility(int flights, int crews, std::vector<std::vector<int>>& availability)
{
    std::vector<int> possibility(flights, -1);
    bool findingCrew = false;

    do
    {
        findingCrew = false;

        for (int index = 0; index < availability.size(); index++)
        {
            if (NumberOfAvailableCrews(availability[index]) == 1 && possibility[index] == -1)
            {
                int availableCrew = AvailableCrew(availability[index]);
                possibility[index] = availableCrew;
                UpdateCrew(availability, availableCrew);
                findingCrew = true;
            }
        }
    } while (findingCrew);

    for (int index = 0; index < availability.size(); index++)
    {
        if (possibility[index] == -1 && NumberOfAvailableCrews(availability[index]) != 0)
        {
            int availableCrew = AvailableCrew(availability[index]);
            possibility[index] = availableCrew;
            UpdateCrew(availability, availableCrew);
        }
    }

    return possibility;
}

void PrintPossibility(std::vector<int> possibility)
{
    for (int index = 0; index < possibility.size(); index++)
    {
        if (possibility[index] == -1)
            std::cout << possibility[index] << " ";
        else
            std::cout << possibility[index] +  1<< " ";
    }
}

int main()
{
    int flights = 0, crews = 0;
    std::vector<std::vector<int>> avaibility;
    std::vector<int> possibility;

    ReadInput(flights, crews, avaibility);
    possibility = GeneratePossibility(flights, crews, avaibility);
    PrintPossibility(possibility);

    system("pause");
    return 0;
}