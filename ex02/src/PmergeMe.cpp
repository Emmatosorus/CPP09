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
	return (   (pow(-1, index-1) + pow(2, index)) / 3   );
}