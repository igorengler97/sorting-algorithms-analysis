#include "Header.h"

void insertion_sort(std::vector<int>& vec)
{
#pragma loop( no_vector )
	for (std::size_t j = 1; j < vec.size(); j++)
	{
		int key = vec[j];
		int i = j - 1;

		while (i >= 0 && vec[i] > key)
		{
			vec[i + 1] = vec[i];
			i--;
		}
		vec[i + 1] = key;
	}
}

void print(std::vector<int>& vec)
{
	for (unsigned i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << "\n";
}