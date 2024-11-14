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

//template <typename T>
//void	binary_insertion(T pend, T container, T oddElement, size_t pair_level)
//{
//	typename T::iterator cmp;
//	if (pend.size() < pair_level)
//	{
//		while (!pend.empty())
//		{
//			cmp = container.begin() + pair_level / 2 - 1;
//			if (cmp )
//		}
//	}
//	size_t jacobsthal_index = 1;
//	(void)jacobsthal_index;
//	(void)(oddElement);
//
//
//}

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

	typename T::iterator it = main.begin();
	while ( it + pair_level - 1 < main.end())
	{
		start = it + (pair_level / 2) - 1;
		end = it + (pair_level - 1);
		if (it == main.begin())
		{
			container.insert(container.end(), it, end + 1);
			it += pair_level;
			continue;
		}
		pend.insert(pend.end(), start - (pair_level / 2) + 1, start + 1);
		container.insert(container.end(), start + 1, end + 1);

		it += pair_level;

		if (it + pair_level - 1 >= main.end() && it + (pair_level / 2) - 1 < main.end())
			oddElement.insert(oddElement.end(), it, it + (pair_level / 2));
	}

	// Insert pend then oddElement into container using binary insertion and jacobsthal numbers
//	binary_insertion(pend, container, oddElement, pair_level);



}