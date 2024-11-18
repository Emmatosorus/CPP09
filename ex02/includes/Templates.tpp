#include "PmergeMe.h"

template <typename T>
bool is_exclusive(T container, size_t nb)
{
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		if (*it == nb)
			return false;
	return true;
}

template <typename T>
void	print(char **av, T container)
{
	std::cout << "Before :";
	for (int i = 1; av[i]; i++)
		std::cout << " " << av[i];
	std::cout << std::endl;
	std::cout << "After :";
	for (typename T::iterator it = container.begin(); it != container.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;
}

template <typename T>
void	parse(char **input, T & container)
{
	int	tmp;
	int	i = 1;
	while (input[i])
	{
		if (!is_number(input[i]))
			throw std::invalid_argument("PmergeMe only accepts positive numbers");
		tmp = static_cast<size_t>(atof(input[i]));
		if (!is_exclusive(container, tmp))
			throw std::invalid_argument("PmergeMe does not accept duplicate numbers");;
		container.push_back(tmp);
		i++;
	}
}

template <typename T>
void	check(int ac, char **av, T array)
{
	if (ac - 1 != (int)array.size())
	{
		print(av, array);
		throw std::runtime_error("\x1B[1mArray is not same size\x1B[0m");
	}


	typename T::iterator it = array.begin();
	while (it + 1 != array.end())
	{
		if (*(it) > *(it + 1))
		{
			print(av, array);
			throw std::runtime_error("\x1B[1mArray is not sorted\x1B[0m");
		}
		it++;
	}
	std::cout << "\x1B[1;32mArray is sorted!!!\x1B[0m" << std::endl;
}