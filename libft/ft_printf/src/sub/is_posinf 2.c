/******************************************************************************
 *
 * \authors Satu Koskinen
 *
 * \brief Returns 1 if `n` is positive infinity.
 *
 *****************************************************************************/

#include "../../../incl/libft.h"

int	is_posinf(double n)
{
	if (n == 1.0 / 0.0)
		return (1);
	return (0);
}
