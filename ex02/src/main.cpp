#include "../includes/PmergeMe.h"
#include <iostream>
#include <iomanip>

int main(int ac, char **av)
{
	try
	{
		clock_t	start;
		clock_t	end;

		start = clock();


		if (ac < 3)
			throw std::invalid_argument("PmergeMe needs two intergers minimum to sort");
		std::vector<int> vector;
		parse(av, vector);
		sort(vector);

		end = clock();

		print(av, vector);

		std::cout << std::endl;

		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		std::cout << std::fixed << std::setprecision(6);
		std::cout << "Time to process a range of " << vector.size() << " elements with std::list : " << time_taken << " sec " << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Error : " << e.what() << std::endl;
		return (1);
	}
}
