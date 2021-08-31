/******************************************************************************
 *
 * \authors Satu Koskinen
 *
 * \brief
 *
 *****************************************************************************/

#include "../../../incl/libft.h"
#include "../inc/print_internal.h"

uintmax_t	_uintmax_pow(int base, int power)
{
	uintmax_t	result;

	result = 1;
	while (power > 0)
	{
		result *= base;
		power--;
	}
	return (result);
}
