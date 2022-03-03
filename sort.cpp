#include "Header.h"

void insertion_sort(std::vector<int>& vec)
{
	int i, j;
	int value;
	for (i = 1; i < vec.size(); i++)
	{
		value = vec[i];
		j = i - 1;

		while (j >= 0 && vec[j] > value)
		{
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = value;
	}
}

void shell_sort(std::vector<int>& vec)
{
	int h = 1;
	int i, j;
	int value;
	while (h < vec.size()/3)
	{
		h = h * 3 + 1;  
		//h = (pow(3.0, double(h)) - 1) / 2;
		//std::cout << h << " ";
	}
	std::cout << h << " ";
	//std::cout<<std::endl;
	while (h > 0)
	{
		for (i = h; i < vec.size(); i++)
		{
			value = vec[i];
			j = i;
			while (j > h - 1 && vec[j - h] >= value)
			{
				vec[j] = vec[j - h];
				j = j - h;
			}
			vec[j] = value;
		}
		h = h/3;
		std::cout << h << " ";
	}
	std::cout << std::endl;
}

void print(std::vector<int>& vec)
{
	for (unsigned i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}