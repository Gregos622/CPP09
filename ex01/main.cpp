
#include <stack>
#include <iostream>
#include <string>

int main (int ac, char **av)
{

	if (ac == 2)
	{
		size_t i = 0;
		std::string expression = av[1];
		bool error = false;

		std::stack <int> stackVal;

		while (i < expression.size())
		{

			if (expression[i] >= '0' && expression[i] <= '9')
				stackVal.push(expression[i] - '0');

			else if (expression[i] == '+')
			{
				if (stackVal.size() > 1)
				{
					int v2 = stackVal.top();
					stackVal.pop();
					int v1 = stackVal.top();
					stackVal.pop();

					stackVal.push(v1 + v2);
				}
			}
			else if (expression[i] == '-')
			{
				if (stackVal.size() > 1)
				{
					int v2 = stackVal.top();
					stackVal.pop();
					int v1 = stackVal.top();
					stackVal.pop();

					stackVal.push(v1 - v2);
				}
			}
			else if (expression[i] == '*')
			{
				if (stackVal.size() > 1)
				{
					int v2 = stackVal.top();
					stackVal.pop();
					int v1 = stackVal.top();
					stackVal.pop();

					stackVal.push(v1 * v2);
				}
			}
			else if (expression[i] == '/')
			{
				if (stackVal.size() > 1)
				{
					int v2 = stackVal.top();
					stackVal.pop();
					int v1 = stackVal.top();
					stackVal.pop();

					stackVal.push(v1 / v2);
				}
			}
			else if (expression[i] == ' ')
			{
				i++;
				continue;
			}
			else
			{
				std::cout << "Error\n";
				error = true;
				break;
			}
			
			i++;
		}

		if (!error)
			std::cout << stackVal.top() << '\n';
	}
	else
		std::cout << "Not enought praramters!\n";
    return(0);
}