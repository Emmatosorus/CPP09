#include "../includes/PmergeMe.h"
#include "../includes/Templates.tpp"
#include "../includes/Sort.tpp"
#include <iostream>
#include <iomanip>

int main(int ac, char **av)
{
	try
	{
		if (ac < 3)
			throw std::invalid_argument("PmergeMe needs two intergers minimum to sort");

		clock_t	start_vector;
		clock_t	start_deque;
		clock_t	end_vector;
		clock_t	end_deque;

		// ----------- With vector -----------

		start_vector = clock();

		std::vector<size_t> vector;
		parse(av, vector);
		sort(vector, 2);

		end_vector = clock();

		// ----------- With deque -----------

		start_deque = clock();

		std::deque<size_t> deque;
		parse(av, deque);
		sort(deque, 2);

		end_deque = clock();

		// ----------- Check that both lists are sorted (optionnal)
		
		check(ac, av, vector);
		check(ac, av, deque);

		// ----------- Print the Before and After

		print(av, vector);

		// ----------- Display duration of sort

		double time_taken = double(end_vector - start_vector) / double(CLOCKS_PER_SEC);
		std::cout << std::fixed << std::setprecision(6);
		std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << time_taken << " sec " << std::endl;
		time_taken = double(end_deque - start_deque) / double(CLOCKS_PER_SEC);
		std::cout << std::fixed << std::setprecision(6);
		std::cout << "Time to process a range of " << deque.size() << " elements with std::deque : " << time_taken << " sec " << std::endl;
	}
	catch (std::exception & e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
		return (1);
	}
}
