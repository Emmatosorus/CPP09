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
void	pair_up(std::pair<int, int> **pairs, T & container )
{
	*pairs = new std::pair<int, int>[(int)(std::ceil(container.size() / 2))];

	int i = 0;
	int pair_index = 0;
	while (container[i])
	{
		if (!container[i + 1])
			(*pairs)[pair_index] = std::make_pair(container[i], -1);
		else
			(*pairs)[pair_index] = std::make_pair(container[i], container[i + 1]);
//		std::cout << (*pairs)[pair_index].first << ", " << (*pairs)[pair_index].second;
		i += 2;
		pair_index++;
	}
}

template <typename T>
void	sort( T & container )
{
	T	sorted;
	std::pair<int, int>	*pairs;


	pair_up(&pairs, container);


	// sort

	for (int i = 0; i <= (int)(std::ceil(container.size() / 2)); i++)
		std::cout << pairs[i].first << ", " << pairs[i].second << std::endl;
	delete pairs;
}


#endif
