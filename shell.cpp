#include "Header.h"

void shell_sort(std::vector<int>& vec)
{
	int h = 1;
	int inner, outer;
	int value;
	while (h < vec.size() / 3)
	{
		h = h * 3 + 1;
		std::cout << h << " ";
	}
	while (h > 0)
	{
		for (outer = h; outer < vec.size(); outer++)
		{
			value = vec[outer];
			inner = outer;

			while (inner > h - 1 && vec[inner - h] >= value)
			{
				vec[inner] = vec[inner - h];
				inner = inner - h;
			}

			vec[inner] = value;
		}
		h = (h - 1) / 3;
		std::cout << "   " << h << "   ";
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