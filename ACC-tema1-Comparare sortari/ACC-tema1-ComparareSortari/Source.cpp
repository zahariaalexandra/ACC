#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <chrono>

void BubbleSort(std::vector<int> &vector)
{
	int size = vector.size();

	for (int index = 0; index < size; index++)
	{
		for (int index2 = 0; index2 < size - index - 1; index2++)
		{
			if (vector[index2] > vector[index2 + 1])
			{
				int temp = vector[index2];
				vector[index2] = vector[index2 + 1];
				vector[index2 + 1] = temp;
			}
		}
	}
}

int Partition(std::vector<int> &vector, int low, int high)
{
	int pivot = vector[high];
	int index = low - 1;

	for (int index2 = low; index2 <= high - 1; index2++)
	{
		if (vector[index2] < pivot)
		{
			index++;
			int temp = vector[index];
			vector[index] = vector[index2];
			vector[index2] = temp;
		}
	}


	int temp = vector[index + 1];
	vector[index + 1] = vector[high];
	vector[high] = temp;

	return index + 1;
}

void QuickSort(std::vector<int>& vector, int low, int high)
{
	if (low < high)
	{
		int pivot = Partition(vector, low, high);
		QuickSort(vector, low, pivot - 1);
		QuickSort(vector, pivot + 1, high);
	}
}

void Merge(std::vector<int>& vector, std::vector<int>& left, std::vector<int>& right)
{
	int index1 = 0, index2 = 0, index3 = 0;
	int size1 = left.size(), size2 = right.size();

	while (index2 < size1 && index3 < size2)
	{
		if (left[index2] < right[index3])
		{
			vector[index1] = left[index2];
			index2++;
		}
		else
		{
			vector[index1] = right[index3];
			index3++;
		}

		index1++;
	}

	while (index2 < size1)
	{
		vector[index1] = left[index2];
		index1++;
		index2++;
	}

	while (index3 < size2)
	{
		vector[index1] = right[index3];
		index1++;
		index3++;
	}
}

void MergeSort(std::vector<int>& vector)
{
	if (vector.size() <= 1)
		return;

	int middle = vector.size() / 2;
	std::vector<int> left;
	std::vector<int> right;

	for (int index = 0; index < middle; index++)
	{
		left.push_back(vector[index]);
	}

	for (int index = 0; index < vector.size() - middle; index++)
	{
		right.push_back(vector[middle + index]);
	}

	MergeSort(left);
	MergeSort(right);
	Merge(vector, left, right);
}

void BitonicMerge(std::vector<int>& vector, int low, int size)
{
	if (size > 1)
	{
		int k = size / 2;

		for (int index = low; index < low + k; index++)
		{
			if (vector[index] > vector[index + k])
			{
				int temp = vector[index];
				vector[index] = vector[index + k];
				vector[index + k] = temp;
			}
		}

		BitonicMerge(vector, low, k);
		BitonicMerge(vector, low + k, k);
	}
}

void BitonicSort(std::vector<int>& vector, int low, int size)
{
	if (size > 1)
	{
		int k = size / 2;
		BitonicSort(vector, low, k);
		BitonicMerge(vector, low, size);
	}
}

int Maxim(std::vector<int> vector)
{
	int maximum = INT32_MIN;

	for (int index = 0; index < vector.size(); index++)
	{
		if (vector[index] > maximum)
			maximum = vector[index];
	}

	return maximum;
}

void LinearSort(std::vector<int>& vector)
{
	int contorSize = Maxim(vector);
	int* contor = new int[contorSize];

	for (int index = 0; index <= contorSize; index++)
	{
		contor[index] = 0;
	}
\
	for (int index = 0; index < vector.size(); index++)
	{
		contor[vector[index]]++;
	}

	vector.clear();

	for (int index = 0; index <= contorSize; index++)
	{
		if(contor[index])
			for (int index2 = 0; index2 < contor[index]; index2++)
			{
				vector.push_back(index);
			}
	}
}

std::vector<int> GenerateVector(int size)
{
	srand(time(NULL));
	std::vector<int> generatedVector;

	for (int index = 0; index < size; index++)
	{
		generatedVector.emplace_back(rand() % 100);
	}

	return generatedVector;
}

void TestSorts()
{
	std::ofstream fout("MeasuredTime.txt");

	std::vector<int> vector1, vector2, vector3, vector4;
	std::vector<int> auxVector;
	std::vector<int> times;
	int mediumTime;
	int size1 = 131072, size2 = 262144, size3 = 524288, size4 = 1048576;

	vector1 = GenerateVector(size1);
	vector2 = GenerateVector(size2);
	vector3 = GenerateVector(size3);
	vector4 = GenerateVector(size4);

	/*Bubble Sort*/
	//{
	//	std::cout << "-->Bubble Sort: \n";
	//	fout << "-->Bubble Sort: \n";
	//	/*size=100000*/
	//	std::cout << "->size = 100000\n";
	//	fout << "->size = 100000\n";

	//	int sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector1;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		BubbleSort(vector1);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 300000*/
	//	times.clear();
	//	std::cout << "->size = 300000\n";
	//	fout << "->size = 300000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector2;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		BubbleSort(vector2);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 600000*/
	//	times.clear();
	//	std::cout << "->size = 600000\n";
	//	fout << "->size = 600000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector3;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		BubbleSort(vector3);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 1000000*/
	//	times.clear();
	//	std::cout << "->size = 1000000\n";
	//	fout << "->size = 1000000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector4;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		BubbleSort(vector4);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";
	//}

	///*Merge Sort*/
	//{
	//	std::cout << "-->Merge Sort: \n";
	//	fout << "-->Merge Sort: \n";
	//	/*size=100000*/
	//	std::cout << "->size = 100000\n";
	//	fout << "->size = 100000\n";

	//	int sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector1;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		MergeSort(vector1);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 300000*/
	//	times.clear();
	//	std::cout << "->size = 300000\n";
	//	fout << "->size = 300000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector2;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		MergeSort(vector2);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 600000*/
	//	times.clear();
	//	std::cout << "->size = 600000\n";
	//	fout << "->size = 600000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector3;
	
	//		auto timeStart = std::chrono::steady_clock::now();
	//		MergeSort(vector3);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 1000000*/
	//	times.clear();
	//	std::cout << "->size = 1000000\n";
	//	fout << "->size = 1000000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector4;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		MergeSort(vector4);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";
	//}

	///*Bitonic Sort*/
	//{
	//	std::cout << "-->Bitonic Sort: \n";
	//	fout << "-->Bitonic Sort: \n";
	//	/*size=100000*/
	//	std::cout << "->size = 100000\n";
	//	fout << "->size = 100000\n";

	//	int sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector1;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		BitonicSort(vector1, 0, vector1.size()-1);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 300000*/
	//	times.clear();
	//	std::cout << "->size = 300000\n";
	//	fout << "->size = 300000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector2;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		BitonicSort(vector2, 0, vector2.size()-1);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 600000*/
	//	times.clear();
	//	std::cout << "->size = 600000\n";
	//	fout << "->size = 600000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector3;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		BitonicSort(vector3, 0, vector3.size()-1);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 1000000*/
	//	times.clear();
	//	std::cout << "->size = 1000000\n";
	//	fout << "->size = 1000000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector4;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		BitonicSort(vector4, 0, vector4.size()-1);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";
	//}

	///*Linear Sort*/
	//{
	//	std::cout << "-->Linear Sort: \n";
	//	fout << "-->Linear Sort: \n";
	//	/*size=100000*/
	//	std::cout << "->size = 100000\n";
	//	fout << "->size = 100000\n";

	//	int sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector1;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		LinearSort(vector1);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 300000*/
	//	times.clear();
	//	std::cout << "->size = 300000\n";
	//	fout << "->size = 300000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector2;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		LinearSort(vector2);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 600000*/
	//	times.clear();
	//	std::cout << "->size = 600000\n";
	//	fout << "->size = 600000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector3;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		LinearSort(vector3);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";

	//	/*size = 1000000*/
	//	times.clear();
	//	std::cout << "->size = 1000000\n";
	//	fout << "->size = 1000000\n";

	//	sumTime = 0;

	//	for (int index = 0; index < 3; index++)
	//	{
	//		auxVector = vector4;
	//		auto timeStart = std::chrono::steady_clock::now();
	//		LinearSort(vector4);
	//		auto timeEnd = std::chrono::steady_clock::now();
	//		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
	//		sumTime += times[index];

	//		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
	//		fout << "time " << index + 1 << ": " << times[index] << "\n";
	//	}

	//	mediumTime = sumTime / 3;
	//	std::cout << "medium time: " << mediumTime << "\n\n";
	//	fout << "medium time: " << mediumTime << "\n\n";
	//}

/*Quick Sort*/
	{
	std::cout << "-->Quick Sort: \n";
	fout << "-->Quick Sort: \n";
	/*size=100000*/
	std::cout << "->size = 100000\n";
	fout << "->size = 100000\n";

	int sumTime = 0;

	for (int index = 0; index < 3; index++)
	{
		auxVector = vector1;
		auto timeStart = std::chrono::steady_clock::now();
		QuickSort(vector1, 0, vector1.size() - 1);
		auto timeEnd = std::chrono::steady_clock::now();
		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
		sumTime += times[index];

		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
		fout << "time " << index + 1 << ": " << times[index] << "\n";
	}

	mediumTime = sumTime / 3;
	std::cout << "medium time: " << mediumTime << "\n\n";
	fout << "medium time: " << mediumTime << "\n\n";

	/*size = 300000*/
	times.clear();
	std::cout << "->size = 300000\n";
	fout << "->size = 300000\n";

	sumTime = 0;

	for (int index = 0; index < 3; index++)
	{
		auxVector = vector2;
		auto timeStart = std::chrono::steady_clock::now();
		QuickSort(vector2, 0, vector2.size() - 1);
		auto timeEnd = std::chrono::steady_clock::now();
		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
		sumTime += times[index];

		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
		fout << "time " << index + 1 << ": " << times[index] << "\n";
	}

	mediumTime = sumTime / 3;
	std::cout << "medium time: " << mediumTime << "\n\n";
	fout << "medium time: " << mediumTime << "\n\n";

	/*size = 600000*/
	times.clear();
	std::cout << "->size = 600000\n";
	fout << "->size = 600000\n";

	sumTime = 0;

	for (int index = 0; index < 3; index++)
	{
		auxVector = vector3;
		auto timeStart = std::chrono::steady_clock::now();
		QuickSort(vector3, 0, vector3.size() - 1);
		auto timeEnd = std::chrono::steady_clock::now();
		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
		sumTime += times[index];

		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
		fout << "time " << index + 1 << ": " << times[index] << "\n";
	}

	mediumTime = sumTime / 3;
	std::cout << "medium time: " << mediumTime << "\n\n";
	fout << "medium time: " << mediumTime << "\n\n";

	/*size = 1000000*/
	times.clear();
	std::cout << "->size = 1000000\n";
	fout << "->size = 1000000\n";

	sumTime = 0;

	for (int index = 0; index < 3; index++)
	{
		auxVector = vector4;
		auto timeStart = std::chrono::steady_clock::now();
		QuickSort(vector4, 0, vector4.size() - 1);
		auto timeEnd = std::chrono::steady_clock::now();
		times.emplace_back(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count());
		sumTime += times[index];

		std::cout << "time " << index + 1 << ": " << times[index] << "\n";
		fout << "time " << index + 1 << ": " << times[index] << "\n";
	}

	mediumTime = sumTime / 3;
	std::cout << "medium time: " << mediumTime << "\n\n";
	fout << "medium time: " << mediumTime << "\n\n";
	}

}

void PrintVector(std::vector<int> vector)
{
	for (int index = 0; index < vector.size(); index++)
	{
		std::cout << vector[index] << " ";
	}

	std::cout << std::endl;
}

int main()
{



	TestSorts();
}