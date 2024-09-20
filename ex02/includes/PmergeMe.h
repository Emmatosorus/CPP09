#ifndef PMERGEME_H
#define PMERGEME_H

// **** includes ****
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <stdint.h>
#include <vector>
#include <deque>

// **** function prototypes ****

bool	is_number(std::string nbr);
int		jacobsthal(int index);
int		get_value(std::pair<void *, void *> *pairs, int depth);
void	delete_pair_down(std::pair<void *, void *> *&pairs, int depth);


#endif
