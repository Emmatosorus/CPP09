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

template <typename T, typename F>
void	devide_n_conquer(T & main, F & pend, F & new_main, F & oddElement, T & leftOvers, size_t pair_level)
{
	typename T::iterator end;
	typename T::iterator start;
	size_t element_size = pair_level / 2;

	typename T::iterator it = main.begin();
	start = it + (pair_level / 2) - 1;
	end = it + (pair_level - 1);
	new_main.push_back(it + element_size - 1);
	new_main.push_back(end);
	it += pair_level;
	while (it < main.end())
	{
		start = it + (pair_level / 2) - 1;
		end = it + (pair_level - 1);
		if (end < main.end())
		{
			pend.push_back(start);
			new_main.push_back(end);
		}
		else
		{
			if (it + element_size - 1 < main.end())
			{
				oddElement.push_back(it + element_size - 1);
				it += element_size;
			}
			if (it < main.end())
				leftOvers.insert(leftOvers.end(), it, main.end());
		}
		it += pair_level;
	}
}

template <typename T, typename F>
void	insert(T & pend, T & new_main, T & oddElement, F copy)
{
	typename T::iterator it;
	typename F::iterator copy_it;
	for (typename T::iterator itr = new_main.begin(); itr != new_main.end(); itr++)
		copy.push_back(**itr);
	if (pend.size() == 1)
	{
		copy_it = std::upper_bound(copy.begin(), copy.end() - 1, **(pend.begin()));
		new_main.insert(new_main.begin() + (copy_it - copy.begin()), *(pend.begin()));
		copy.insert(copy_it, **(pend.begin()));
	}
	else if (pend.size() > 1)
	{
		size_t jacobsthal_index = 3;
		size_t count = 0;
		size_t index;
		size_t decrease;
		while (!pend.empty())
		{
			index = jacobsthal(jacobsthal_index) - jacobsthal(jacobsthal_index - 1);
			if (index > pend.size())
				index = pend.size();
			decrease = 0;
			while (index != 0)
			{
				copy_it = copy.begin() + (jacobsthal(jacobsthal_index) + count) - decrease;
				if (copy_it > copy.end())
					copy_it = copy.end();
				copy_it = std::upper_bound(copy.begin(), copy_it, **(pend.begin() + index - 1));
				new_main.insert(new_main.begin() + (copy_it - copy.begin()), *(pend.begin() + index - 1));
				copy.insert(copy_it, **(pend.begin() + index - 1));
				pend.erase(pend.begin() + index - 1, pend.begin() + index);

				count++;
				decrease++;
				index--;
			}
			jacobsthal_index++;
		}
	}
	if (!oddElement.empty())
	{
		copy_it = std::upper_bound(copy.begin(), copy.end(), **(oddElement.begin()));
		new_main.insert(new_main.begin() + (copy_it - copy.begin()), *(oddElement.begin()));
	}
}

template <typename T, typename F>
void	rebuild_main(T & main, F & new_main, T & leftOvers, size_t element_size)
{
	T main_copy;
	typename F::iterator it = new_main.begin();
	while (it != new_main.end())
	{
		main_copy.insert(main_copy.end(), (*it) - (element_size - 1), (*it) + 1);
		it++;
	}
	main_copy.insert(main_copy.end(), leftOvers.begin(), leftOvers.end());
	main = main_copy;
}

template <typename T>
void	sort( T & main, size_t pair_level)
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

	// Organize numbers between Pend, new Main, Odd and what's left

	std::vector<typename T::iterator> pend;
	std::vector<typename T::iterator> new_main;
	std::vector<typename T::iterator> oddElement;
	T leftOvers;
	size_t element_size = pair_level / 2;

	devide_n_conquer(main, pend, new_main, oddElement, leftOvers, pair_level);

	// insert Pend and Odd in the new Main
	if (!pend.empty() || !oddElement.empty())
	{
		T copy;
		insert(pend, new_main, oddElement, copy);
		rebuild_main(main, new_main, leftOvers, element_size);
	}

}