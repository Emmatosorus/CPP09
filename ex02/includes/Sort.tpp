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
	typename T::iterator it = main.begin();
	typename T::iterator end = it + (pair_level - 1);
	typename T::iterator start = it + (pair_level / 2) - 1;
	size_t element_size = pair_level / 2;
	size_t nb_it = 0;

	// We put into the new main the first pair a1 and b1

	new_main.push_back(it + element_size - 1);
	new_main.push_back(end);

	it += pair_level;
	nb_it += pair_level;

	while (nb_it < main.size())
	{
		// If there is a full pair then we devide ax and bx into pend and new_main respectively

		 if (nb_it + (pair_level - 1) < main.size())
		 {
		 	start = it + (pair_level / 2) - 1;
		 	end = it + (pair_level - 1);

		 	pend.push_back(start);
		 	new_main.push_back(end);
		 }

		// If not then we are at the end of our array

		else
		{
			// If there is an odd element (not a full pair) then we put it in OddElement

			if (nb_it + element_size - 1 < main.size())
			{
				oddElement.push_back(it + element_size - 1);
				it += element_size;
			}

			// If there are some integers left but not enough to make up an element we put it in the leftOvers vector

			if (nb_it < main.size())
				leftOvers.insert(leftOvers.end(), it, main.end());
			return ;
		}
		if (nb_it + pair_level < main.size())
		{
			it += pair_level;
			nb_it += pair_level;
		}
		else
			return ;

	}
}

template <typename T, typename F>
void	insert(T & pend, T & new_main, T & oddElement, F copy)
{
	typename F::iterator copy_it;

	// We put in copy the numbers pointed to by each interator in new_main

	for (typename T::iterator itr = new_main.begin(); itr != new_main.end(); itr++)
		copy.push_back(**itr);

	// If there is only one element in pend, we insert normally since jacobsthal does not apply

	if (pend.size() == 1)
	{
		copy_it = std::upper_bound(copy.begin(), copy.end() - 1, **(pend.begin()));
		new_main.insert(new_main.begin() + (copy_it - copy.begin()), *(pend.begin()));
		copy.insert(copy_it, **(pend.begin()));
	}

	// If there are more than one element in pend then we insert using jacobsthal to set the order of insertion

	else if (pend.size() > 1)
	{
		size_t jacobsthal_index = 3;
		size_t count = 0;
		size_t index;
		size_t decrease;
		while (!pend.empty())
		{
			// We use jacobsthal to get the index of the element we will first insert

			index = jacobsthal(jacobsthal_index) - jacobsthal(jacobsthal_index - 1);
			if (index > pend.size())
				index = pend.size();

			// We then insert the element at index and anything before it

			decrease = 0;
			while (index != 0)
			{
				// We calculate where we can limit our search area for binary search to use less comparisions

				if ((jacobsthal(jacobsthal_index) + count) - decrease <= copy.size())
					copy_it = copy.begin() + (jacobsthal(jacobsthal_index) + count) - decrease;
				else
					copy_it = copy.end();

				// We use upper_bound to find where to insert the element at index

				copy_it = std::upper_bound(copy.begin(), copy_it, **(pend.begin() + index - 1));

				// We then insert the iterator element into the new_main, the number element into copy, and remove the iterator element from pend

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

	// If there is an odd element we insert it to the new_main

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

	// We insert into main_copy the numbers pointed to by the iterators in new_main along with whatever other numbers are paired
	// to it on this recursion level

	while (it != new_main.end())
	{
		main_copy.insert(main_copy.end(), (*it) - (element_size - 1), (*it) + 1);
		it++;
	}

	// We insert any leftovers

	main_copy.insert(main_copy.end(), leftOvers.begin(), leftOvers.end());

	main = main_copy;
}

template <typename T>
void	sort( T & main, size_t pair_level)
{
	typename T::iterator end;
	typename T::iterator start;

	// Simple recursive sort of numbers using a pairing method

	for (typename T::iterator it = main.begin(); it + (pair_level - 1) < main.end(); it += pair_level)
	{
		start = it + (pair_level / 2) - 1;
		end = it + (pair_level - 1);
		if (*start > *end)
			swap(start, end, pair_level);
	}
	if (main.size() / pair_level >= 2)
		sort(main, pair_level * 2);

	// Organize pairs between Pend, new Main, Odd and what's left

	std::vector<typename T::iterator> pend;
	std::vector<typename T::iterator> new_main;
	std::vector<typename T::iterator> oddElement;
	T leftOvers;
	size_t element_size = pair_level / 2;

	devide_n_conquer(main, pend, new_main, oddElement, leftOvers, pair_level);

	// if there is something in pend or odd we insert them in the new Main

	if (!pend.empty() || !oddElement.empty())
	{
		T copy;
		insert(pend, new_main, oddElement, copy);

		// We then use new_main (a vector of iterators) to build the main (a vector of integers)

		rebuild_main(main, new_main, leftOvers, element_size);
	}
}