#include "../includes/RPN.h"

int	calculate(std::string input)
{
	std::stack<int> stack;
	int	operands[2];
	int i = 0;

	while (input[i])
	{
		if (input[i] >= '0' && input[i] <= '9')
			stack.push(input[i] - 48);
		else
		{
			if (stack.empty())
				throw std::invalid_argument("incorrect number of operators");
			operands[0] = stack.top();
			stack.pop();
			if (stack.empty())
				throw std::invalid_argument("incorrect number of operators");
			operands[1] = stack.top();
			stack.pop();
			if (input[i] == '+')
			{
			//	std::cout << operands[1] << " + " << operands[0] << " = " << operands[1] + operands[0] << std::endl;
				stack.push(operands[1] + operands[0]);
			}
			else if (input[i] == '-')
			{
			//	std::cout << operands[1] << " - " << operands[0] << " = " << operands[1] - operands[0] << std::endl;
				stack.push(operands[1] - operands[0]);
			}
			else if (input[i] == '*')
			{
			//	std::cout << operands[1] << " * " << operands[0] << " = " << operands[1] * operands[0] << std::endl;
				stack.push(operands[1] * operands[0]);
			}
			else if (input[i] == '/')
			{
			//	std::cout << operands[1] << " / " << operands[0] << " = " << operands[1] / operands[0] << std::endl;
				stack.push(operands[1] / operands[0]);
			}
		}
		i++;
	}
	return (stack.top());
}

void	parse(std::string & parsed, std::string raw)
{
	for (int i = 0; raw[i]; i++)
	{
		if (raw[i] != '+' && raw[i] != '-' && raw[i] != '*' && raw[i] != '/' \
			&& raw[i] != ' ' && (raw[i] < '0' || raw[i] > '9'))
			throw std::invalid_argument("RPN only accepts : \'*/+-\' and digits from 0 (zero) to 9 (nine)");
		if (raw[i] != ' ')
		{
			if (raw[i + 1] != ' ' && raw[i + 1] != '\0')
				throw std::invalid_argument("Every operand and operator must be spaced out by 1 (one) space");
			parsed += raw[i];
		}
	}
}