/******************************************************************************
 *
 * \authors Satu Koskinen
 *
 * \brief
 *
 *****************************************************************************/

#include "../../../incl/libft.h"
#include "../inc/print_internal.h"

int	_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return ((int)(result * sign));
}
