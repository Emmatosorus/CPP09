#include "../includes/PmergeMe.h"

bool	is_number(std::string nbr)
{
	for (int i = 0; nbr[i]; i++)
		if (nbr[i] < '0' || nbr[i] > '9')
			return false;
	return true;
}

int	jacobsthal(int index)
{
	return (int)( (pow(-1, index-1) + pow(2, index)) / 3 );
}

int	get_value(std::pair<void *, void *> *pairs, int depth)
{
	int	res;
	if (depth == 0)
		res = static_cast<int>(reinterpret_cast<intptr_t>(pairs->first));
	else
		res = get_value(reinterpret_cast<std::pair<void *, void *> *>(pairs->first), depth - 1);
	return (res);
}

void	delete_pair_down(std::pair<void *, void *> *pairs, int depth)
{
	if (depth == 0)
		delete [] pairs;
	else
	{
		delete_pair_down(reinterpret_cast<std::pair<void *, void *> *>(pairs->first), depth - 1);
		delete [] pairs;
	}
	return ;
}
