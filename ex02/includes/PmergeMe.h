#ifndef PMERGEME_H
#define PMERGEME_H

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <vector>
#include <deque>

bool	is_number(std::string nbr);
int		jacobsthal(int index);

template <typename T>
bool is_exclusive(T container, int nb)
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
		tmp = static_cast<int>(atof(input[i]));
		if (!is_exclusive(container, tmp))
			throw std::invalid_argument("PmergeMe does not accept duplicate numbers");;
		container.push_back(tmp);
		i++;
	}
}

template <typename T>
void	sort( T & container )
{
	T	sorted;
	(void)container;
	std::cout << "jacobsthal :";
	for (int i = 0; i < 20; i++)
		std::cout << " " << jacobsthal(i);
	std::cout << std::endl;
	// sort
}


#endif
