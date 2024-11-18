#include "PmergeMe.h"

template <typename T>
void	swap(T & start1, T & start2, size_t& pair_level)
{
	T it1 = start1;
	T it2 = start2;
	for (size_t	i = 0; i != pair_level / 2; i++)
	{
		std::swap(*it1, *it2);
		it1--;
		it2--;
	}
}

template <typename T>
void	binary_search(T & container, T & to_insert, size_t element_size, size_t high)
{
	size_t bx = to_insert[element_size - 1];
	size_t low = element_size -1;
	size_t mid;

	while (!to_insert.empty())
	{
		mid = ((((low + 1) / element_size) + (((high + 1) / element_size) - ((low + 1) / element_size)) / 2) * element_size) - 1;
		if (bx > container[mid])
		{
			if (mid == high || bx < container[mid + element_size])
			{
				container.insert(container.begin() + mid + 1, to_insert.begin(), to_insert.end());
				return ;
			}
			else
				low = mid + element_size;
		}
		else if (bx < container[mid])
		{
			if (mid == low)
			{
				container.insert(container.begin(), to_insert.begin(), to_insert.end());
				return ;
			}
			else if (bx > container[mid - element_size])
			{
				container.insert(container.begin() + 1 + mid - element_size, to_insert.begin(), to_insert.end());
				return ;
			}
			else
				high = mid - element_size;
		}
	}
}

// high = (pair_level + (count + index - 1) * (pair_level / 2)) - 1;
//				high = ((count + index - 2) * pair_level / 2) - 1;
//				high = container.size() - 1;

// b3 {b1 a1 a2}
// {b1 a1 a2 b3}

// b2 {b1 a1}
// {b1 a1 b2 a2 b3}

// b
template <typename T>
void	insert_all(T & pend, T & container, T & oddElement, size_t pair_level)
{
	typename T::iterator cmp;
	T	to_insert;
	if (pend.size() < pair_level)
	{
		binary_search(container, pend, pair_level / 2, 2 * (pair_level / 2) - 1);
	}
	else
	{
		size_t jacobsthal_index = 3;
		size_t high;
		size_t count = 0;
		size_t index = 2;
		size_t decrease;
		while (!pend.empty())
		{

			index = (jacobsthal(jacobsthal_index) - jacobsthal(jacobsthal_index - 1)) * pair_level / 2;
			if (index > pend.size())
				index = pend.size();
			decrease = 0;
			while (index != 0)
			{
//				high = ((jacobsthal(jacobsthal_index) + count) - decrease) * (pair_level / 2) - 1;
				high = container.size();
				to_insert.insert(to_insert.begin(), pend.begin() + index - (pair_level / 2), pend.begin() + index);
				pend.erase(pend.begin() + index - (pair_level / 2), pend.begin() + index);
				binary_search(container, to_insert, pair_level / 2, high);
				count++;
				decrease++;
				to_insert.clear();
				index -= pair_level / 2;
			}
			jacobsthal_index++;
		}
	}
	if (!oddElement.empty())
	{
		binary_search(container, oddElement, pair_level / 2, container.size() - 1);
	}
}

template <typename T>
void	sort( T & main, size_t pair_level )
{
	typename T::iterator end;
	typename T::iterator start;

	// Do simple recursive sort of numbers

	for (typename T::iterator it = main.begin(); it + pair_level - 1 < main.end(); it += pair_level)
	{
		start = it + (pair_level / 2) - 1;
		end = it + (pair_level - 1);
		if (*start > *end)
			swap(start, end, pair_level);
	}
	if (main.size() / pair_level >= 2)
		sort(main, pair_level * 2);

	// Organize numbers between Pend Main and Odd
	T pend;
	T container;
	T oddElement;
	T leftOvers;

	typename T::iterator it = main.begin();
	while ( it != main.end())
	{
		start = it + (pair_level / 2) - 1;
		end = it + (pair_level - 1);
		if (it == main.begin())
		{
			container.insert(container.end(), it, end + 1);
			it += pair_level;
			continue;
		}
		if (it + pair_level - 1 < main.end())
		{
			pend.insert(pend.end(), start - (pair_level / 2) + 1, start + 1);
			container.insert(container.end(), start + 1, end + 1);
			it += pair_level;
		}
		if (it + pair_level - 1 >= main.end())
		{
			if (it + (pair_level / 2) - 1 < main.end())
			{
				oddElement.insert(oddElement.end(), it, it + (pair_level / 2));
				main.erase(it, it + (pair_level / 2));
			}
			leftOvers.insert(leftOvers.end(), it, main.end());
			break ;
		}
	}

	// Insert pend then oddElement into container using binary insertion and jacobsthal numbers
	if (!pend.empty())
	{
		insert_all(pend, container, oddElement, pair_level);
		oddElement.clear();

		// copy container in the main
		main = container;
		main.insert(main.end(), leftOvers.begin(), leftOvers.end());
	}
	if (pair_level == 2 && !oddElement.empty())
		binary_search(main, oddElement, oddElement.size(), main.size());
}