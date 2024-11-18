#include "../includes/PmergeMe.h"
#include "../includes/Templates.tpp"
#include "../includes/Sort.tpp"
#include <iostream>
#include <iomanip>

int main(int ac, char **av)
{
//	std::cout << ac - 1 << std::endl;
	try
	{
//		clock_t	start;
//		clock_t	end;

//		start = clock();


		if (ac < 3)
			throw std::invalid_argument("PmergeMe needs two intergers minimum to sort");
		std::vector<size_t> vector;
		parse(av, vector);
		sort(vector, 2);

		if (ac - 1 != (int)vector.size())
		{
			print(av, vector);
			throw std::runtime_error("\x1B[1mList is not same size\x1B[0m");
		}


		std::vector<size_t>::iterator it = vector.begin();
		while (it + 1 != vector.end())
		{
			if (*(it) > *(it + 1))
				 throw std::runtime_error("\x1B[1mList is not sorted\x1B[0m");
			it++;
		}
		std::cout << "\x1B[1;32mList is sorted!!!\x1B[0m" << std::endl;


//		end = clock();

		print(av, vector);

//		std::cout << std::endl;

//		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
//		std::cout << std::fixed << std::setprecision(6);
//		std::cout << "Time to process a range of " << vector.size() << " elements with std::list : " << time_taken << " sec " << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Error : " << e.what() << std::endl;
		return (1);
	}
}
