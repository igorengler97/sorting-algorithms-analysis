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

void shell_sort(std::vector<int>& vec)
{

	int h = 1;
	int inner, outer;
	int value;
#pragma loop( no_vector )
	while (h < vec.size() / 3)
	{
		h = h * 3 + 1;
		//std::cout << h << " ";
	}
#pragma loop( no_vector )
	while (h > 0)
	{
#pragma loop( no_vector )
		for (outer = h; outer < vec.size(); outer++)
		{
			value = vec[outer];
			inner = outer;
#pragma loop( no_vector )
			while (inner > h - 1 && vec[inner - h] >= value)
			{
				vec[inner] = vec[inner - h];
				inner = inner - h;
			}

			vec[inner] = value;
		}
		h = (h - 1) / 3;
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