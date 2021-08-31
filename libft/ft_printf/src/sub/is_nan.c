/******************************************************************************
 *
 * \authors Satu Koskinen
 *
 * \brief Returns 1 if `n` is not a number.
 *
 *****************************************************************************/

#include "../../../incl/libft.h"

int	is_nan(double n)
{
	if (n != n)
		return (1);
	return (0);
}
