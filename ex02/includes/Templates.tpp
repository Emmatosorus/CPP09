#include "PmergeMe.h"

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
void	pair_up(std::pair<void *, void *> *&o_pairs, T & container, int & odd)
{
	std::pair<void *, void *> *n_pairs = new std::pair<void *, void *>[(int)std::floor(container.size() / 2)];

	size_t i = 0;
	int pair_index = 0;
	while (i < container.size())
	{
		if (i + 1 >= container.size())
		{
			odd = container[i];
			container.pop_back();
		}
		else
		{
			if (container[i] < container[i + 1])
				n_pairs[pair_index] = std::make_pair(reinterpret_cast<void *>(container[i]), reinterpret_cast<void *>(container[i + 1]));
			else
				n_pairs[pair_index] = std::make_pair(reinterpret_cast<void *>(container[i + 1]), reinterpret_cast<void *>(container[i]));
		}
		i += 2;
		pair_index++;
	}
	o_pairs = n_pairs;
}

template <typename T>
std::pair<void *, void *>	*pair_down(std::pair<void *, void *> *&o_pairs, T & container, int depth, std::vector<std::pair<void *, void *> *> & gb_collector)
{
	int	value1;
	int	value2;
	int	nb_pairs = std::ceil(container.size() / pow(2, depth));
	if (nb_pairs == 2)
	{
		std::pair<void *, void *> *n_pairs = new std::pair<void *, void *>[1];
		gb_collector.push_back(n_pairs);
		value1 = get_value(&o_pairs[0], depth - 1);
		value2 = get_value(&o_pairs[1], depth - 1);
		if (value1 < value2)
			*n_pairs = std::make_pair(reinterpret_cast<void *>(&o_pairs[0]), reinterpret_cast<void *>(&o_pairs[1]));
		else
			*n_pairs = std::make_pair(reinterpret_cast<void *>(&o_pairs[1]), reinterpret_cast<void *>(&o_pairs[0]));
		return (n_pairs);
	}
	else
	{
		std::pair<void *, void *> *n_pairs = new std::pair<void *, void *>[(int)(std::ceil(container.size() / pow(2, depth + 1)))];
		gb_collector.push_back(n_pairs);
		int i = 0;
		int i2 = 0;
		while (i < nb_pairs)
		{
			value1 = get_value(&o_pairs[i], depth - 1);
			if (i + 1 == nb_pairs)
				value2 = -1;
			else
				value2 = get_value(&o_pairs[i + 1], depth - 1);
			if (value1 < value2 && value2 >= 0)
				n_pairs[i2] = std::make_pair(reinterpret_cast<void *>(&o_pairs[i]), reinterpret_cast<void *>(&o_pairs[i + 1]));
			else if (value2 >= 0)
				n_pairs[i2] = std::make_pair(reinterpret_cast<void *>(&o_pairs[i + 1]), reinterpret_cast<void *>(&o_pairs[i]));
			else
				n_pairs[i2] = std::make_pair(reinterpret_cast<void *>(&o_pairs[i]), (void *)0);
			i2++;
			i += 2;
		}
		std::pair<void *, void *>	*ptr = pair_down(n_pairs, container, depth + 1, gb_collector);
		return (ptr);
	}

}

template <typename T>
void	sort( T & container )
{
	T	sorted;

	std::pair<void *, void *>	*pairs = 0;
	std::pair<void *, void *>	*new_pairs = 0;
	std::vector<std::pair<void *, void *> *>	gb_collector;

	int	depth = 0;
	int thing = 0;
	while (thing != 2)
	{
		thing = std::ceil(container.size() / pow(2, depth));
		depth++;
	}

	int	odd = -1;

	pair_up(pairs, container, odd);
	new_pairs = pair_down(pairs, container, 1, gb_collector);

	// sort

	int test = get_value(new_pairs, depth - 1);
	int test2 = get_value(reinterpret_cast<std::pair<void *, void *> *>(new_pairs->second), 2);
	std::cout << test << ", " << test2 << std::endl;
	if (odd != -1)
		std::cout << odd << std::endl;

	for (int i = 0; i < (int)gb_collector.size(); i++)
		delete [] gb_collector [i];

	delete [] pairs;





}